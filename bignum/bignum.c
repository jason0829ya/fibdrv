#include "bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Add(Big_Num *new_big, const Big_Num *b1, const Big_Num *b2)
{
	if (!b1->other_bits && !b2->other_bits) {
		Add_NN(new_big, b1, b2);
	} else if (b1->other_bits && b2->other_bits) {
		Add_BB(new_big, b1, b2);
	} else {
		if (b1->other_bits) {
			Add_BN(new_big, b1, b2);
		} else {
			Add_BN(new_big, b2, b1);
		}
	}
}

void Add_NN(Big_Num *new_big, const Big_Num *b1, const Big_Num *b2)
{
	/* overflow happens */
	if (b1->r64bit > ~b2->r64bit) {
		new_big->other_bits = malloc(sizeof(uint64_t) * 1);
		new_big->other_bits[0] = 1;
		new_big->size += 1;
	}
	new_big->r64bit = b1->r64bit + b2->r64bit;
}

void Add_BN(Big_Num *new_big, const Big_Num *big, const Big_Num *normal)
{
	/* overflow happens */
	if (big->r64bit > ~normal->r64bit) {
		unsigned overflow_end = 0;
		while (overflow_end < big->size &&
			   big->other_bits[overflow_end] == MAX_INT_64) {
			++overflow_end;
		}

		bool overflow_toMSB = false;
		if (overflow_end == big->size) {
			/* overflow to MSB of big */
			new_big->size = overflow_end + 1;
			new_big->other_bits = malloc(sizeof(uint64_t) * (overflow_end + 1));
			overflow_toMSB = true;
		} else {
			new_big->size = big->size;
			new_big->other_bits = malloc(sizeof(uint64_t) * big->size);
		}

		unsigned cnt = 0;
		/* set overflow regions */
		for (cnt; cnt < overflow_end; ++cnt)
			new_big->other_bits[cnt] = 1;

		if (overflow_toMSB) {
			new_big->other_bits[cnt] = 1;
		} else {
			for (cnt; cnt < new_big->size; ++cnt)
				new_big->other_bits[cnt] = big->other_bits[cnt];
		}
	}
	new_big->r64bit = big->r64bit + normal->r64bit;
}

void Add_BB(Big_Num *new_big, const Big_Num *b1, const Big_Num *b2)
{
	/* set b1 to be the big_num with larger size */
	if (b1->size < b2->size) {
		const Big_Num *tmp = b1;
		b1 = b2;
		b2 = tmp;
		tmp = NULL;
	}

	/* least significant 64 bits */
	bool overflow = false;
	if (b1->r64bit > ~b2->r64bit)
		overflow = true;
	new_big->r64bit = b1->r64bit + b2->r64bit;

	/* higher bits */
	const unsigned big_size = b1->size;
	const unsigned small_size = b2->size;
	new_big->other_bits = malloc(sizeof(uint64_t) * big_size);
	new_big->size = big_size;
	
	unsigned cnt = 0;
	for (cnt; cnt < small_size; ++cnt) {
		const uint64_t b1_value = b1->other_bits[cnt];
		const uint64_t b2_value = b2->other_bits[cnt];
		if (overflow) {
			if (b1_value >= ~b2_value)
				overflow = true;
			new_big->other_bits[cnt] = b1_value + b2_value + 1;
		} else {
			if (b1_value > b2_value)
				overflow = true;
			new_big->other_bits[cnt] = b1_value + b2_value;
		}
	}

	/* overflow happens in most significant region */
	if (overflow) {
		uint64_t tmp_val = new_big->r64bit;
		uint64_t tmp_arr[big_size];
		for (unsigned i = 0; i < big_size; ++i)
			tmp_arr[i] = new_big->other_bits[i];
		
		Remove_Bits(new_big);
		new_big->r64bit = tmp_val;
		new_big->size = big_size + 1;
		new_big->other_bits = malloc(sizeof(uint64_t) * (big_size + 1));
		for (unsigned i = 0; i < big_size; ++i)
			new_big->other_bits[i] = tmp_arr[i];
		new_big->other_bits[big_size] = 1;
	}
}
