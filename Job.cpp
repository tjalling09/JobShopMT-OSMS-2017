/*
 * Job.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include <iostream>
#include "Job.h"

Job::Job(const unsigned int aId, const std::vector<unsigned int>& aTasks) :
		id(aId), currentTaskIndex(0), currentTime(0), startTime(0), endTime(0)
{
	createTasks(aTasks);
}

Job::~Job()
{
	// TODO Auto-generated destructor stub
}

unsigned int Job::calculateLeastSlackTime()
{
	return 0;
}

void Job::increaseCurrentTaskIndex()
{
}

unsigned int Job::getCurrentMachine()
{
	return 0;
}

void Job::addTime(unsigned long time)
{
}

void Job::createTasks(const std::vector<unsigned int>& aTasks)
{
	for (size_t i = 0; i < aTasks.size()-1; i++)
	{
		Task task(aTasks[i],aTasks[i+1]);
		tasks.push_back(task);
	}
}

void Job::printJob()
{
	std::cout << "Job " << id << ": ";
	for(Task task : tasks)
	{
		 std::cout << "[" << task.getMachine() << "," << task.getDuration() << "] ";
	}
	std::cout << std::endl;
}

unsigned int Job::getId() const
{
	return id;
}
