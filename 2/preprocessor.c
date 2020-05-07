#include <stdio.h>

#define UNIX 1
#define MESSAGE "Hello\n"

int main(){

    #if UNIX
    printf(MESSAGE);
    #else
    printf("Not unix");
    #endif

        return 0;
}
