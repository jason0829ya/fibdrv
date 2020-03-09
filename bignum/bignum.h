#ifndef BIG_NUM
#define BIG_NUM

#ifndef MAX_INT_64
#define MAX_INT_64 0xFFFFFFFFFFFFFFFF
#endif



typedef struct big_num {
    unsigned long long higher;
    unsigned long long lower;
} Big_Num;

Big_Num new_bignum(const char *);
Big_Num add(const Big_Num *, const Big_Num *);
void print_num(const Big_Num *);

#endif
