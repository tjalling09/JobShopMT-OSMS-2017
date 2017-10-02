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

void Job::setEarliestStart(const unsigned long aEarliestStart)
{
	tasks[currentTaskIndex].setEarliestStart(aEarliestStart);
}

void Job::calculateEarliestStartTime()
{
	if (!tasks.empty())
	{
		for (unsigned int i = currentTaskIndex; i < tasks.size() - 1; ++i)
		{
			Task& current = tasks.at(i);
			Task& next = tasks.at(i + 1);
			next.setEarliestStart(
					current.getEarliestStart() + current.getDuration());
		}
	}
}

unsigned long Job::getEarliestFinishTime() const
{
	return tasks.back().getEarliestStartTime() + tasks.back().getDuration();
}

unsigned long Job::getEarliestStartTime() const
{
	return tasks[currentTaskIndex].getEarliestStartTime();
}

unsigned short Job::getFirstMachine() const
{
	return tasks[currentTaskIndex].getMachine();
}

unsigned long Job::getFirstTaskDuration() const
{
	return tasks[currentTaskIndex].getDuration();
}

void Job::CalculateLatestStartTime(unsigned long maxFinishTime)
{
	tasks.back().setLastStartTime(maxFinishTime - tasks.back().getDuration());
	for (unsigned int i = tasks.size() - 1; i > currentTaskIndex; --i)
	{
		Task& current = tasks.at(i);
		Task& previous = tasks.at(i - 1);
		previous.setLastStartTime(current.getLastStartTime() - previous.getDuration());
	}
}

unsigned int Job::getCurrentTaskIndex() const
{
	return currentTaskIndex;
}

unsigned int Job::getCurrentTaskIndex()
{
	return currentTaskIndex;
}

bool Job::checkIfDone() const
{
	return currentTaskIndex == tasks.size();
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
