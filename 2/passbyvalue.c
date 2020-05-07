#include <stdio.h>

void setValue(int* x){
    *x = 9999;
    printf("x address: %p\n",(void*)&x);
}

int main(){
    int a = 6;
    setValue(&a);
    printf("a is: %d\n",a);
    printf("a address: %p\n",(void*)&a);
}
