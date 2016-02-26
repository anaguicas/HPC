#include <stdio.h>
#include <malloc.h>
#include <unistd.h> 
#include <time.h>


#define N 150000

void llenar(int *a){
	for(int i=0; i<N; i++){		
		a[i]=i;		
	}	
}


void sumar(int *a, int *b, int *c){	
	for(int i=0; i<N; i++){	
		c[i]=a[i]+b[i];	
	}	
}


void print(int *a){	
	for(int i=0; i<N; i++){	
		printf("%d\n",a[i]);	
	}
}

int main(){

	clock_t start_t,end_t;	
	clock_t start = clock();  
		
	int *a = (int*)malloc(sizeof(int)*N) ;
	int *b = (int*)malloc(sizeof(int)*N);
	int *c = (int*)malloc(sizeof(int)*N);
	
	llenar(a);
	llenar(b);
	
	start_t=clock();

	sumar(a,b,c);

	end_t=clock();
	
	//print(c);

	printf("Tiempo: %f", ((double)(end_t - start_t)) / CLOCKS_PER_SEC);
   	
}
