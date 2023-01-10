// C Program to multiply two Vector using pthreads and equalizing the charge on the Cores

#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sched.h>

struct args {
    int arg1;
    int arg2;
};

//Each thread computes single Multiplication in the resultant vector
void * functionThread(void * arg){
    struct args *arguments = (struct args *) arg;
    long resulat = arguments->arg1 * arguments->arg2;
    return (void*) resulat;
}

//Function to initialize the vector
void initVector(int * vector, int size){
    // Generating random values in vector
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        vector[i] = rand() % 10;
    }
}

//Function to print the vectors
void printVector(int * vector1,int * vector2, int size){
    for (int i = 0; i < size; i++)
    {
        printf("vector1[%d] = %d \t vector2[%d] = %d \n", i, vector1[i], i, vector2[i]);
    }
}

//Driver code
int main(int argc, char const *argv[])
{ 
    //get the number of cores
    long nbCores = sysconf(_SC_NPROCESSORS_ONLN);
    
    srand(time(NULL));
    int size = rand()%10;

    int vector1[size];
    int vector2[size];

    initVector(vector1, size);
    initVector(vector2, size);

    printVector(vector1, vector2, size);

    //declaring array of threads	
    pthread_t threads[size];
    void * results[size];
    int valeurFinal = 0;

    for (int i = 0; i < size; i++)
    {
        struct args *arg = malloc(sizeof(struct args));
        arg->arg1 = vector1[i];
        arg->arg2 = vector2[i];

        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(i % nbCores, &cpuset);
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        if (pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset)!= 0)
        {
            printf("error in setting affinity \n");
            perror("pthread_setaffinity_np");
            exit(EXIT_FAILURE);
        }

        if (pthread_create(&threads[i], NULL, functionThread, (void*) arg) != 0)
        {
            printf("error in creating thread \n");
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    
    //Joining all threads and collecting return value
    for (int i = 0; i < size; i++)
    {
        if (pthread_join(threads[i], &results[i]) != 0)
        {
            printf("error in joining thread \n");
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < size; i++)
    {
        valeurFinal += (long) results[i];
    }
    printf("the final value is %d \n", valeurFinal);
        
    return 0;
}

/* @Ilyas "Sc0Pe" NHASSE */