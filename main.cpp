/*
 * main.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include "Jobshop.h"

int main(int argc, char **argv) {
	if (argc > 1)
	{
		Jobshop jobshop(argv[1]);
		jobshop.printJobs();
	}
}

