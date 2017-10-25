// where_are_the_bits.c ... determine bit-field order
// COMP1521 Lab 03 Exercise
// Written by ...

#include <stdio.h>
#include <stdlib.h>

struct _bit_fields {
	unsigned int a : 1,
		        b : 8,
		        c : 23;
};

typedef union show{
	struct _bit_fields x;
	unsigned int num;
}showbit;

int main(void)
{
	showbit n;
	n.x.a = n.x.b =n.x.c = 0;
	
	printf("bit_fields byte = %d\n",sizeof(n.x));
	scanf("%u",&n.num);
	printf("a = %d\n",n.x.a);
	printf("b = %d\n",n.x.b);
	printf("c = %d\n",n.x.c);
	n.x.a = n.x.b =n.x.c = 0;
	return 0;
}


