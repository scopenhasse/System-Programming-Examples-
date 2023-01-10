// C Program to Calculate Factoriel using pthreads

#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sched.h>

//factoriel function for the threads
void * factorielle(void* arg)
{   
    long n = (long) arg;
    int i;
    long resulat = 1;
    for (i = 1; i <= n; i++)
    {
        resulat = resulat * i;
    }
    return (void*) resulat;
}

//Driver code
int main(int argc, char const *argv[])
{
    //get the number of cores
    long nbCores = sysconf(_SC_NPROCESSORS_ONLN);

    //declaring array of threads
    pthread_t * threads;
    threads = calloc(argc - 1,sizeof(pthread_t));
    void * results[argc - 1];

    //you need at least to entre an Argument the ./exe is considered an argument
    if (argc < 2)
    {
        printf("you need to pass at least one argument \n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < argc - 1; i++)
    {
        //create the threads
        if (pthread_create(&threads[i], NULL, factorielle, (void*) ((long)atoi(argv[i + 1]))) != 0)
        {
            printf("error in creating thread \n");
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }
    
    //join the threads
    for (int i = 0; i < argc - 1; i++)
    {
        if (pthread_join(threads[i], &results[i]) != 0)
        {
            printf("error in joining thread \n");
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < argc-1; i++)
    {
        printf("factorielle de %ld est %ld from Thread %d\n",(long)atoi(argv[i+1]), (long)results[i],i);
    }

    //if you used malloc or calloc to allocate the threads you need to free them
    free(threads);
    return 0;
}


//@by: @ILYAS "Sc0Pe" NHASSE 
