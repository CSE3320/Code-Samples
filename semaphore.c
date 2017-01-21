#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */

/* prototype for thread routine */
void handler ( void *ptr );

sem_t mutex; // Mutex to guard the critical section
int counter; // Shared variable

int main()
{
    int i[2];
    pthread_t thread_a;
    pthread_t thread_b;
    
    i[0] = 0; /* argument to threads */
    i[1] = 1;
    
    sem_init(&mutex, 0, 1);      /* initialize mutex to 1 - binary semaphore */
                                 /* second param = 0 - semaphore is local */
                                 
    /* Note: you can check if thread has been successfully created by checking return value of
       pthread_create */                                 
    pthread_create (&thread_a, NULL, (void *) &handler, (void *) &i[0]);
    pthread_create (&thread_b, NULL, (void *) &handler, (void *) &i[1]);
    
    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);

    sem_destroy(&mutex); /* destroy semaphore */
                  
    exit(0);
} 

void handler ( void *ptr )
{
    int x; 
    x = *((int *) ptr);

    // Down semaphore
    sem_wait(&mutex); 


    /* START CRITICAL SECTION */
    printf("Thread %d: Now in critical region...\n", x);
    printf("Thread %d: Counter Value: %d\n", x, counter);
    printf("Thread %d: Incrementing Counter...\n", x);
    counter++;
    printf("Thread %d: New Counter Value: %d\n", x, counter);
    printf("Thread %d: Exiting critical region...\n", x);
    /* END CRITICAL SECTION */    

    // Up semaphore
    sem_post(&mutex);   
   
    pthread_exit(0); 
}
