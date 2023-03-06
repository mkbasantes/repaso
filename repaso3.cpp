#include <iostream>
#include <mpi.h>
#include <cmath>
#include <stdlib.h>
int main(int argc, char** argv){
    
    int rank;
    int size;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    srand(time(NULL));
    int n=10;
    
    int div = n/4;
    if(rank==0){
        char* nombre[n]={"milena","leonardo","dally","fabiana","gaby","karen","rut","luis","muguel","adrian"};
         for(int i=0;i<n;i++){  
            printf("lista: %s",nombre[i]);
        }
        int part=0;
        MPI_Request request;
        for(int i=1;i<4;i++){
            MPI_Isend(&nombre[part],div,MPI_CHAR,i,0,MPI_COMM_WORLD,&request);
            part+=div;
        }
        char* aux1[part-div];

         for(int i=part;i<n-1;i++){
                
                
                for(int j=0;j<n-1-i;j++){
                    if(aux1[j]>aux1[j+1]){
                        char* aux=aux1[j];
                        aux1[j]=aux1[j+1];
                        aux1[j+1]=aux;
                    }
                }
        }
        char* aux2[div];
        MPI_Irecv(aux2,div,MPI_CHAR,1,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);

         char* aux3[div];
        MPI_Irecv(aux3,div,MPI_CHAR,2,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        char* aux4[div];
        MPI_Irecv(aux4,div,MPI_CHAR,2,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);

        char* lista[n];
       
     
        for(int i=0;i<div;i++){
           lista[i]= aux2[i];
        }
         int cont=0;
        for(int i=div;i<div*2;i++){
            lista[i]=aux3[cont];
            cont++;
        }
          int cont2=0;
        for(int i=div*2;i<div*3;i++){
            lista[i]=aux4[cont2];
            cont2++;
        }
        int cont3=0;
        for(int i=div*3;i<n;i++){
            lista[i]=aux4[cont3];
            cont3++;
        }
        for(int i=0;i<n;i++){  
           
                for(int j=0;j<n-1-i;j++){
                    if(aux1[j]>aux1[j+1]){
                        char* aux=aux1[j];
                        aux1[j]=aux1[j+1];
                        aux1[j+1]=aux;
                    }
                }
        }
        printf("holi");
        for(int i=0;i<n;i++){  
            printf("lista: %s",lista[i]);
        }
        
            
    }else{
         MPI_Request request;
        char* nombre[div];
        
        MPI_Irecv(nombre,div,MPI_CHAR,0,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
            for(int i=0;i<div-1;i++){
                
             
                for(int j=0;j<div-1-i;j++){
                    if(nombre[j]>nombre[j+1]){
                         char*aux=nombre[j];
                        nombre[j]=nombre[j+1];
                        nombre[j+1]=aux;
                    }
                }
            }
            MPI_Isend(&nombre[0],div,MPI_CHAR,0,0,MPI_COMM_WORLD,&request); 
        }
    
    /*//producto punto
    int n=70;
    int div=n/size;
    if(rank==0){
        int a[n];
        int b[n];
        for(int i=0;i<n;i++){
            a[i]=rand()%5+1;
            b[i]=rand()%5+1;
        }
         printf("vectores a  : b\n");
        for(int i=0;i<n;i++){
           printf("%d  :  %d \n", a[i], b[i]);
           
        }
        MPI_Request request;
        int part=0;
        for(int i=1;i<4;i++){
            MPI_Isend(&a[part],div,MPI_INT,i,0,MPI_COMM_WORLD,&request);
             MPI_Isend(&b[part],div,MPI_INT,i,0,MPI_COMM_WORLD,&request);
            part+=div;
        }
        int suma=0;
        for(int i=part;i<n;i++){
            suma=suma+(a[i]*b[i]);
        }
        int sumapart=0;
         for(int i=1;i<4;i++){
            int suma2=0;
             MPI_Irecv(&suma2,1,MPI_INT,i,0,MPI_COMM_WORLD,&request);
            
            MPI_Wait(&request, MPI_STATUS_IGNORE);
             sumapart+=suma2;
        }
        int sumatotal=suma+sumapart;
        printf("el producto punto es: %d",sumatotal);


    }else{
        MPI_Request request;
        int a[div];
        int b[div];
        MPI_Irecv(a,div,MPI_INT,0,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        MPI_Irecv(b,div,MPI_INT,0,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request, MPI_STATUS_IGNORE);
        int suma=0;
        for(int i=0;i<div;i++){
            suma=suma+(a[i]*b[i]);
        }
        MPI_Isend(&suma,1,MPI_INT,0,0,MPI_COMM_WORLD,&request);

    }*/
    MPI_Finalize(); 
    return 0;
}