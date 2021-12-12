#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <syslog.h>

#define NUM_THREADS 1

typedef struct
{
    int threadIdx;
} threadParams_t;



pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];


void *pThread(void *threadp)
{
	syslog(LOG_INFO, "[COURSE:X][ASSIGNMENT:1] Hello World from Thread!\n");
}


int main (int argc, char *argv[])
{
   int rc;
   int i;

   syslog(LOG_INFO, "[COURSE:X][ASSIGNMENT:1] Hello World from Main!\n");


   threadParams[i].threadIdx=i;

   pthread_create(&threads[i],   // pointer to thread descriptor
				  (void *)0,     // use default attributes
				  pThread, // thread function entry point
				  (void *)&(threadParams[i]) // parameters to pass in
                  );
   
   pthread_join(threads[i], NULL);

   printf("\r\n Test completed!");
   printf("\r\n You may use 'cat /var/log/syslog' to view the syslog output ");
   printf("\r\n");
   
   
}
