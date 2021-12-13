#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <syslog.h>
#include <string.h>

#define NUM_THREADS 1

typedef struct
{
    int threadIdx;
} threadParams_t;



pthread_t threads[NUM_THREADS];
threadParams_t threadParams[NUM_THREADS];


void *pThread(void *threadp)
{
	syslog(LOG_INFO, "Hello World from Thread!\n");
}


int main (int argc, char *argv[])
{
	int rc;
	int i;

	FILE *ls = popen("uname -a", "r");
	char buf[256];
	char result[256];
	char termByte = '\0';
	while (fgets(buf, sizeof(buf), ls) != 0) 
	{
		/*...*/
	}
	pclose(ls);


	//strcpy(result,   "[COURSE:1][ASSIGNMENT:1]: ");
	strcat(result,   (char*) buf);
	strcat(result,   &termByte);


	openlog ("[COURSE:1][ASSIGNMENT:1]:", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog(LOG_INFO, "%s",  result);
	syslog(LOG_INFO, "Hello World from Main!\n");


	threadParams[i].threadIdx=i;

	pthread_create(&threads[i],   // pointer to thread descriptor
				  (void *)0,     // use default attributes
				  pThread, // thread function entry point
				  (void *)&(threadParams[i]) // parameters to pass in
				  );

	pthread_join(threads[i], NULL);

	printf("\r\n Test completed!");
	
	//closelog();
	
	
	
	printf("\r\n You may use 'cat /var/log/syslog' to view the syslog output ");
	printf("\r\n");
   
   
}
