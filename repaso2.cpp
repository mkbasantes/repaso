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
    int div=30/size;
    int a[30][3];
    
    for(int i=0;i<30;i++){
        a[i][0]=rand()%5+1;
        a[i][1]=rand()%5+1;
        a[i][2]=rand()%5+1;
    }
    int c[1][3];
        c[0][0]=rand()%5+1;
        c[0][1]=rand()%5+1;
        c[0][2]=rand()%5+1;
    
    if(rank==0){
        int part=div+2;
        for(int i=1;i<4;i++){
            MPI_Send(&part,1,MPI_INT,i,0,MPI_COMM_WORLD);
            MPI_Send(&a[part][0],div*3,MPI_INT,i,0,MPI_COMM_WORLD);
            part+=div;
        }

         for(int i= 0; i<30;i++){
            printf("(%d , %d , %d) \n ",a[i][0],a[i][1],a[i][2]);
        }
         printf("c(%d , %d , %d) \n ",c[0][0],c[0][1],c[0][2]);
        for(int i=0;i<div+2;i++){
            if((double)c[0][0]/(double)a[i][0]==(double)c[0][1]/(double)a[i][1]&&(double)c[0][0]/(double)a[i][0]==(double)c[0][2]/(double)a[i][2]){
               printf("es paralelo el indice %d del vector a \n",i);
            }
        }
        for(int i=1;i<4;i++){
            int cont2=0;
           MPI_Recv(&cont2,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
           int posicion[cont2];
           MPI_Recv(posicion,cont2,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
           for(int i=0;i<cont2;i++){
            
               printf("es paralelo el indice %d del vector a \n",posicion[i]);
           }
        }
        
    }else{
        int cont=0;
       
        MPI_Recv(&cont,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(a,div*3,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int posicion[div];
        int cont2=0;
        
        for(int i=0;i<div;i++){
          
           // printf("--%f-%f-%f\n",(double)c[1][0]/(double)a[i][0],(double)c[1][1]/(double)a[i][1],(double)c[1][2]/(double)a[i][2]);
            if((double)c[0][0]/(double)a[i][0]==(double)c[0][1]/(double)a[i][1]&(double)c[0][0]/(double)a[i][0]==(double)c[0][2]/(double)a[i][2]){
                printf("%d %d %d***\n",a[i][0],a[i][1],a[i][2]);
                 printf("---%d;  %d;  %d\n",c[0][0],c[0][1],c[0][2]);
                posicion[cont2]=cont;
                cont2++;
            }
            cont++;
           
        }
        printf("%d-----\n",cont2);
         MPI_Send(&cont2,1,MPI_INT,0,0,MPI_COMM_WORLD);
         MPI_Send(&posicion[0],cont2,MPI_INT,0,0,MPI_COMM_WORLD);

    }
    //ejecicio 2
    /*
    if(rank==0){
        int n=10;
        int cont=0;
        int a[n][3];
        for(int i=0;i<n;i++){
            a[i][0]=cont++;
            a[i][1]=cont++;
            a[i][2]=cont++;
        }
        int contp=0;
        int conti=0;
        int par[n*3];
        int impar[n*3];
        for(int i= 0; i<n;i++){
            for(int j=0;j<3;j++){
                if(a[i][j]%2==0){
                    par[contp]=a[i][j];
                    contp++;
                }else{
                impar[conti]=a[i][j];
                    conti++;  
                }  
            }    
        }
        MPI_Send(&contp,1,MPI_INT,2,0,MPI_COMM_WORLD);
        MPI_Send(&par[0],contp,MPI_INT,2,0,MPI_COMM_WORLD);
        MPI_Send(&conti,1,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Send(&impar[0],conti,MPI_INT,1,0,MPI_COMM_WORLD);
         printf(" el rank 0 recibio: ninguno\n");
    }else if(rank==1){
        int conti=0;
        MPI_Recv(&conti,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int impar[conti];
        MPI_Recv(impar,conti,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      
        printf(" el rank 1 recibio:\n ");
        for(int i=0;i<conti;i++){
            printf(" %d \n",impar[i]);
        }
    }else{
        
        int contp=0;
        MPI_Recv(&contp,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        int par[contp];
        MPI_Recv(par,contp,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
       
        printf(" el rank 2 recibio:\n ");
        for(int i=0;i<contp;i++){
            printf(" %d \n",par[i]);
        }
    }*/
    /*
    int i=0;
     while(i<rank){
     
         MPI_Barrier(MPI_COMM_WORLD);
        printf("soy el rank %d sali 1\n",rank);
         i++;
      }
    
     printf("soy el rank %d hola\n",rank);
   printf("%d",i);
     while(i < size)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        printf("soy el rank %d sali 2\n",rank);
        i++;
    }*/

       //ejercicio 3
       /*
       int n=100;
int div=n/size;
int a[n][2][2];
if(rank==0){ 
        for(int i=0;i<n;i++){
            for(int j=0;j<2;j++){
                a[i][j][0]=rand()%100+1;
                a[i][j][1]=rand()%100+1;
            }
            
        }
 
    for(int i= 0; i<n;i++){
            
            printf("(%d , %d ),(%d , %d ) \n ",a[i][0][0],a[i][0][1],a[i][1][0],a[i][1][1]);
            
    }


        int part=div;
        for(int i=1;i<4;i++){
            MPI_Send(&a[part][0][0],div*4,MPI_INT,i,0,MPI_COMM_WORLD);
            part+=div;
            
        }
        
        int b[div][2];
            for(int i= 0; i<div;i++){
                b[i][0]= (a[i][0][0]+ a[i][1][0])/2;
                b[i][1]= (a[i][0][1]+ a[i][1][1])/2;
            }
        for(int i= 0; i<div;i++){
                printf("(%d , %d ) \n ",b[i][0],b[i][1]);
        }
}else{
    
   MPI_Recv(a,div*4,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    int b[div][2];
     for(int i= 0; i<div;i++){
         b[i][0]= (a[i][0][0]+ a[i][1][0])/2;
         b[i][1]= (a[i][0][1]+ a[i][1][1])/2;
    }
     for(int i= 0; i<div;i++){
            printf("(%d , %d ) %d\n ",b[i][0],b[i][1],rank);
    }
}
   */
   

    
     MPI_Finalize(); 
    return 0;
}