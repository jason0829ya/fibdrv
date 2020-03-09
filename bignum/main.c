#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

int main()
{
    Big_Num a = new_bignum("1111111111111111111");
    print_num(&a);

    return 0;
}
