//C Program to expand a matrix by 2

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>

//dimentions of the matrix
#define n 3
#define m 6

struct indices_t
{
	int l; //l lign
	int c; //c colomn
};

int arg;
int A[n][n];
int B[m][m];

//initiate matrix
void initMatrix(int M[arg][arg]);

//print matrix
void printMatrix(int M[m][m]);

//expand matrix
void expendMatrix(int M[n][n]);

//thread function
void* functionThread(void* arg);


//Driver code 
int main(int argc, char* argv[])
{
	//initiate matrix A and B
	initMatrix(A);
	initMatrix(B);

	struct indices_t *ind;	

	//declaring threads
	pthread_t* threads;
	threads = calloc(9, sizeof(pthread_t));

	//get the number of cores
	long nbCore = sysconf(_SC_NPROCESSORS_ONLN);
	
	pthread_attr_t attr;
	cpu_set_t cpuset;

	//k indecate numbre of thread
	int k = 0;
	
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			ind = malloc(sizeof(struct indices_t));
			(*ind).l = i;
			(*ind).c = j;

			//equally distribute threads on cores
			CPU_ZERO(&cpuset);
			CPU_SET(k%(nbCore), &cpuset);
			pthread_attr_init(&attr);
			pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);

			//create thread
			if (pthread_create(&threads[k], &attr, functionThread, (void*) ind) != 0)
			{
				perror("pthread_create");
				exit(EXIT_FAILURE);
			}
		k++;
		}
	}

	//join threads	
	for (int i=0; i<9; i++)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			perror("pthread_join");
			exit(EXIT_FAILURE);
		}
	}

	printf("\tResult zoom (x2) : \n");

	expendMatrix(A);
	printf("\n");
	
	printMatrix(B);
	
	pthread_exit(threads);
	free(threads);
	
	return EXIT_SUCCESS;
}

void initMatrix(int M[arg][arg])
{
	srand(time(NULL));
	if (arg = m)
	{
		for(int i=0; i<m; i++)
		{
			for(int j=0; j<m; j++)
			{
				M[i][j] = 0;
			}
		}
	}
	if (arg = n)
	{
		for(int i=0; i<m; i++)
		{
			for(int j=0; j<m; j++)
			{
				M[i][j] = rand() % 10;
			}
		}
	}
	
}

void printMatrix(int M[m][m])
{
	for(int i=0; i<m; i++)
	{
		printf("\t");
		for(int j=0; j<m; j++)
		{
			printf("%d ",M[i][j]);
		}
		printf("\n");
	}
}
void expendMatrix(int M[n][n])
{
	for(int i=0; i<n; i++)
	{
		printf("\t");
		for(int j=0; j<n; j++)
		{
			printf("%d ",M[i][j]);
		}
		printf("\n");
	}
}

void* functionThread(void* arg)
{
	struct indices_t* ind = (struct indices_t*) arg;
	
	int lThread = (*ind).l;
	int cThread = (*ind).c;
	
	B[lThread*2][cThread*2] = A[lThread][cThread];
	B[lThread*2][cThread*2 + 1] = A[lThread][cThread];
	B[lThread*2 + 1][cThread*2] = A[lThread][cThread];
	B[lThread*2 + 1][cThread*2 + 1] = A[lThread][cThread];
	
	free(ind);
}

/* @Ilyas "Sc0Pe" NHASSE */