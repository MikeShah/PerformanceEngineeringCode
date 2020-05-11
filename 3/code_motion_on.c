// gcc code_motion_on -o code_motion_on
// time ./code_motion_on
#define ITERATIONS 1000000


double approx_pi(){
    return 22.0/7.0;
}

int main(){

    double circumferences[ITERATIONS];
    double PI_times_2 = 2*approx_pi();
    for(int i=0; i < ITERATIONS; i++){
        // 2 * PI * r = circumference
        circumferences[i] = PI_times_2*i;
    }

    return 0;
}

