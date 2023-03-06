#include <iostream>
#include <omp.h>
#include <cmath>
#include <chrono>
#include <stdlib.h>
int vectorPunto(int n){
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
        int suma=0;
        #pragma omp parallel shared(suma)
        {
            #pragma omp for
            for(int i=0;i<n;i++){
            suma=suma+(a[i]*b[i]);
            }
        }
        return suma;

}
int main(){
   printf("la suma tota es: %d\n",vectorPunto(70));
   
        return 0;
}