// gcc matrix.c -o matrix -lm 
// Note: We need to link in the math library in this example

// gcc matrix.c -O3 -o matrix -lm 

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h> // For memset
#include <sys/time.h>
#include <unistd.h>

#define N 900
float A[N][N];
float B[N][N];
float C[N][N];


int main(int argc, const char* argv[]){

    // Figure out size of our L3 cache
    // We will then try to squeeze in '3' matrices into our L3
    size_t L3_CACHE = sysconf(_SC_LEVEL3_CACHE_SIZE);

    // Figure out the size of our data type
    size_t floatSize = sizeof(double);

    printf("L3 Cache size: %zu\n",L3_CACHE);
    printf("sizeof float: %zu\n",floatSize);
    // Number of NxN matrices we can fit in a fully associative cache
    //      Size of our cache divided by the data we store
    //      Then divide the number of matrices we have (3)
    //      Then divide by 2, because we have 2 dimensions
    printf("Entries we can fit in cache per matrix: %f\n",sqrt(L3_CACHE/floatSize/3));
    
    // Initialize array
    for(int i =0; i < N; ++i){
        for(int j =0; j < N; ++j){
            A[i][j] = (float)rand() / (double)RAND_MAX;
            B[i][j] = (float)rand() / (double)RAND_MAX;
        }
    }
    
    // Use memset
    // Quickly set memory to 0 value
    memset(C,0,N*N);

    // Start our timers
    struct timeval start, end;
    gettimeofday(&start,NULL);

    // Perform multiplication
    const int stepSize = 1;
    for(int i =0; i < N; i+=stepSize){
        for(int j =0; j < N; j+=stepSize){
            for(int k =0; k < N; k+=stepSize){
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    gettimeofday(&end, NULL);
    printf("%0.6f\n", (end.tv_sec-start.tv_sec)+1e-6*(end.tv_usec-start.tv_usec));

    return 0;
}
