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
    int usage[CACHE_SIZE]; // Keep track of the iteration which a value was last used in
    int totalFaults = 0; // keeps track of the total page faults
    
    for (i = 0; i < CACHE_SIZE; i++){//initialise cache array  
         cache[i].pageno = -1;
         usage[i] = -1;
    }

    int iterationNum = 0; // Keep track of which iteration the program is on

    while (fgets(pageCache, 100, stdin)){
    	int page_num = atoi(pageCache); // Stores number read from file as an int
        int foundInCache = 0;
        // Iterate through the entire cache to try and get a hit
        for (i = 0; i < CACHE_SIZE; i++) {
            // Compare values to determine if there is a hit
            if (cache[i].pageno == page_num) {
                usage[i] = iterationNum; // Update the iteration number of the value that had a hit
                foundInCache = 1;
                break;
            }
        } 
        // If this was a miss for the given value, then insert it in the cache
        if (foundInCache == 0) {
            int j, placeHere = 0;
            // Iterate through the entire cache to find the lease recently used page
            // This is accomplished by the finding the lowest (oldest) iteration number
            for (j = 0; j < CACHE_SIZE; j++) {
                // Compare the iteration numbers to find the minimum
                if (usage[j] < usage[placeHere]) {
                    placeHere = j; // Update the iteration number to get the minimum
                }
            }
            // Swap the page number into the cache
            cache[placeHere].pageno = page_num;
            // Place the current iteration number into the page's associated location
            usage[placeHere] = iterationNum;
            // Keep track of the total number of page faults
            totalFaults++;
        }
        iterationNum++;
    }

    printf("%d Total Page Faults\n", totalFaults);
    return 0;



}
