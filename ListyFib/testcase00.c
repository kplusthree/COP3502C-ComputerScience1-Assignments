#include <limits.h>
#include <stdio.h>
#include "ListyFib.h"

int main(void)
{
	ListyInt *listy;
	Node *temp;


	// Create new ListyInt, check its internals, and then destroy it.
	listy = uintToListyInt(8746);


	listy = destroyListyInt(listy);


	// Create new ListyInt, check its internals, and then destroy it.
	//listy = uintToListyInt(981325);


	listy = destroyListyInt(listy);

	printf("%u\n", UINT_MAX);


	// Create new ListyInt, check its internals, and then destroy it.
	//listy = uintToListyInt(UINT_MAX);

	listy = destroyListyInt(listy);


	// The goal is to reach this line without any assert() statements failing.
	printf("Hooray!\n");


	return 0;
}
