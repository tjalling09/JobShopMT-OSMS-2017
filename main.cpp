/*
 * main.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include "Jobshop.h"
#include <iostream>

#define DEV

int main(int argc, char **argv)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	if (argc > 1)
	{
		Jobshop jobshop(argv[1]);
		jobshop.printJobs();
	}
}

