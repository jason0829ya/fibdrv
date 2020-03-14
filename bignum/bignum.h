#ifndef BIG_NUM
#define BIG_NUM

#include <stdint.h>
#include <stdbool.h>

#ifndef MAX_INT_64
#define MAX_INT_64 0xFFFFFFFFFFFFFFFF
#endif

typedef struct big_num {
	uint64_t r64bit;
	uint64_t *other_bits;

	/* number of extra uint64_t to store bits exceeding 64 */
	unsigned size; 

} Big_Num;

void Add(Big_Num *, const Big_Num *, const Big_Num *);
void Add_NN(Big_Num *, const Big_Num *, const Big_Num *);
void Add_BN(Big_Num *, const Big_Num *, const Big_Num *);
void Add_BB(Big_Num *, const Big_Num *, const Big_Num *);
void Remove_Bits(Big_Num *);
void Print_Num(const Big_Num *);

#endif
