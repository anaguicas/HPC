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
	
	cudaError_t error = cudaSuccess;

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
  	
  	//Asignación de memoria
	error= cudaMalloc((void **)&m1_a,(tama));
	if(error != cudaSuccess){
        	printf("Ocurrio un error reservando memoria para la matriz 1");
        	exit(0);
    	}
    	
	error=cudaMalloc((void **)&m2_a,(tama));
	if(error != cudaSuccess){
        	printf("Ocurrio un error reservando memoria para la matriz 2");
        	exit(0);
    	}
    	
	error=cudaMalloc((void **)&m3_a,(tama));
	if(error != cudaSuccess){
        	printf("Ocurrio un error reservando memoria para la matriz resultado");
        	exit(0);
    	}
    	
	start_t_GPU=clock();
	
	//Copia de datos del host al device
	error=cudaMemcpy(m1_a,m1,tama,cudaMemcpyHostToDevice);
	if(error != cudaSuccess){
        	printf("Error copiando datos de la matriz m1 a la matriz m1_a");
        	exit(0);
    	}
    	
	error=cudaMemcpy(m2_a,m2,tama,cudaMemcpyHostToDevice);
	if(error != cudaSuccess){
        	printf("Error copiando datos de la matriz m2 a la matriz m2_a");
        	exit(0);
    	}

	int blockSize=32;
	dim3 dimBlock(blockSize,blockSize,1);
  	dim3 dimGrid(ceil(cols/float(blockSize)),ceil(cols/float(blockSize)),1);

	multi_matricesDevice<<<dimGrid,dimBlock>>>(m1_a,m2_a,m3_a);

	error=cudaMemcpy(m3,m3_a,tama,cudaMemcpyDeviceToHost);	
	if(error != cudaSuccess){
        	printf("Error copiando de la matriz m3_a a la matriz m3");
        	exit(0);
    	}

	end_t_GPU=clock();
	/*---------------------------------------------------------------*/

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
