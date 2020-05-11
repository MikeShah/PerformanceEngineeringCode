// gcc code_motion_off -o code_motion_off
// time ./code_motion_off
#define ITERATIONS 1000000


double approx_pi(){
    return 22.0/7.0;
}

int main(){

    double circumferences[ITERATIONS];
    for(int i=0; i < ITERATIONS; i++){
        // 2 * PI * r = circumference
        circumferences[i] = 2*approx_pi()*i;
    }

    return 0;
}

