/*
 * Task.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include <iostream>
#include "Task.h"

Task::Task(const unsigned int aMachine, const unsigned long aDuration) :
		machine(aMachine), duration(aDuration)
{
}

Task::~Task()
{
	// TODO Auto-generated destructor stub
}

unsigned long Task::getDuration() const
{
	return duration;
}

unsigned long Task::getMachine() const
{
	return machine;
}
