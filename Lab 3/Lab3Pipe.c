// Name: Matthew Ding
// Date: 1/20/2022
// Title: Lab Assignment 3: Pthreads and Inter-process Communication - Pipes
// This step of the lab assignment uses a pipe to pass a message from a producer
// to a consumer. It is concerned with communication rather than running a
// system call or shell command. The methods applied were similar to previous
// steps in the lab assignment.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int thruPipe[2];
    char buff[60];
    int count;
    int i;
    pipe(thruPipe);
    if (fork() == 0) {
        close(thruPipe[0]); // Close the downstream end of the pipe
        printf("This message is from the producer -- read by the consumer."); // Message to communicate
        dup2(thruPipe[1], 1); // Redirect standard out through the pipe
        // I tried to use the open() function to pass a text file as the message, but I was unable to
        // get it to work.
        // Details: open() function was generally successful, file descriptor was properly assigned to
        // the variable inputMsgDesc, redirecting inputMsgDesc through the pipe with dup2 didn't have
        // any errors when compiling or during runtime, the downstream end of the pipe printed nothing
        // int inputMsgDesc = open("message.txt", O_RDONLY);
        // dup2(thruPipe[1], inputMsgDesc);
        exit(0);
    } else if (fork() == 0) {
        close(thruPipe[1]); // Close the upstream end of the pipe
        while ((count = read(thruPipe[0], buff, 60)) > 0) { // Print out the message from the producer
            for (i = 0; i < count; ++i) {
                write(1, buff + i, 1);
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
