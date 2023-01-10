//C Program that creat 3 thread : read data from input, calculate the sum of the data and display the result
//using pthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Global variables to share data between threads
int data;
int sum;

// Thread 1 function to read data from input
void* read_data(void* arg) {
    printf("Enter a number: ");
    scanf("%d", &data);
    return NULL;
}

// Thread 2 function to calculate the sum of the data
void* calculate_sum(void* arg) {
    sum += data;
    printf("calculating sum\n");
    return NULL;
}

// Thread 3 function to display the result
void* display_result(void* arg) {
    printf("Sum: %d\n", sum);
    return NULL;
}

int main(int argc, char* argv[]) {
    // Declare threads
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    // Create threads
    while (1)
    {
        pthread_create(&thread1, NULL, read_data, NULL);
        pthread_join(thread1, NULL);

        pthread_create(&thread2, NULL, calculate_sum, NULL);
        pthread_join(thread2, NULL);

        pthread_create(&thread3, NULL, display_result, NULL);
        pthread_join(thread3, NULL);
    }
    return 0;
}

//@by: @ILYAS "Sc0Pe" NHASSE 