/*
 * Jobshop.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include "Jobshop.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <limits>
#include <array>
#include <algorithm>
#include <iterator>

Jobshop::Jobshop(const std::string& aFilename) :
		filename(aFilename), nJobs(0), nMachines(0), ifs(filename,
				std::ifstream::in)
{
	extractFirstLine();
	createJobs(extractJobs());
}

Jobshop::~Jobshop()
{
	// TODO Auto-generated destructor stub
}

void Jobshop::extractFirstLine()
{
	if (!ifs.is_open())
	{
		std::cout << "failed to open " << filename << std::endl;
	}
	else
	{
		ifs >> nJobs >> nMachines;
	}
}

std::vector<std::vector<unsigned int>> Jobshop::extractJobs()
{
	std::vector<std::vector<unsigned int>> jobs;
	if (!ifs.is_open())
	{
		std::cout << "failed to open " << filename << std::endl;
	}
	else
	{
		std::vector<unsigned int> job;
		int machine, duration;
		while (ifs >> machine >> duration)
		{
			job.push_back(machine);
			job.push_back(duration);
			if (ifs.peek() == '\n' || ifs.peek() == EOF)
			{
				jobs.push_back(job);
				job.clear();
			}
		}
	}
	return jobs;
}

void Jobshop::createJobs(
		const std::vector<std::vector<unsigned int>>& aJobs)
{
	for (unsigned int i = 0; i < aJobs.size(); i++)
	{
		Job job(i, aJobs[i]);
		jobs.push_back(job);
	}
}

void Jobshop::printJobs()
{
	for (Job job : jobs)
	{
		job.printJob();
	}
}

void Jobshop::schedule()
{
	unsigned long currentTime = 0;
	for (Job& job : jobs)
	{
		job.setEarliestStart(std::max(job.getEarliestStart(), currentTime));
	}

	calculateSlack();

	std::sort(jobs.begin(), jobs.end());

	//use of  iterator to ensure begin->end order
	for (auto i = jobs.begin(); i != jobs.end(); ++i)
	{
		if ((i->getEarliestStartTime() <= currentTime)
				&& (getFreeMachineAt(i->getFirstMachine()) <= currentTime))
		{
			machines[i->getFirstMachine()] = currentTime
					+ i->getFirstTaskDuration();
			i->increaseCurrentTaskIndex();
		}
	}

	//Move finished jobs to scheduledJobs list.
	auto i = jobs.end();
	while (i > jobs.begin())
	{
		--i;
		if (i->checkIfDone())
		{
			finishedJobs.push_back(*i);
			jobs.erase(i);
		}
	}

	//set time to next free machine moment
	unsigned long nextFreeMachineMoment = INT_MAX;
	for (auto machine : machines)
	{
		if (machine.second > currentTime && machine.second < nextFreeMachineMoment)
		{
			nextFreeMachineMoment = machine.second;
		}
	}
	currentTime = nextFreeMachineMoment;

}

void JobShop::calculateSlack()
{
	unsigned long maxFinishTime = 0;

	for (Job& job : jobs)
	{
		job.calculateEarliestStartTime();
		maxFinishTime = std::max(maxFinishTime, job.getEarliestFinishTime()); // get maximum finish time of all jobs
	}

	for (Job& job : jobs)
	{
		job.determineLatestStart(maxFinish);
	}
}

unsigned long JobShop::getFreeMachineAt(const unsigned short machineId) const
{
	return machines.at(machineID);
}


