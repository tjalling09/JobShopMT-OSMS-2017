/*
 * main.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include "Jobshop.h"
#include <iostream>
#include <chrono>
//De "#define DEV" zorgt ervoor dat van alle functies in main.cpp "__PRETTY_FUNCTION__" wordt uitgeprint in de comandline.
//#define DEV

int main(int argc, char **argv)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	if(argc > 1)
	{
		std::cout << "Start Scheduling...\n"<< std::endl;

		//Maakt een jobshop aan met het mee gegeven bestand.
		Jobshop jobshop(argv[1]);

		//Start timer.
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

		//Start het schedulen.
		jobshop.schedule();

		//Stop timer.
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

		//Print de gescheduled jobs.
		jobshop.printJobs();

		std::cout << "\nScheduling finished!\n"<< std::endl;

		//Print tijd die het programma erover deed om uit te voeren.
		std::cout << "Elapsed time: " << (std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()) /1000000.0 <<std::endl;
	}
	else
	{
		throw std::logic_error("Please add an input file!");
	}
	return 0;
}

/*
 * Tijd variabelen: unsigned long
 * indexes: 		unsigned int
*/
