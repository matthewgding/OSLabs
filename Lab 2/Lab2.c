/* Name: Matthew Ding
 * Date: 1/13/2022
 * Title: Lab 2 - Programming in C and use of System Calls
 * Description: This section of the lab involves beginning with a parent process and ending with a
 * total number of 7 processes (including the initial parent). Every process may only create either
 * two or zero child processes. */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void forChild(int childNum, int n) {
	pid_t pid, pid2;
	pid = fork(); // Fork from parent
	if (pid == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno); // Print error if fork fails
	}
	if (pid) {
		pid2 = fork(); // Fork from parent
		if (pid2 == -1) {
			fprintf(stderr, "can't fork, error %d\n", errno); // Print error if fork fails
		}
		if (!pid2) {
			printf("Child process %d.2\n", childNum); // Identify as second subchild
			usleep(n);
		}
	}
	if (!pid) {
		printf("Child process %d.1\n", childNum); // Identify as first subchild
		usleep(n);
	}
}


int main(int argc, char *argv[]) {
	pid_t pid, pid2;
	int i, j, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
	printf("\nBefore forking. \n");
	pid = fork(); // Fork from the parent
	if (pid == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno); // Print error if fork fails
	}
	if (pid) {
		printf("Parent process\n"); // Identify process as parent
		usleep(n);
		pid2 = fork(); // Fork from the parent
		if (pid2 == -1) {
			fprintf(stderr, "can't fork, error %d\n", errno); // Print error if fork fails
		}
		if (!pid2) {
			printf("Child process 2\n"); // Identify process as second child
			forChild(2, n); // Run code to create two more children
			usleep(n);
		}
	}
	if (!pid) {
		printf("Child process 1\n"); // Identify process as first child
		forChild(1, n); // Run code to create two more children
		usleep(n);
	}
	return 0;
}
