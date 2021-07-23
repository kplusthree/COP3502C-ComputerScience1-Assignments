// Sean Szumlanski
// COP 3502, Fall 2020

// =============================
// Orcheeseo: UnitTestLauncher.c
// =============================
// This code simply calls the unitTest() function in whatever test case is
// compiled with the program. This only works if Orcheeseo.h is set to
// re-define main() as __hidden_main__(). Otherwise, compiling this with
// Orcheeseo.h will result in two definitions of the main() function: one
// in Orcheeseo.c, and one in this file.


int unitTest(int argc, char **argv);

int main(int argc, char **argv)
{
	unitTest(argc, argv);
	return 0;
}
