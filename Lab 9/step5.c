#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// threadWrite() function for each thread to perform the reading and writing
void *threadWrite(char *argv[]) {
    int buffSize = atoi(argv[2]); // Obtain the buffer size from the command line
    char buffer[buffSize]; // Intialize the buffer
    FILE *fp, *fp2;
    fp = fopen(argv[1], "rb"); // Open the file to read
    fp2 = fopen("write.txt", "wb"); // Open the file to write to
    while (fread(buffer, sizeof(buffer), 1, fp)) {
        // Reading the input file
        fputs(buffer, fp2); // Writing to the output file
    }
    fclose(fp); // Close the reading file
    fclose(fp2); // Close the writing file
}

int main(int argc, char *argv[]) {
    int numThreads = atoi(argv[3]); // Obtain the number of threads from the command line
    pthread_t threads[numThreads]; // Initalize the thread IDs
    int i;
    for (i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, threadWrite, argv); // Open all the threads
    }
}
