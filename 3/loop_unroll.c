// gcc loop_unroll.c -o loop_unroll

int main(){

    // We can unroll this loop 
    int sum =0;
    int A[4] = {1,2,3,4};

    for(int i=0; i < 4; i++){
        sum = sum + A[i];
    }
    // to...
    sum = A[0] + A[1] + A[2] + A[3];


    return 0;
}
