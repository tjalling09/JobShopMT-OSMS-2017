/*
 * main.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include "Jobshop.h"
#include <iostream>

//#define DEV

int main(int argc, char **argv)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	if(argc > 1)
	{
		std::cout << "Start Scheduling..."<< std::endl;

		Jobshop jobshop(argv[1]);
		jobshop.schedule();
		jobshop.printJobs();

		std::cout << "Scheduling finished!"<< std::endl;
	}else
	{
		std::cout << "Start Scheduling..."<< std::endl;

		Jobshop jobshop("Data/6x6.txt");
		jobshop.schedule();
		jobshop.printJobs();

		std::cout << "Scheduling finished!"<< std::endl;
	}
	return 0;
}

