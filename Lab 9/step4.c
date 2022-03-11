#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int buffSize = atoi(argv[2]); // Obtain the buffer size from the command line
    char buffer[buffSize]; // Initialize the buffer
    FILE *fp, *fp2;
    fp = fopen(argv[1], "rb"); // Open the file to be read
    fp2 = fopen("write.txt", "wb"); // Open the file to write to
    while (fread(buffer, sizeof(buffer), 1, fp)) {
        // Reading the input file
        fputs(buffer, fp2); // Writing to the output file
    }
    fclose(fp); // Close the reading file
    fclose(fp2); // Close the writing file
}
