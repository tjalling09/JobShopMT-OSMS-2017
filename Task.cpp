/*
 * Task.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include <iostream>
#include "Task.h"

Task::Task(const int aMachine, const int aDuration) :
		machine(aMachine), duration(aDuration)
{
}

Task::~Task()
{
	// TODO Auto-generated destructor stub
}

int Task::getDuration() const
{
	return duration;
}

int Task::getMachine() const
{
	return machine;
}
