// Sean Szumlanski
// COP 3502, Fall 2020

// =======================
// Orcheeseo: UnitTest07.c
// =======================
// Tests the functionality of your printOrcheeseo() function. This test case
// also gives examples of how to write some auxiliary functions that process
// strings.


#include <stdio.h>
#include <string.h>
#include "Orcheeseo.h"


// Check whether string is valid and can be passed to printOrcheese(). We will
// never pass printOrcheeseo() a NULL pointer or a string that contains
// characters other than lowercase 'o', 'c', or 'g'.
int isValid(char *str)
{
	int i, len;

	if (str == NULL)
		return 0;

	len = strlen(str);

	for (i = 0; i < len; i++)
		if (str[i] != 'o' && str[i] != 'c' && str[i] != 'g')
			return 0;

	// If we get here, the string must be valid.
	return 1;
}

void runTest(char *str)
{
	// Check whether string is valid before passing it to printOrcheeseo().
	if (!isValid(str))
		return;		

	printf("Calling printOrcheeseo(\"%s\"):\n", str);
	printOrcheeseo(str);
	printf("[End of function output.]\n\n\n");
}

// This acts as the main() function for this test case.
int unitTest(int argc, char **argv)
{
	runTest("oggggggggggcoggggggggggo");
	runTest("oggggggggggcogggggggggggo");
	runTest("coggggggggggcogggggggggggo");
	runTest("occccgccogoooo");

	printf("Finished running test cases.\n");

	return 0;
}
