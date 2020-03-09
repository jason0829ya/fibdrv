#include "bignum.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Big_Num new_bignum(const char *num)
{
    Big_Num new_num;
    size_t num_len = strlen(num);

    /* bit number of the number does not exceed 64 */
    if (num_len < 19) {
        new_num.higher = 0;
        new_num.lower = atoi(num);
    }
    /*
     * bit number of the number does exceed 64
     * Big_Num is needed !!!
     */
    else {
        new_num.lower = strtoull(num + (num_len - 18), NULL, 10);
        char *high_str = malloc(sizeof(char) * (num_len - 18));
        memcpy(high_str, num, num_len - 18);
        new_num.higher = atoi(high_str);
        free(high_str);
    }

    return new_num;
}

void print_num(const Big_Num *bignum)
{
    if (bignum->higher == 0) {
        printf("%llu ", bignum->lower);
    } else {
        printf("%llu", bignum->higher);
        printf("%llu", bignum->lower);
    }
    printf("\n");
}
