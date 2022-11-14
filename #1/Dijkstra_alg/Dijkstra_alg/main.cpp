#include <iostream>

#include "Deij_alg.h"

int main(int argc, char* argv)
{
	DEIJ deij("test5.txt");
	deij.header();

	std::cout << std::endl;
	system("pause");
	return 0;
}