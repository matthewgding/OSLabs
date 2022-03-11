/* Name: Matthew Ding
 * Date: 1/13/2022
 * Title: Lab 2 - Programming in C and use of System Calls
 * Description: This section of the lab involves creating two threads
 * to perform the same actions as the example program in the lab. */

#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>

void *forThread1() {
	printf("This is thread 1\n");
}

void *forThread2() {
	printf("This is thread 2\n");
}

int main(int argc, char *argv[]) {
	pthread_t thread1, thread2;
	printf("\nBefore creating threads.\n");
	pthread_create(&thread1, NULL, forThread1, NULL);
	pthread_create(&thread2, NULL, forThread2, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	return 0;
}
