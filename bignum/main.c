#include <stdio.h>
#include <stdlib.h>
#include "bignum.h"

int main()
{
	char dec[10] = "1024";
	char bin[100] = "0";
	dec2bin(bin, dec);
	printf("done\n%s\n", bin);
	
	
	//char a[10] = "012345678";
	//a [2] -= '0';
	//
	//printf("%d\n", a[2] & 1);
    return 0;
}
