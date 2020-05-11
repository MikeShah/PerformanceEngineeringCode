// 96-bit representation of date                                                                                    
// 1 int is 32 bits (4 bytes)
// 3 ints thus is 3*32 = 96 bits.
typedef struct{                                                                                                     
  int year;                                                                
  int month;                                                                     
  int day;                                                                    
} date_t; 
