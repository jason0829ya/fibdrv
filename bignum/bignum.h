#ifndef BIG_NUM
#define BIG_NUM

#ifndef MAX_INT_64
#define MAX_INT_64 0xFFFFFFFFFFFFFFFF
#endif

typedef struct big_num {
	uint64_t r64bits;
	uint64_t *other_bits;

	/* number of extra unsigned longlong to store bits exceeding 64 */
	unsigned size; 

} Big_Num;

Big_Num new_bignum(const char *);
void add(const Big_Num *, const Big_Num *);
void print_num(const Big_Num *);

#endif
