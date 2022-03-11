// Name: Matthew Ding
// Date: 1/27/2022
// Title: Lab 4 Assignment - Developing Multithreaded Applications
// In this lab, I had to apply multithreading to calculate the product of two matrices.
// After randomizing the values in the two input matrices, threads were used to
// calculate the dot products in parallel, making the program much faster. The size of
// the output matrix used was 1024x1024 which is a total of 1,048,576 elements.

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define M 1024
#define N 1024
#define L 1024
pthread_t threads[M];
double matrixA[M][N];
double matrixB[N][L];
double matrixC[M][L];

void fillMatrix(double firstMatrix[N][M], double secondMatrix[M][L]);
void *calculateEntry(void *);

// Main method
int main() {
    // Randomly fill two matrices using 2D arrays
    fillMatrix(matrixA, matrixB);

    // Calculate the entries of the output matrix
    static int i;
    for (i = 0; i < M; i++) {
        // Use threads to calculate the entries in parallel
        pthread_create(&threads[i], NULL, calculateEntry, (void *)i);
    }
    for (i = 0; i < M; i++) {
        // Close all the threads
        pthread_join(threads[i], NULL);
    }
    // Print out the entries of the output matrix
    int j, k;
    // Traverse the rows of the output matrix
    for (j = 0; j < M; j++) {
        // Traverse the columns of the output matrix
        for (k = 0; k < L; k++) {
            // Print out the values in the output matrix
            printf("The value at coordinate (%d, %d): %f\n", j, k, matrixC[j][k]);
        }
    } 
}

// Helper function: fillMatrix()
// Input: Two matrices represented using 2D arrays
// Purpose: Randomly fill the two matrices
void fillMatrix(double firstMatrix[M][N], double secondMatrix[N][L]) {
    int i, j;
    // Fill the first matrix
    srand(time(NULL));
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            firstMatrix[i][j] = rand();
        }
    }
    int x, y;
    // Fill the second matrix
    for (x = 0; x < N; x++) {
        for (y = 0; y < L; y++) {
            secondMatrix[x][y] = rand();
        }
    }
}

// Thread function: calculateEntry()
// Input: The thread number as an integer, three matrices represented using 2D arrays
// Purpose: Calculate the entry of a third array as a dot product of the
// row of the first array and a column of a second array. Place the calculated entry
// in the third array.
void *calculateEntry(void *arg) {
    int x, y, z;
    x = (int) arg;
    // Traverse the columns of the second array
    for (y = 0; y < L; y++) {
        double temp = 0;
        // Traverse the columns of the first array
        for (z = 0; z < N; z++) {
            // Calculate the dot product for each entry of the third array
            temp += matrixA[x][z] * matrixB[z][y];
        }
        // Insert the calculated entries into the third array
        matrixC[x][y] = temp;
    }
}







