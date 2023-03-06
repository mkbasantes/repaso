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
    int n=70;
    int div=n/size;
    int a[n];
    int b[n];
    if(rank==0){
        for(int i=0;i<n;i++){
            a[i]=rand()%5+1;
            b[i]=rand()%5+1;
        }
         printf("vectores a  : b\n");
        for(int i=0;i<n;i++){
           printf("%d  :  %d \n", a[i], b[i]);
           
        }
    }
    int aux[div];
    int aux2[div];
    MPI_Scatter(a,div,MPI_INT,aux,div,MPI_INT,0,MPI_COMM_WORLD);
    MPI_Scatter(b,div,MPI_INT,aux2,div,MPI_INT,0,MPI_COMM_WORLD);
    int suma=0;
    for(int i=0;i<div;i++){
        suma+=aux[i]*aux2[i];
       
    }
    
    int sumatotal=0;
    MPI_Reduce(&suma,&sumatotal,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("la suma total es: %d\n",sumatotal);
    }

             MPI_Finalize(); 
    return 0;
}