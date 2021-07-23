// Sean Szumlanski
// COP 3502, Fall 2020

// =======================
// Orcheeseo: UnitTest05.c
// =======================
// Tests the functionality of your printGoldfish() function.


#include <stdio.h>
#include "Orcheeseo.h"

// This acts as the main() function for this test case.
int unitTest(int argc, char **argv)
{
	int i;
	double retval;
	double expected_heights[] = {
		0.0,   // height for 0 goldfish (=> 0 layers)
		0.1,   // height for 1 goldfish (=> 1 thin layer of crumbs)
		0.25,  // height for 2 goldfish (=> 1 layer total)
		0.25,  // height for 3 goldfish (=> 1 layer total)
		0.25,  // height for 4 goldfish (=> 1 layer total)
		0.50,  // height for 5 goldfish (=> 2 layers total)
		0.50,  // height for 6 goldfish (=> 2 layers total)
		0.50,  // height for 7 goldfish (=> 2 layers total)
		0.75,  // height for 8 goldfish (=> 3 layers total)
		0.75,  // height for 9 goldfish (=> 3 layers total)
		0.75,  // height for 10 goldfish (=> 3 layers total)
		1.0    // height for 11 goldfish (=> 4 layers total)
	};

	for (i = 0; i <= 11; i++)
	{
		printf("Calling printGoldfish(%d):\n", i);
		retval = printGoldfish(i);

		printf("Return value: %.3f ", retval);

		if (retval == expected_heights[i])
			printf("(Hooray!)\n");
		else
			printf("Oh nooooo. :(\n");

		// Spacing out all the test cases for clarity.
		if (i != 11)
			printf("\n");
	}

	return 0;
}
