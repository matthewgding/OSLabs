#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int buffSize = atoi(argv[2]); // Obtain the buffer size from the command line
    char buffer[buffSize]; // Intialize the buffer
    FILE *fp;
    fp = fopen(argv[1], "rb"); // Open the file to be read
    while (fread(buffer, sizeof(buffer), 1, fp)) {
        // Reading the file
    }
    fclose(fp); // Close the file after reading
}
