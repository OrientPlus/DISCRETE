#include <iostream>

#include "FW.h"

int main(int argc, char* argv)
{
	FW fw("test3.txt");
	fw.header();

	std::cout << std::endl;
	system("pause");
	return 0;
}