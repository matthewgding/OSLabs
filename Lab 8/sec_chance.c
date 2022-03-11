#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {//to 
    int pageno;
} ref_page;


int main(int argc, char *argv[]){
    int CACHE_SIZE = atoi(argv[1]); // Size of Cache passed by user
    ref_page cache[CACHE_SIZE]; // Cache that stores pages
    char pageCache[100]; // Cache that holds the input from test file

    int i;
    int usage[CACHE_SIZE]; // Array to store second chance bit statuses
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < CACHE_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
         usage[i] = 0;
    }

    int counter = 0; // Counter to enable circular array

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        int foundInCache = 0;
        // Iterate through the entire cache to try and get a hit
        for (i = 0; i < CACHE_SIZE; i++) {
            // Compare values to determine if there is a hit
            if (cache[i].pageno == page_num) {
                usage[i] = 1; // If there is a hit, set the bit
                foundInCache = 1;
                break;
            }
        }
        // If this was a miss for the given input, insert it in the cache
        if (foundInCache == 0) {
            int inserted = 0;
            while(inserted != 1) {
                // Check if the entry in question has a second chance
                if (usage[counter] == 0) {
                    cache[counter].pageno = page_num; // Swap the value if it does not have a second chance
                    // Increment the counter appropriately for a circular array
                    if (counter == CACHE_SIZE - 1) {
                        counter = 0;
                    } else {
                        counter++;
                    }
                    inserted = 1;
                } else {
                    usage[counter] = 0; // Flip the bit to 0 if it gets its second chance
                    // Increment the counter appropriately for a circular array
                    if (counter == CACHE_SIZE - 1) {
                        counter = 0;
                    } else {
                        counter++;
                    }
                }
            }
            totalFaults++; // Keep track of the total number of page faults
        }
    }
    printf("%d Total Page Faults\n", totalFaults);
    return 0;
}
