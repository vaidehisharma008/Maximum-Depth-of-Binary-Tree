// User function Template for C

#include <stdlib.h> // for malloc

int* getArray(int n) {
    // Allocate memory for n integers
    int* ptr = (int*)malloc(n * sizeof(int));
    
    // Check if memory allocation was successful
    if (ptr == NULL) {
        return NULL; // Allocation failed
    }

    // Initialize all elements to 1
    for (int i = 0; i < n; i++) {
        ptr[i] = 1;
    }

    return ptr;
}
