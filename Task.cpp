/*
 * Task.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include <iostream>
#include "Task.h"
//De "#define DEV" zorgt ervoor dat van alle functies in Task.cpp "__PRETTY_FUNCTION__" wordt uitgeprint in de comandline.
//#define DEV

//Constructor
Task::Task(const unsigned int aMachine, const unsigned long aDuration) :
		machine(aMachine), duration(aDuration), earliestStartTime(0), lastStartTime(0)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
}

//Destructor
Task::~Task()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
}

//Setters
void Task::setEarliestStartTime(const unsigned long aEarliestStartTime)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	earliestStartTime = aEarliestStartTime;
}

void Task::setLastStartTime(const unsigned long aLastStartTime)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	lastStartTime = aLastStartTime;
}

//Getters
unsigned long Task::getEarliestStartTime() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return earliestStartTime;
}

unsigned long Task::getLastStartTime() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return lastStartTime;
}

unsigned long Task::getDuration() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return duration;
}

unsigned long Task::getMachine() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return machine;
}

unsigned long Task::getSlackTime() const
{
	//De slack time is de tijd dat een taak uitgesteld kan worden. Oftewel de laatst mogelijk begintijd - de eerst mogelijk begintijd.
	return lastStartTime - earliestStartTime;
}
