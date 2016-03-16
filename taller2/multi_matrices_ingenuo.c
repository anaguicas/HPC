#include<cuda.h>
#include<time.h>
#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include <unistd.h> 
#include <cuda.h>

#define rows 200
#define cols 200
#define tam = rows*cols*sizeof(int)

__global__ void multi_matricesDevice(int *m1_a, int *m2_a, int *m3_a){
	
  int i,j,aux;

  j = blockIdx.y*blockDim.y+threadIdx.y;
  i = blockIdx.x*blockDim.x+threadIdx.x;
	
	if(i<cols && j<rows){
    	aux=0;
	   for(int k=0;k<cols;k++){
		 aux+= m1_a[j*cols+k] * m2_a[k*cols+i];
		}
		m3_a[i*cols+j]=aux;
	}
}

void multi_matricesHost(int *m1, int *m2, int *m3){
	int i,j,k,aux;
	for (i = 0; i < rows; i++){
	     for (k = 0; k < cols; k++){
				aux=0;
					for (j = 0; j < rows; j++){
		    		aux += m1[i*cols+j] * m2[j*cols+k];
		   			 m3[i*cols+k] = aux; 
					}
				}
		}
}

void llenar(int *m){
	
	int i,j;
	for (i = 0; i < rows; i++){
	   for (j = 0; j < cols; j++){
			m[(i*cols)+j]=i+j;		
		}
	}
}

void comprobarResultado(int *m3_a, int *m3){
	for(int i=0; i<cols; i++){
		for (int j = 0; i < cols; j++){
			if(m3_a[(i*cols)+j] != m3[(i*cols)+j]){
				printf("Los resultados no son iguales \n");
			}			
		}
	}

	printf("Los resultados son iguales \n");
}

void imprimir(int *m){
	int i,j;
	for (i = 0; i < rows; i++){		
		for (j = 0; j < cols; j++){
			printf("%d ",m[(i*cols)+j]);
		}
		printf("\n");		
	}
}


int main(){
	int *m1,*m2,*m3;
	int *m1_a,*m2_a,*m3_a;
	int tama = rows*cols*(sizeof(int));
	
	clock_t start_t, end_t, start_t_GPU, end_t_GPU;
	double total_t, total_t_GPU;	

	/*-------------Algoritmo secuencial-----------------------------*/
	m1= (int *)malloc(tama);		
	m2= (int *)malloc(tama);
	m3= (int *)malloc(tama);			
  
  	llenar(m1);
	llenar(m2);

	start_t=clock();	
		
	multi_matricesHost(m1,m2,m3);
	//imprimir(m3);
	end_t= clock();	

  	total_t= ((double)(end_t - start_t))/CLOCKS_PER_SEC;

  	printf("tiempo algoritmo secuencial: %f \n",total_t);
  	/*---------------------------------------------------------------*/


  	/*-------------Algoritmo paralelo-----------------------------*/
	cudaMalloc((void **)&m1_a,(tama));
	cudaMalloc((void **)&m2_a,(tama));
	cudaMalloc((void **)&m3_a,(tama));

	cudaMemcpy(m1_a,m1,tama,cudaMemcpyHostToDevice);
	cudaMemcpy(m2_a,m2,tama,cudaMemcpyHostToDevice);

	int blockSize=32;
	dim3 dimBlock(blockSize,blockSize,1);
  	dim3 dimGrid(ceil(cols/float(blockSize)),ceil(cols/float(blockSize)),1);

  	start_t_GPU=clock();

	multi_matricesDevice<<<dimGrid,dimBlock>>>(m1_a,m2_a,m3_a);

	cudaMemcpy(m3,m3_a,tama,cudaMemcpyDeviceToHost);	

	end_t_GPU=clock();
	/*---------------------------------------------------------------*/

	//comprobarResultado(m3_a,m3);

	/*imprimir(m3);
	printf("\n");*/

	total_t_GPU= ((double)(end_t_GPU - start_t_GPU))/CLOCKS_PER_SEC;
	printf("tiempo algoritmo paralelo: %f",total_t_GPU);
	
	cudaFree(m1_a);
	cudaFree(m2_a);
	cudaFree(m3_a);
	free(m1);
	free(m2);
	free(m3);

	return 0;
	
}
