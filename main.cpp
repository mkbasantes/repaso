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
    for(int i=1;i<100;i++){
      bool esTruncado=true;
      int numero=i;
      int digitos=log10(numero);
      
        if(esPrimo(numero)==true){
         
            while(numero>=10){
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
    int part=20;
    int inicio=50;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 

   std::printf("hola soy el rank %d, de un total de %d procesos \n" ,rank,size); 
   if(rank==0){
    for(int i =1;i<=100;i++){
        data[i]=i;        
    }
    
    MPI_Request request;
    for(int i=1;i<4;i++){
        if(i==1){
           MPI_Isend(&data[0],inicio,MPI_INT,i,0,MPI_COMM_WORLD,&request);  
        }else{
            MPI_Isend(&data[inicio],part,MPI_INT,i,0,MPI_COMM_WORLD,&request);
            inicio=part+inicio;
        }
        
    }
    int cont=0;
    int truncado[100];
    for(int i=inicio;i<100;i++){
      bool esTruncado=true;
      int numero=data[i];
      int digitos=log10(numero);
      
        if(esPrimo(numero)==true){
         
            while(numero>=10){
                numero= numero % (int)pow(10,digitos);
                if(esPrimo(numero)==false){
                    
                    esTruncado=false;
                }
                digitos--;
            }
             if(esTruncado==true){
                    truncado[cont]=data[i];
                    cont++;
                }
        }

    }
    
    for(int i=0;i<cont;i++){
        printf("numeros truncados son: %d \n",truncado[i]);
    }
   
    for(int i=1;i<4;i++){

        int count=0;
        MPI_Irecv(&count,1,MPI_INT,i,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,MPI_STATUS_IGNORE);

        int truncado2[count];
        MPI_Irecv(truncado2,count,MPI_INT,i,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,MPI_STATUS_IGNORE);

        for(int i=0;i<count;i++){
            printf("los numeros truncados son: %d \n",truncado2[i]);
        }
    }
   }else if(rank==1){
   
        MPI_Request request;
            MPI_Irecv(data,inicio,MPI_INT,0,0,MPI_COMM_WORLD,&request);
            MPI_Wait(&request,MPI_STATUS_IGNORE);
            int cont=0;
            int truncado[inicio];
            for(int i=0;i<inicio;i++){
            bool esTruncado=true;
            int numero=data[i];
            int digitos=log10(numero);
            
                if(esPrimo(numero)==true){
                
                    while(numero>=10){
                        numero= numero % (int)pow(10,digitos);
                        if(esPrimo(numero)==false){
                            
                            esTruncado=false;
                        }
                        digitos--;
                    }
                    if(esTruncado==true){
                            truncado[cont]=data[i];
        
                            cont++;
                        }
                }

            }

                MPI_Isend(&cont,1,MPI_INT,0,0,MPI_COMM_WORLD,&request);
                MPI_Isend(&truncado[0],cont,MPI_INT,0,0,MPI_COMM_WORLD,&request);
    }else{

        MPI_Request request;
        MPI_Irecv(data,part,MPI_INT,0,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request,MPI_STATUS_IGNORE);
       
        int cont=0;
        int truncado[part];
        for(int i=0;i<part;i++){
        bool esTruncado=true;
        int numero=data[i];
        int digitos=log10(numero);
        
            if(esPrimo(numero)==true){
            
                while(numero>=10){
                    numero= numero % (int)pow(10,digitos);
                    if(esPrimo(numero)==false){
                        
                        esTruncado=false;
                    }
                    digitos--;
                }
                if(esTruncado==true){
                        truncado[cont]=data[i];
    
                        cont++;
                    }
            }

        }

            MPI_Isend(&cont,1,MPI_INT,0,0,MPI_COMM_WORLD,&request);
            MPI_Isend(&truncado[0],cont,MPI_INT,0,0,MPI_COMM_WORLD,&request);
   }
}