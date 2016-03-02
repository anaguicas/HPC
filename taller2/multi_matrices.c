#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

#define rows 3
#define cols 3
//#define tam = rows*cols*sizeof(int)

void llenar(int *m){
	
	int i,j;
	for (i = 0; i < rows; i++){
	   for (j = 0; j < cols; j++){
				m[i*cols+j]=i*cols+j;		
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

void multiplicar(int *m1, int *m2, int *m3){
	int i,j,k,aux;
	for (i = 0; i < rows; i++){
	     for (k = 0; k < cols; k++){
				aux=0;
					for (j = 0; j < rows; j++){
		    		aux += m1[i*cols+j] * m2[j*cols+j];
		   			 m3[i*cols+j] = aux; 
					}
				}
		}
}

int main(){
	
	int *m1,*m2,*m3;
  
  clock_t start_t, end_t;
	double total_t;
	
	start_t = clock();

	m1= (int *)malloc(rows*cols*sizeof(int *));		
	m2= (int *)malloc(rows*cols*sizeof(int *));
	m3= (int *)malloc(rows*cols*sizeof(int *));
	
	llenar(m1);
	llenar(m2);
	
	multiplicar(m1,m2,m3);
  
  //printf("matriz 1\n");
  //imprimir(m1);

  //printf("matriz 2\n");
  //imprimir(m2);
  
  //printf("resultado\n");
	imprimir(m3);
	
	end_t= clock();
	
	total_t= ((double)(end_t - start_t)) / CLOCKS_PER_SEC;
	
	printf("tiempo= %f", total_t);
	
	free(m1);
	free(m2);
	free(m3);
	
	return 0;
	
}
