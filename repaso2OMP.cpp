#include <iostream>
#include <omp.h>
#include <cmath>
#include <chrono>
#include <stdlib.h>
void multiplicacion(int n){
     srand(time(NULL));
    int a[n][n];
    int b[n][n];
    for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                a[i][j]=rand()%5+1;
                b[i][j]=rand()%5+1;
            }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
            printf( "%d  ",a[i][j]);
            
            }
            printf( "\n");
        }
        printf( "\n ----------\n");
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
            
            printf( "%d  ",b[i][j]); 
            }
            printf( "\n ");
        }
        int c[n][n];
        #pragma omp parallel shared(c)
        {
             //int tid = omp_get_thread_num();
              #pragma omp for
                for(int i=0;i<n;i++){
            
                    int cont=0;
                    for(int k=0;k<n;k++){
                        int suma=0;
                        for(int j=0;j<n;j++){
                        suma=suma + a[i][j]*b[j][k];
                        }
                    
                        c[i][cont]=suma;
                        cont++;
                    } 
                }
        }
       for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
            
            printf( "%d  ",c[i][j]); 
            }
            printf( "\n ");
        }  
    
}
int main(){
    multiplicacion(4);
        return 0;
}