// Compile: gcc fib_table.c -o fib_table
// RUn with: time ./fib_table
#include <stdio.h>

#define PRECOMPUTED_VALUES 100
long FIB_TABLE[PRECOMPUTED_VALUES];

long initialize_table(){
    for(long i= 0; i < PRECOMPUTED_VALUES; i++){
        // Store as a sentinal value so we know
        // it has not been precomputed
        FIB_TABLE[i] = -1;
    }
}


long fib_memo(long n){
    // lookup value first and return result
    // if it has not been previously computed
    if(FIB_TABLE[n] != -1){
        return FIB_TABLE[n];
    }
    // base case
    if(n<=1){
        FIB_TABLE[n] = 1;
        return 1;
    }
    // Recursive call
    FIB_TABLE[n] = fib_memo(n-1) + fib_memo(n-2);
    return FIB_TABLE[n];
}


int main(){

    const long NthNumberToCompute = 45;
    // Setupt our table
    initialize_table();

    long fibComputation1 = fib_memo(NthNumberToCompute);
    long fibComputation2 = fib_memo(NthNumberToCompute);
    
    printf("fibComputation1: %ld\n",fibComputation1);
    printf("fibComputation2: %ld\n",fibComputation2);

    return 0;
}


