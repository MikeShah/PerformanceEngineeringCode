// gcc partial_loop_unroll.c -o partial_loop_unroll

int main(){

    // We can partially unroll this loop 
    int sum =0;
    int A[4] = {1,2,3,4};

    for(int i=0; i < 4; i++){
        sum = sum + A[i];
    }
    // to...
    for(int i=0; i < 4; i+=2){
        sum = sum + A[i];
        sum = sum + A[1+1];
    }


    return 0;
}
