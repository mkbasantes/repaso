#include <iostream>
#include <mpi.h>
#include <cmath>
double funcion(double x){
   double f= 4/(1+pow(x,2));
   return f;
}
double trapecio(double a, double b,int n){
    double h= (b-a) / n;
    double fa=funcion(a)/2;
    double fb=funcion(b)/2;
    double suma=0.0;
    for(int i=1;i<n;i++){
        suma=suma+funcion(a+i*h);
    }
    suma=(h)*(fa+suma+fb);
    return suma; 
}

int main(int argc, char** argv){
    double a=0;
    double b=1;
    int n=10000000;
    double h= (b-a) / n;
    double fa=funcion(a)/2;
    double fb=funcion(b)/2;
    int rank;
    int size;
    int div=n/4;
    
    int* data = new int [n];
    MPI_Init(&argc,&argv);
   
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //printf("%f \n",trapecio(0.0,6.0,100000000));
    if(rank==0){
       
        for(int i=0;i<n;i++){
            data[i]=i+1;
        }
        int part=div-1;
        for(int i=1;i<4;i++){
            MPI_Send(&data[part],div,MPI_INT,i,0,MPI_COMM_WORLD);
            part+=div;
        }

        double suma=0.0;
         

        for(int i=0;i<div-1;i++){
             suma=suma+funcion(a+data[i]*h);
           //  printf("%d en",data[i]);
              
        }
      

        double sumaTotal=0.0;
        for(int i=1;i<4;i++){
            double sumapar=0.0;
            MPI_Recv(&sumapar,1,MPI_DOUBLE,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            sumaTotal=sumapar+sumaTotal;
        }

       double total=(h)*(fa+suma+sumaTotal+fb);
       printf("resultado= %f\n",total);

    }else{
        MPI_Recv(data,div,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        double suma=0.0;
       // printf("rank= %d desde  %d hasta %d \n",rank,data[0],data[div-1]);
        for(int i=0;i<div;i++){
            
            suma=suma+funcion(a+data[i]*h);
          
        }
        MPI_Send(&suma,1,MPI_DOUBLE,0,0,MPI_COMM_WORLD);


    }
    
    MPI_Finalize(); 
    return 0;
}