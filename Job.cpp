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
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	createTasks(aTasks);
	printJob();

}

Job::~Job()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	// TODO Auto-generated destructor stub
}

Job& Job::operator=(const Job& aJob)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	if (this != &aJob)
	{
		id = aJob.id;
		tasks = aJob.tasks;
		currentTaskIndex = aJob.currentTaskIndex;
	}
	return *this;
}

bool Job::operator<(const Job& aJob)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	if (getSlackTime() == aJob.getSlackTime())
	{
		return getId() < aJob.getId();
	}
	else
	{
		return getSlackTime() < aJob.getSlackTime();
	}
}

void Job::setEarliestStartTime(const unsigned long aEarliestStart)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	tasks[currentTaskIndex].setEarliestStartTime(aEarliestStart);
}

void Job::calculateEarliestStartTime()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	if (!tasks.empty())
	{
		for (unsigned int i = currentTaskIndex; i < tasks.size() - 1; ++i)
		{
			Task& current = tasks[i];
			Task& next = tasks[i + 1];
			next.setEarliestStartTime(
					current.getEarliestStartTime() + current.getDuration());
		}
	}
}

unsigned long Job::getEarliestFinishTime() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return tasks.back().getEarliestStartTime() + tasks.back().getDuration();
}

unsigned long Job::getEarliestStartTime() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return tasks[currentTaskIndex].getEarliestStartTime();
}

unsigned short Job::getFirstMachine() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return tasks[currentTaskIndex].getMachine();
}

unsigned long Job::getFirstTaskDuration() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return tasks[currentTaskIndex].getDuration();
}

void Job::CalculateLatestStartTime(unsigned long maxFinishTime)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	tasks.back().setLastStartTime(maxFinishTime - tasks.back().getDuration());
	for (unsigned int i = tasks.size() - 1; i > currentTaskIndex; --i)
	{
		Task& current = tasks[i];
		Task& previous = tasks[i - 1];
		previous.setLastStartTime(current.getLastStartTime() - previous.getDuration());
	}
}

unsigned int Job::getCurrentTaskIndex() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return currentTaskIndex;
}

bool Job::checkIfDone() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return currentTaskIndex == tasks.size();
}

void Job::addTime(unsigned long time)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
}

void Job::createTasks(const std::vector<unsigned int>& aTasks)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	for (size_t i = 0; i < aTasks.size()-1; i++)
	{
		Task task(aTasks[i],aTasks[i+1]);
		tasks.push_back(task);
	}
}

void Job::printJob()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	std::cout << "Job " << id << ": ";
	for(Task task : tasks)
	{
		 std::cout << "[" << task.getMachine() << "," << task.getDuration() << "] ";
	}
	std::cout << std::endl;
}

unsigned int Job::getId() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return id;
}

unsigned long Job::getSlackTime() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	if (tasks.empty())
	{
		return INT_MAX;
	}
	else
	{
		return tasks[currentTaskIndex].getSlackTime();
	}
}

void Job::increaseCurrentTaskIndex()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	if(currentTaskIndex < tasks.size())
	{
		++currentTaskIndex;
	}
}

void Job::setCurrentTaskIndex(const int index)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	currentTaskIndex = index;
}
