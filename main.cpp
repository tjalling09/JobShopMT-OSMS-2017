/*
 * main.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include "Jobshop.h"
#include <iostream>
//als de "#define DEV" dan worden in alle functies de "__PRETTY_FUNCTION__" uitgeprint in de comandline in de main.cpp file
//#define DEV

int main(int argc, char **argv)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	if(argc > 1)
	{
		std::cout << "Start Scheduling..."<< std::endl;
		//maakt een jobshop aan met het mee gegeven bestand
		Jobshop jobshop(argv[1]);
		jobshop.schedule();
		jobshop.printJobs();

		std::cout << "Scheduling finished!"<< std::endl;
	}
	else
	{
		throw std::logic_error("Please add an input file!");
	}
	return 0;
}

/*
we hebben er voor gekozen voor alle tijd variabelen een unsigned long tegebruiken
en unsigned int voor de indexen
*/
