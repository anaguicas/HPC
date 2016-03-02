
#include<cuda.h>
#include<time.h>
#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include <unistd.h> 

#define filas 3
#define cols 3

__global__ void multiplicar(int **m1, int **m2, int **m3){
	
	int i,j,k,aux;

	int col = int i=(threadIdx.x*blockDim.x) + threadIdx.x;
	int row = int i=(threadIdx.y*blockDim.y) + threadIdx.y;

	for (i = 0; i < filas; i++){
	     for (k = 0; k < cols; k++){
		aux=0;
		for (j = 0; j < filas; j++){
		    aux += m1[i][j] * m2[j][k];
		    m3[i][k] = aux; 
			}
		}
	}
}

void llenar(int **m){
	
	int i,j;
	for (i = 0; i < filas; i++){
	   for (j = 0; j < cols; j++){
		m[i][j] = (i*10)+j;
	   }		
	}
}

void imprimir(int **m){
	int i,j;
	for (i = 0; i < filas; i++){		
		for (j = 0; j < cols; j++){
			printf("%d ",m[i][j]);
		}
		printf("\n");		
	}
}


int main(){
	int **m1;
	m1= (int **)malloc(filas*sizeof(int *));	
	
	int i;
	for (i = 0; i < filas; i++){
	     m1[i] = (int *)malloc(cols*sizeof(int));
	}
	
	int **m2= (int **)malloc(filas*sizeof(int *));
	for (i = 0; i < filas; i++){
	     m2[i] = (int *)malloc(cols*sizeof(int));
	}
	
	int **m3= (int **)malloc(filas*sizeof(int *));
	for (i = 0; i < filas; i++){
	     m3[i] = (int *)malloc(cols*sizeof(int));
	}
	
	llenar(m1);
	llenar(m2);
	
	multiplicar(m1,m2,m3);
	
	//imprimir(m2);
	imprimir(m3);
	
	return 0;
	
}
