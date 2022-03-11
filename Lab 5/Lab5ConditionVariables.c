/* Name: Matthew Ding
 * Date: 2/3/2022
 * Title: Lab Assignment 5: Synchronization Using Semaphores, Locks, and Condition Variables
 * Purpose: The purpose of this step in the lab is to create a producer and consumer system
 * using condition variables to create mutual exclusion. The items that the producer and
 * consumer handle are arbitrary.
 */

#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define N 10
int buffer[N];
pthread_t producerThread, consumerThread;
pthread_mutex_t lock;
pthread_cond_t full, empty;
int count = 0;

void* producer();
void* consumer();

int main() {
    // Initialize the lock and condition variable
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);

    // Open the threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Close the threads. I don't think this happens because the producer and consumer have infinite loops.
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy the lock
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);
}

void* producer() {
    printf("Producer thread opened\n");
    srand(time(NULL));
    int nextItem, j, added;
    do {
        // Generate a random value
        nextItem = rand();
        
        // Enter the critical region
        pthread_mutex_lock(&lock);
        // Wait for an available place in the buffer
        while (count == N) {
            pthread_cond_wait(&empty, &lock);
        }

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
                // Increment the count of items in the buffer
                count++;
                // Indicate that an item has been added so the while loop ends
                added = 1;
            }
            j++;
        }

        // Exit the critical region
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&lock);
        sleep(1);
    } while(1);
}

void* consumer() {
    printf("Consumer thread opened\n");
    int nextItem, k, removed;
    do {
        // Enter the critical region
        pthread_mutex_lock(&lock);
        // Wait for an occupied place in the buffer
        k = 0;
        while(count == 0) {
            pthread_cond_wait(&full, &lock);
        }

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
                // Decrement the count of items in the buffer
                count--;
                // Indicate that an item has been removed so the while loop ends
                removed = 1;
            }
            k++;
        }

        // Exit the critical region
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&lock);

        // Display the value of the item that was removed from the buffer
        if (nextItem != 0) {
            printf("\t\tThe value of the item removed by consumer is %d\n", nextItem);
        } else {
            printf("\t\tNo item was removed\n");
        }
        sleep(1);
    } while(1);
}
