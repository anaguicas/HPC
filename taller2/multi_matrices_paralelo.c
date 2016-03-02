#include<cuda.h>
#include<time.h>
#include<stdio.h>
#include <stdlib.h>
#include<malloc.h>
#include <unistd.h> 
#include <cuda.h>

#define rows 3
#define cols 3
#define tam = rows*cols*sizeof(int)

__global__ void multiplicar(int *m1_a, int *m2_a, int *m3_a){
	
	int i,j,aux;

	j=(threadIdx.x*blockDim.x) + threadIdx.x;
	i=(threadIdx.y*blockDim.y) + threadIdx.y;
	
	if(i<cols && j<rows){
		for(int k=0;k<cols;k++){
		 aux+= m1_a[i*cols+j] * m2_a[j*cols+j];
		}
		m3_a[i*cols+j]=aux;
	}
}

void llenar(int *m){
	
	int i,j;
	for (i = 0; i < rows; i++){
	   for (j = 0; j < cols; j++){
		m[i*cols+j]=i+j;		
		}
	}
}

void imprimir(int *m){
	int i,j;
	for (i = 0; i < rows; i++){		
		for (j = 0; j < cols; j++){
			printf("%d ",m[i*cols+j]);
		}
		printf("\n");		
	}
}


int main(){
	int *m1,*m2,*m3;
	int *m1_a,*m2_a,*m3_a;
	int tama = rows*cols*(sizeof(int));
	
	clock_t start_t,end_t;
	double total_t;

	m1= (int *)malloc(tama);		
	m2= (int *)malloc(tama);
	m3= (int *)malloc(tama);

	llenar(m1);
	llenar(m2);
	
	cudaMalloc((void **)&m1_a,(tama));
	cudaMalloc((void **)&m2_a,(tama));
	cudaMalloc((void **)&m3_a,(tama));

	cudaMemcpy(m1_a,m1,tama,cudaMemcpyHostToDevice);
	cudaMemcpy(m2_a,m2,tama,cudaMemcpyHostToDevice);

	int blockSize=32;
	dim3 dimBlock(blockSize,blockSize,1);
    	dim3 dimGrid(ceil(cols/float(blockSize)),ceil(cols/float(blockSize)),1);
	
	start_t=clock();

	multiplicar<<<dimGrid,dimBlock>>>(m1_a,m2_a,m3_a);

	cudaMemcpy(m3,m3_a,tama,cudaMemcpyDeviceToHost);

	//multiplicar(m1_a,m2_a,m3_a);

	end_t= clock();
	//imprimir(m2);
	imprimir(m3);
	printf("\n");
	total_t= ((double)(end_t - start_t))/CLOCKS_PER_SEC;
	printf("tiempo %f",total_t);
	
	
	
	cudaFree(m1_a);
	cudaFree(m2_a);
	cudaFree(m3_a);
	free(m1);
	free(m2);
	free(m3);

	return 0;
	
}
