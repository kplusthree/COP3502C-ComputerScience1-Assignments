// Sean Szumlanski
// COP 3502, Fall 2020

// =======================
// Orcheeseo: UnitTest08.c
// =======================
// Tests the functionality of your printOrcheeseo() function. This test also
// ensures that your printOrcheeseo() function doesn't modify the string it
// receives. Your printOrcheeseo() function will actually crash your program if
// you try to modify the string it receives in this particular test case.


#include <stdio.h>
#include "Orcheeseo.h"

// This acts as the main() function for this test case.
int unitTest(int argc, char **argv)
{
	char *str = "coggggggggggcogggggggggggo";

	printOrcheeseo(str);
	printf("\n");

	printf("Back in main(): \"%s\"\n", str);

	return 0;
}
