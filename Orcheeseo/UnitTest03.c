// Sean Szumlanski
// COP 3502, Fall 2020

// =======================
// Orcheeseo: UnitTest03.c
// =======================
// Tests the functionality of your returnThirtyTwo() function.


#include <stdio.h>
#include "Orcheeseo.h"

// This acts as the main() function for this test case.
int unitTest(int argc, char **argv)
{
	int result = returnThirtyTwo();

	if (result == 32)
		printf("Success!\n");
	else
		printf("Oh noooo. The function returned %d. :(\n", result);

	return 0;
}
