#include<cuda.h>
#include<time.h>
#include<stdio.h>
#include<malloc.h>
#include <unistd.h> 


#define N 150000000

__global__ void sumar(int *d_a,int *d_b,int *d_c){
	
	int i=(threadIdx.x*blockDim.x) + threadIdx.x;

	if(i<N){
	    d_c[i]=d_a[i]+d_b[i];	
	}	
}

void llenar(int a[]){
	for(int i=0;i<N;i++){
		a[i]=i;
	}
}

void imprimir(int c[]){
	for(int i=0;i<N;i++){
		printf("%d\n",c[i]);
}
}

int main(){
	int *a,*b,*c;
	int *d_a,*d_b,*d_c;
	clock_t start_t,end_t;
	double total_t;
	
	
	a = (int *)malloc(N * sizeof(int));	
	b = (int *)malloc(N * sizeof(int));
	c = (int *)malloc(N * sizeof(int));

	llenar(a);
	llenar(b);

	cudaMalloc((void **)&d_a,(N*sizeof(int)));
	cudaMalloc((void **)&d_b,(N*sizeof(int)));
	cudaMalloc((void **)&d_c,(N*sizeof(int)));
	
	cudaMemcpy(d_a,a,sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(d_b,b,sizeof(int),cudaMemcpyHostToDevice);
	
	int blockSize = 1024;
	int tama = N;
	int blockThread = ceil((float)(tama/blockSize));	
	
	start_t=clock();

	sumar<<<blockThread,blockSize>>>(d_a,d_b,d_c);

	cudaMemcpy(c,d_c,(N* sizeof(int)), cudaMemcpyDeviceToHost);

 	end_t= clock();

	total_t= ((double)(end_t - start_t))/CLOCKS_PER_SEC;
	printf("tiempo %f",total_t);

	imprimir(c);
	
	
	free(a);
	free(b);
	free(c);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);	
}
