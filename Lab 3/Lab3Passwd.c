// Name: Matthew Ding
// Date: 1/20/2022
// Title: Lab Assignment 3: Pthreads and Inter-process Communication - Pipes
// This step of the lab assignment was to implement the shell command
// cat /etc/passwd | grep root. This was accomplished by taking the output of
// the cat /etc/passwd command, sesnding it to the upstream end of the pipe,
// then running grep root on the downstream end of the pipe and printing
// the output.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int thruPipe[2];
    char buff[60];
    int count;
    int i;
    pipe(thruPipe);
    if (fork() == 0) {
        close(thruPipe[0]); // Close the downstream end of the pipe
        dup2(thruPipe[1],1); // Redirect the standard out through the pipe
	execlp("cat", "cat", "/etc/passwd", 0); // Run the cat /etc/passwd command
        exit(0);
    } else if (fork() == 0) {
        dup2(thruPipe[0], 0); // Redirect standard in from the pipe
        close(thruPipe[1]); // Close the upstream end of the pipe
        execlp("grep", "grep", "root", 0); // Run the grep root command
        while ((count = read(thruPipe[0], buff, 60)) > 0) { // Print the output
            for (i = 0; i < count; ++i) {
                write(1, buff + i, 1);
                write(1, " ", 1);
            }
            printf("\n");
        }
        exit(0);
    } else {
        close(thruPipe[0]); // Close both ends of the pipe
        close(thruPipe[1]);
        wait(0);
        wait(0);
    }
    return 0;
}
