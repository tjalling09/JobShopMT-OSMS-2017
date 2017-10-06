/*
 * Job.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include <iostream>
#include "Job.h"

// als "DEV" nit is uit gecomment zal elke functie "__PRETTY_FUNCTION__" printen in Job
//#define DEV

//Constructor
Job::Job(const unsigned int aId, const std::vector<Task>& aTasks) :
	id(aId), tasks(aTasks), currentTaskIndex(0), currentTime(0), startTime(0), endTime(0)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	//als printJob() niet is uitgecomment wordt de job geprint in de command line
	//printJob();
}

//Destructor
Job::~Job()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
}

//Operators
Job& Job::operator=(const Job& aJob)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	//er word gecontoleerd op id, tasks en currentTaskIndex
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
	// deze functie word gebruikt door de sort in de schedular in jobshop daar sorteren we op de slackTime
	if (getSlackTime() == aJob.getSlackTime())
	{
		return getId() < aJob.getId();
	}
	else
	{
		return getSlackTime() < aJob.getSlackTime();
	}
}

//Public functions
void Job::calculateEarliestStartTime()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	//hier kijken wat de eers mogelijke tijd is dat de volgende task kan beginnen
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

void Job::calculateLatestStartTime(unsigned long maxFinishTime)
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

void Job::increaseCurrentTaskIndex()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	// hier word de taskindex opgehoogt met 1
	if(currentTaskIndex < tasks.size())
	{
		++currentTaskIndex;
	}
}

bool Job::checkIfDone() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	//return of de job al klaar is
	return currentTaskIndex == tasks.size();
}

void Job::printJob()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	std::cout << "Job " << id << ": ";
	//hier wordt elke task in de job geprint in de comaand line
	for(Task task : tasks)
	{
		 std::cout << "[" << task.getMachine() << "," << task.getDuration() << "] ";
	}
	std::cout << std::endl;
}

//Setters
void Job::setEarliestStartTime(const unsigned long aEarliestStart)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	//hier word de de huidige task zijn earlieststarttime aan gepast
	tasks[currentTaskIndex].setEarliestStartTime(aEarliestStart);
}

void Job::setCurrentTaskIndex(const unsigned int index)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	//hier kan de current task index worden verandert
	if(currentTaskIndex <= tasks.size())
	{
		currentTaskIndex = index;
	}
}

//Getters
unsigned int Job::getId() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return id;
}

unsigned long Job::getEarliestStartTime() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return tasks[currentTaskIndex].getEarliestStartTime();
}

unsigned long Job::getEarliestFinishTime() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return tasks.back().getEarliestStartTime() + tasks.back().getDuration();
}

unsigned int Job::getCurrentTaskIndex() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return currentTaskIndex;
}

unsigned int Job::getFirstMachine() const
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

unsigned long Job::getSlackTime() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	//als er geen tasks meer zijn word zo'n groot moglijk getal ge retoneert zodat deze kan worden over schreven door de andere jobs.
	if (tasks.empty())
	{
		return INT_MAX;
	}
	else
	{
		return tasks[currentTaskIndex].getSlackTime();
	}
}

