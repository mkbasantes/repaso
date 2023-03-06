#include <iostream>
#include <mpi.h>
#include <cmath>
#include <random>
#include <chrono>
#include<thread>
using namespace std::chrono_literals;
double funcion(double x){
   double f= 4/(1+pow(x,2));
   return f;
}
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
int main(int argc, char** argv){
    
    int rank;
    int size;
    std::random_device r;
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);
  //ejercicio1
  /*
    MPI_Barrier(MPI_COMM_WORLD);
  
    std:: default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1,10);
    int mean=uniform_dist(e1);

    
    double start_time=MPI_Wtime();
    std::this_thread::sleep_for( 1000ms*mean);
    double rank_time=MPI_Wtime()-start_time;
   
    std::printf("time for work is %f seconds with  rank %d \n", rank_time,rank);

    double max_tiempo=0.0;
    MPI_Reduce(&rank_time,&max_tiempo,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if(rank==0){
        printf("tiempo max= %f ",max_tiempo);
    }*/
  
  /*
    std:: default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1,10);
     MPI_Barrier(MPI_COMM_WORLD);
       int data[10];
    if(rank==0){
       
        for(int i=0;i<10;i++){
            data[i]=uniform_dist(e1);
        }
          
       /*
        for(int i=0;i<10-1;i++){
                int aux=0;
                for(int j=i+1;j<10;j++){
                    if(data[i]>data[j]){
                        aux=data[j];
                        data[j]=data[i];
                        data[i]=aux;
                    }
                }
            }
            for (int i=0;i<10;i++) {
            printf("arreglo ordenado %d, rank= %d\n",data[i],rank);
                }*/
    //}
    /*
   MPI_Bcast(data,10,MPI_INT,0,MPI_COMM_WORLD);
   
   // if(rank!=0){
      double start_time=MPI_Wtime();  
         for(int i=0;i<10-1;i++){
            int aux=0;
            for(int j=0;j<10-1-i;j++){
                if(data[j]>data[j+1]){
                    aux=data[j];
                    data[j]=data[j+1];
                    data[j+1]=aux;
                }
            }
        }
        for (int i=0;i<10;i++) {
            printf("arreglo ordenado %d, rank= %d\n",data[i],rank);
        }
       double rank_time=MPI_Wtime()-start_time;   
    
        MPI_Barrier(MPI_COMM_WORLD);
      
      
    
       
        printf(" rank= %d\n",rank);
   // int listaTotal[10*4];
    // MPI_Gather(&data[0], 10, MPI_INT, listaTotal, 10, MPI_INT, 0, MPI_COMM_WORLD);
     double tiempo[4];
    
     MPI_Gather(&rank_time, 1, MPI_DOUBLE, tiempo, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
     
    
    if(rank==0){
        for (int i=0;i<4;i++) {
                    printf("tiempo %f\n",tiempo[i]);
                    
                }
    }
    
    double max_tiempo=0.0;
    MPI_Reduce(&rank_time,&max_tiempo,1,MPI_DOUBLE,MPI_MAX,0,MPI_COMM_WORLD); 
     
    
    if(rank==0){
        printf("tiempo max= %f ",max_tiempo);
    }
    double tiempo2[8]={1,2,3,4,5,6,7,8};
    double t[2];
    MPI_Scatter(tiempo2, 2, MPI_DOUBLE, t, 2, MPI_DOUBLE, 0, MPI_COMM_WORLD);
  //  }
  for(int i=0;i<2;i++){
    printf("tiempo2 %f\n",t[i]);
  }*/
    //ejercicio trabajo
    /*
    double a = 0;
    double b = 1;
    int n = 10000;
    double h = (b-a) / n;
    double fa = funcion(a)/2;
    double fb = funcion(b)/2;
    int* data = new int [n];
      int div = n/size;
    if(rank==0){
        
            for(int i = 0 ; i < n ; i++){
                data[i] = i + 1;
            }
    }
 int temp[div];
 MPI_Scatter(data,div,MPI_INT,temp,div,MPI_INT,0,MPI_COMM_WORLD);
  double suma = 0.0;
        for(int i = 0 ; i < div ; i++){
            
            suma = suma + funcion(a + temp[i] * h);
          
        }
        double sumaTotal=0.0;
    MPI_Reduce(&suma,&sumaTotal,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        double total=(h)*(fa+sumaTotal+fb);
        printf("resul= %f\n",total);
    }*/
    //ejercicio 3
    
    std:: default_random_engine e1(r());
    std::uniform_int_distribution<int> uniform_dist(1,100);
    int n=1000;
    int* data = new int [n];
    int div = n/size;
    if(rank==0){
       
        for(int i=0;i<n;i++){
            data[i]=uniform_dist(e1);
        }
    } 
    int temp[div];
    MPI_Scatter(data,div,MPI_INT,temp,div,MPI_INT,0,MPI_COMM_WORLD);
     int cont = 0;
        for(int i = 0 ; i < div ; i++){
            if(esPrimo(temp[i])){
                printf("primo= %d \n",temp[i]);
                     cont++;
            }
        }
        int sumaTotal=0;
         MPI_Reduce(&cont,&sumaTotal,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0){
        
        printf("resul= %d\n",sumaTotal);
    }
    MPI_Finalize(); 
    return 0;
}



 
 