// Compile with: gcc -mavx2 difference.c -o difference
// Note the addition of the -mavx2 flag! 
#include <immintrin.h>
#include <stdio.h>

int main(){

  __m256 ones = _mm256_set_ps(1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0);
  __m256 count = _mm256_set_ps(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);

  __m256 result = _mm256_sub_ps(ones,count);

  float* f = (float*)&result;

  printf("%f %f %f %f %f %f %f %f\n",
          f[0],
          f[1],
          f[2],
          f[3],
          f[4],
          f[5],
          f[6],
          f[7]);

        return 0;
}