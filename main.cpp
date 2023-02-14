#include <iostream>
#include <mpi.h>
#include <cmath>
bool  esPrimo(int numero){

    bool primo=true;
    if(numero==1){
        primo=false;
    }else{
    for(int i=2;i<(numero/2+1);i++){
            if(numero%i==0){
            primo=false;
            }
        }
    }
    
    //printf("%d, %d\n",primo,numero);

    return primo;
}
void primoTruncado(){
    int truncado[100];
    int cont=0;
    int aux=0;
    bool esTruncado=true;
    for(int i=1;i<100;i++){
      int numero=i;
      int digitos=log10(numero);
      
        if(esPrimo(numero)==true){
         
            while(numero>=10){
                 printf("dig %d\n",(int)pow(10,digitos));
                numero= numero % (int)pow(10,digitos);
                if(esPrimo(numero)==false){
                    esTruncado=false;
                }
                digitos--;

            }
             if(esTruncado==true){
                    truncado[cont]=i;
                    cont++;
                }
        }

    }
    
    for(int i=0;i<cont;i++){
        printf("los numeros truncados son: %d \n",truncado[i]);
    }
}
int main(int argc, char** argv){
    int rank;
    int size;
    int data[100];

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
   MPI_Comm_size(MPI_COMM_WORLD, &size); 
   primoTruncado();
   std::printf("hola soy el rank %d, de un total de %d procesos \n" ,rank,size); 
}