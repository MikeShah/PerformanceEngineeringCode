// Compile: gcc fib.c -o fib
// RUn with: time ./fib
#include <stdio.h>

long fib(long n){
    if(n<=1){
        return 1;
    }
    // Recursive call
    return fib(n-1) + fib(n-2);
}


int main(){

    const long NthNumberToCompute = 45;

    long fibComputation1 = fib(NthNumberToCompute);
    long fibComputation2 = fib(NthNumberToCompute);

    printf("fibComputation1: %ld\n",fibComputation1);
    printf("fibComputation2: %ld\n",fibComputation2);

    return 0;
}


