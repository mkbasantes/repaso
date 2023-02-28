#include <iostream>
#include <mpi.h>
#include <stdlib.h>
#include <cmath> 
#include <vector>
#define MAX_PUNTOS 30
#define MAX_CENTROS 3
float calcular_distancia(int x1,int y1,int z1,int x2,int y2,int z2){
    return std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
}
std::vector<int> medir_distancia(std::vector<int>datos,std::vector<int>centros,int count){
    std::vector<int>indices;
    
    for(int i=0;i<count*3;i+=3){
        float d1= calcular_distancia(datos[i],datos[i+1],datos[i+2],centros[0],centros[1],centros[2]);
     int mindist=d1;
    float d2= calcular_distancia(datos[i],datos[i+1],datos[i+2],centros[3],centros[4],centros[5]);
 if(d2<mindist){
     mindist=d2;
 }
 float d3= calcular_distancia(datos[i],datos[i+1],datos[i+2],centros[6],centros[7],centros[8]);
    if(d3<mindist){
        mindist=d3;
    }
}
}

int main(int argc, char** argv){
    int rank;
    int size;
    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int total_puntos=std::ceil(MAX_PUNTOS/(float)size);
    int tmp_puntos= MAX_PUNTOS-(size-1)+total_puntos;//30-3*8=6

    if(rank==0){
     std::vector<int> A = {6, 8, 7, 9, 7, 6, 6, 5, 5, 0, 0, 6, 5, 3, 6, 3, 8, 2, 1, 5, 8, 8, 3, 1, 6, 0, 0, 9, 0, 2, 1, 9, 0, 1, 8, 7, 7, 4, 5, 4, 7, 5, 2, 2, 0, 0, 7, 8, 3, 8, 5, 1, 9, 9, 4, 5, 1, 5, 6, 4, 7, 0, 3, 9, 1, 1, 6, 0, 8, 1, 4, 5, 8, 8, 7, 8, 9, 6, 8, 2, 7, 4, 5, 6, 3, 0, 3, 6, 7, 1};
     std::vector<int> C = {0,6,1,3,5,2,7,1,4};
        
        for(int i=1;i<size;i++){
            int index=(i-1)*total_puntos*3;

            MPI_Send(&A(index),total_puntos*3,MPI_INT,i,0,MPI_COMM_WORLD);
            //centros
            MPI_Send(&C(0),MAX_CENTROS*3,MPI_INT,i,0,MPI_COMM_WORLD);

        }
        //calcular
        std::vector<int> datos0;
        datos0.insert(datos0.begin(),A.begin()+(total_puntos+3*(size-1)),A.end());
         std::vector<int> indice0  =medir_distancia(datos0,C,);
            std::vector<int> indice1(total_puntos);
            std::vector<int> indice2(total_puntos);
            std::vector<int> indice3(total_puntos);
        MPI_Recv(indice1.data(),total_puntos,MPI_INT,1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(indice2.data(),total_puntos,MPI_INT,2,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(indice3.data(),total_puntos,MPI_INT,3,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        std::vector<int> indices;

        indices.insert(indices.end(),indice1.begin(),indice1.end());
        indices.insert(indices.end(),indice2.begin(),indice2.end());
        indices.insert(indices.end(),indice3.begin(),indice3.end());
        indices.insert(indices.end(),indice0.begin(),indice0.end());
        std::printf("centros \n");

        for(int i=0;i<MAX_CENTROS*3;i+=3){
            printf("(%d %d %d)\n ",C[i],C[i+1],C[i+2]);
        }
        std::printf("VECTORES\n ");
        int index=0;
         for(int i=0;i<MAX_PUNTOS*3;i+=3){
            printf("%2d (%d %d %d), indice =%d\n",i/3,A[i],A[i+1],A[i+2],indices[index]);
        }

    }else{
        std::vector<int> datos(total_puntos*3);
        std::vector<int> centros (MAX_CENTROS*3);
        MPI_Recv(datos.data(),total_puntos*3,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(centros.data(),MAX_CENTROS*3,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

        //calcular
        std::vector<int> distancias = medir_distancia(datos,centros,total_puntos);
        //enviar
        MPI_Send(distancias.data(),total_puntos,MPI_INT,0,0,MPI_COMM_WORLD);


    }
     MPI_Finalize(); 
    return 0;
}