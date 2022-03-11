/* Name: Matthew Ding
 * Date: 1/13/2022
 * Title: Lab 2 - Programming in C and use of System Calls
 * Description: This part of the lab involves a child process forking from the parent process
 * and running the ls command. While the child process runs, the parent must wait for the child
 * to terminate before terminating itself. */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	pid_t pid;
	int i, n = atoi(argv[1]); // n microseconds to input from keyboard for delay
	printf("\nBefore forking.\n");
	pid = fork(); // Fork from parent
	if (pid == -1) {
		fprintf(stderr, "can't fork, error %d\n", errno); // Print error if fork fails
	}
	if (!pid) {
		printf("Child process\n"); // Identify as the child process
		execlp("/bin/ls", "ls", NULL); // Run the ls command
	} else {
		wait(NULL); // Wait for the child process to complete
		printf("Child complete\n"); // Acknowledge that the child process terminated
		exit(0); // Continue with parent process
	}
	return 0;
}
