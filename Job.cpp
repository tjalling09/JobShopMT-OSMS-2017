/*
 * Job.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include <iostream>
#include "Job.h"

Job::Job(const int aId, const std::vector<int>& aTasks) :
		id(aId), currentTaskIndex(0), currentTime(0), startTime(0), endTime(0)
{
	createTasks(aTasks);
}

Job::~Job()
{
	// TODO Auto-generated destructor stub
}

int Job::calculateLeastSlackTime()
{
	return 0;
}

void Job::increaseCurrentTaskIndex()
{
}

int Job::getCurrentMachine()
{
	return 0;
}

void Job::addTime(int time)
{
}

void Job::createTasks(const std::vector<int>& aTasks)
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

int Job::getId() const
{
	return id;
}
