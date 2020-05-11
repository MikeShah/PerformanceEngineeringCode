// 22-bit representation of date
typedef struct{
    int year: 13; // 2^13 or 8192 years [-4096-4095]
    int month: 4; // 4 bits is 2^4=16 for months
    int day: 5;   // 5 bits--months of 32 days max
} date_t;



