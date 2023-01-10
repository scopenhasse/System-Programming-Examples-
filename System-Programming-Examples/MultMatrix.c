// C Program to multiply two matrix using pthreads

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
int MAX;

//Each thread computes single element in the resultant matrix
void * mult(void* arg);

//Function to initialize the matrix
void initMatrix(int mat[MAX][MAX], int r, int c);

//Function to print the matrix
void printMatrix(int mat[MAX][MAX], int r, int c);


//Driver code
int main()
{
	//get MAX size 
	printf("Enter the size of the matrix: ");
	scanf("%d",&MAX);

	int matA[MAX][MAX];
	int matB[MAX][MAX];
	
	
	int r1=MAX,c1=MAX,r2=MAX,c2=MAX,i,j,k;


	//initiate Matrix
	initMatrix(matA, r1, c1);
	initMatrix(matB, r2, c2);
	
	// Displaying Matrix
	printMatrix(matA, r1, c1);
	printf("\n");
	printMatrix(matB, r2, c2);
	printf("\n");
	
	int max = r1*c2;
	
	//declaring array of threads of size r1*c2	
	pthread_t *threads;
	threads = (pthread_t*)malloc(max*sizeof(pthread_t));
	
	int count = 0;
	int* data = NULL;

	for (i = 0; i < r1; i++){
		for (j = 0; j < c2; j++){
			//storing row and column elements in data
			data = (int *)malloc((20)*sizeof(int));
			data[0] = c1;
			for (k = 0; k < c1; k++)
				data[k+1] = matA[i][k];
			for (k = 0; k < r2; k++)
				data[k+c1+1] = matB[k][j];
			//creating threads
			if(pthread_create(&threads[count++], NULL,mult, (void*)(data))!=0){
				printf("Error in creating thread");
				perror("pthread_create");
				exit(EXIT_FAILURE);
			}
		}
	}

	printf("RESULTANT MATRIX IS :- \n");

	for (i = 0; i < max; i++){
		void *k;
		//Joining all threads and collecting return value
		if(pthread_join(threads[i], &k)!=0){
			printf("Error in joining thread");
			perror("pthread_join");
			exit(EXIT_FAILURE);
		}
		int *p = (int *)k;
		printf("%d ",*p);
		if ((i + 1) % c2 == 0) 
			printf("\n");
	}

return 0;
}

void * mult(void* arg){
	int *data = (int *)arg;
	int k = 0, i = 0;
	
	int x = data[0];
	for (i = 1; i <= x; i++)
		k += data[i]*data[i+x];
	
	int *p = (int*)malloc(sizeof(int));
		*p = k;
	
//Used to terminate a thread and the return value is passed as a pointer
	pthread_exit(p);
}

void initMatrix(int mat[MAX][MAX], int r, int c){
	// Generating random values in mat
	for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				mat[i][j] = rand() % 10;
}

void printMatrix(int mat[MAX][MAX], int r, int c){
	for (int i = 0; i < r; i++){
		for (int j = 0; j < c; j++)
			printf("%d ",mat[i][j]);
		printf("\n");
	}
}
/* @Ilyas "Sc0Pe" NHASSE */