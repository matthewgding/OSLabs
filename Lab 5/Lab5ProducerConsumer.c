/* Name: Matthew Ding
 * Date: 2/3/2022
 * Title: Lab Assignment 5: Synchronization Using Semaphores, Locks, and Condition Variables
 * Purpose: The purpose of this step in the lab is to create a producer and consumer system
 * using semaphores to create mutual exclusion. The items that the producer and consumer
 * handle are arbitrary.
 */

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define N 10
int buffer[N];
pthread_t producerThread, consumerThread;
sem_t full, empty, mutex;

void* producer();
void* consumer();

int main() {
    // Initialize the semaphores
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, N);
    sem_init(&mutex, 0, 1);

    // Open the threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Close the threads. I don't think this happens because the producer and consumer have infinite loops.
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy the semaphores
    sem_destroy(&full);
    sem_destroy(&empty);
    sem_destroy(&mutex);
}

void* producer() {
    printf("Producer thread opened\n");
    srand(time(NULL));
    int nextItem, j, added;
    do {
        // Generate a random value
        nextItem = rand();
        
        // Enter the critical region
        sem_wait(&empty);
        sem_wait(&mutex);

        // Critical region
        printf("Adding a new item...\n");
        added = 0;
        j = 0;
        // Look for a location to add the new item
        while (!added && j < N) {
            // Zero locations in the buffer are available locations
            // Find the first available location and add the new item
            if (buffer[j] == 0) {
                buffer[j] = nextItem;
                // Indicate that an item has been added so the while loop ends
                added = 1;
            }
            j++;
        }

        // Exit the critical region
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);
    } while(1);
}

void* consumer() {
    printf("Consumer thread opened\n");
    int nextItem, k, removed;
    do {
        // Enter the critical region
        sem_wait(&full);
        sem_wait(&mutex);

        // Critical region
        removed = 0;
        k = 0;
        // Look for an item to remove
        while(!removed && k < N) {
            // Non-zero locations are locations where an item is currently housed
            if (buffer[k] != 0) {
                // Create a local copy of the item to dispplay
                nextItem = buffer[k];
                // Remove the item from the buffer
                buffer[k] = 0;
                // Indicate that an item has been removed so the while loop ends
                removed = 1;
            }
            k++;
        }

        // Exit the critical region
        sem_post(&mutex);
        sem_post(&empty);

        // Display the value of the item that was removed from the buffer
        if (nextItem != 0) {
            printf("\t\tThe value of the item removed by consumer is %d\n", nextItem);
        } else {
            printf("\t\tNo item was removed\n");
        }
        sleep(1);
    } while(1);
}
