/*
 * Job.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include <iostream>
#include "Job.h"

//De "#define DEV" zorgt ervoor dat van alle functies in Job.cpp "__PRETTY_FUNCTION__" wordt uitgeprint in de comandline.
//#define DEV

//Constructor
Job::Job(const unsigned int aId, const std::vector<Task>& aTasks) :
	id(aId), tasks(aTasks), currentTaskIndex(0), currentTime(0), startTime(0), endTime(0)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	/*
	 * printJob() print van elke job alle taken uit.
	 * wordt gebruikt voor het testen.
	 */
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
	//Deze operator wordt gebruikt door de sorteren van de jobs vector in de schedular in jobshop om zo te kunnen sorteren op de slacktime.
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

	//Hier berekenen we voor elke taak de eerst mogelijke tijd dat hij kan beginnen.
	if (!tasks.empty())
	{
		for (unsigned int i = currentTaskIndex; i < tasks.size() - 1; ++i)
		{
			Task& current = tasks[i];
			Task& next = tasks[i + 1];
			next.setEarliestStartTime(current.getEarliestStartTime() + current.getDuration());
		}
	}
}

void Job::calculateLatestStartTime(unsigned long maxFinishTime)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	
	//Hier berekenen we voor elke taak de laatst mogelijke tijd (LS) dat hij kan beginnen.
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
	//Hiet wordt de taskindex met 1 opgehoogd.
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

	//Geeft terug of de job al klaar is, oftewel of de huidige taak index gelijk is aan de grootte van de taken vector.
	return currentTaskIndex == tasks.size();
}

void Job::printJob()
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	//Hier wordt elke taak van de job geprint naar de command line.
	std::cout << "Job " << id << ": ";
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

	//Hier wordt van de huidige taak zijn earliest start time aangepast
	tasks[currentTaskIndex].setEarliestStartTime(aEarliestStart);
}

void Job::setCurrentTaskIndex(const unsigned int index)
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif

	//Hier wordt de huidige taak index van een job gezet op de waarde van index.
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

unsigned int Job::getCurrentMachine() const
{
	#ifdef DEV
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	#endif
	return tasks[currentTaskIndex].getMachine();
}

unsigned long Job::getCurrentTaskDuration() const
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

	//Geeft de slack time van de huidige taak terug.
	if(currentTaskIndex < tasks.size())
	{
		return tasks[currentTaskIndex].getSlackTime();
	}
	else
	{
		return ULONG_MAX;
	}
}

