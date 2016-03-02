#include<cuda.h>
#include<time.h>
#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include <unistd.h> 

#define rows 3
#define cols 3

__global__ void multiplicar(int **m1, int **m2, int **m3){
	
	int i,j,k,aux;

	int col = int i=(threadIdx.x*blockDim.x) + threadIdx.x;
	int row = int i=(threadIdx.y*blockDim.y) + threadIdx.y;

	for (i = 0; i < rows; i++){
	     for (k = 0; k < cols; k++){
		aux=0;
		for (j = 0; j < rows; j++){
		    aux += m1[i][j] * m2[j][k];
		    m3[i][k] = aux; 
			}
		}
	}
}

void llenar(int **m){
	
	int i,j;
	for (i = 0; i < rows; i++){
	   for (j = 0; j < cols; j++){
		m[i][j] = (i*10)+j;
	   }		
	}
}

void imprimir(int **m){
	int i,j;
	for (i = 0; i < rows; i++){		
		for (j = 0; j < cols; j++){
			printf("%d ",m[i][j]);
		}
		printf("\n");		
	}
}


int main(){
	int **m1;
	int **m1_a,**m2_b,**m3_c;
	int tama = rows*cols*(sizeof(int));

	m1= (int **)malloc(rows*sizeof(int *));	
	
	int i;
	for (i = 0; i < rows; i++){
	     m1[i] = (int *)malloc(cols*sizeof(int));
	}
	
	int **m2= (int **)malloc(rows*sizeof(int *));
	for (i = 0; i < rows; i++){
	     m2[i] = (int *)malloc(cols*sizeof(int));
	}
	
	int **m3= (int **)malloc(rows*sizeof(int *));
	for (i = 0; i < rows; i++){
	     m3[i] = (int *)malloc(cols*sizeof(int));
	}
	llenar(m1);
	llenar(m2);
	
	cudaMalloc((void **)&m1_a,(tama);
	cudaMalloc((void **)&m2_a,(tama);
	cudaMalloc((void **)&m3_a,(tama);

	cudaMemcpy(m1_a,m1,sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(m2_a,m2,sizeof(int),cudaMemcpyHostToDevice);

	multiplicar<<1,10>>(m1_a,m2_a,m3_a);

	cudaMemcpy(m3,m3_a,tama,cudaMemcpyDeviceToHost);

	//multiplicar(m1,m2,m3);
	
	//imprimir(m2);
	imprimir(m3);
	
	cudaFree(m1_a);
	cudaFree(m2_a);
	cudaFree(m3_a);
	free(m1);
	free(m2);
	free(m3);

	return 0;
	
}


