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
                
     int a[3][3];
     int b[5][3];
    // int a1[2][3];
    if(rank==0){
       for(int i=0;i<3;i++){
            for(int j=0;i<3;i++){
                a[i][j]=rand()%5+1;
            }
       }
       for(int i=0;i<3;i++){
           b[i]=a[i];
       }
       b[3]=a[0];
       b[4]=a[1];

       /*
      for(int i=0;i<2;i++){
            for(int j=0;i<3;i++){
                a1[i][j]=a[i][j];
            }
       }*/
         for(int i=0;i<5;i++){
            for(int j=0;i<3;i++){
               printf(" %d ", b[i][j]);
            }
            printf("\n")
       }
       /*
       for(int i=0;i<2;i++){
            for(int j=0;i<3;i++){
                 printf(" %d ", a1[i][j]);
            }
             printf("\n")
       }*/
        
    }      
   MPI_Bcast(b,9,MPI_INT,0,MPI_COMM_WORLD);
  
   int cont_aux = 2;
   int mult=0;
   int mult2=0;
    for (i = 0; i < 3; i++) {
       int mult = A[rank+i][i]
       int mult2= A[rank+0][cont_aux--]
    }
    int resultado = mult + mult2
    int resulT=0;
    MPI_Reduce(resultado,resulT,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        printf("resul %d",resulT);
    }
    
MPI_Finalize(); 
    return 0;
}