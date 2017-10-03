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

#define DEV

Jobshop::Jobshop(const std::string& aFilename) :
		filename(aFilename), nJobs(0), nMachines(0), ifs(filename,
				std::ifstream::in)
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	extractFirstLine();
	createJobs(extractJobs());
}

Jobshop::~Jobshop()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	// TODO Auto-generated destructor stub
}

void Jobshop::extractFirstLine()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
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
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
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
			machines[machine] = 0;
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

void Jobshop::createJobs(const std::vector<std::vector<unsigned int>>& aJobs)
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	for (unsigned int i = 0; i < aJobs.size(); i++)
	{
		Job job(i, aJobs[i]);
		jobs.push_back(job);
	}
}

void Jobshop::schedule()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	unsigned long currentTime = 0;
	while (!jobs.empty())
	{
		for (Job& job : jobs)
		{
			job.setEarliestStartTime(
					std::max(job.getEarliestStartTime(), currentTime));
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
			if (machine.second > currentTime
					&& machine.second < nextFreeMachineMoment)
			{
				nextFreeMachineMoment = machine.second;
			}
		}
		currentTime = nextFreeMachineMoment;
	}
}

void Jobshop::calculateSlack()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	unsigned long maxFinishTime = 0;

	for (Job& job : jobs)
	{
		job.calculateEarliestStartTime();
		maxFinishTime = std::max(maxFinishTime, job.getEarliestFinishTime()); // get maximum finish time of all jobs
	}

	for (Job& job : jobs)
	{
		job.CalculateLatestStartTime(maxFinishTime);
	}
}

unsigned long Jobshop::getFreeMachineAt(const unsigned int machineId)
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	return machines[machineId];
}

void Jobshop::printJobs()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	for (Job& job : finishedJobs)
	{
		job.setCurrentTaskIndex(0);
	}

	std::sort(finishedJobs.begin(), finishedJobs.end(),
			[](const Job& j1, const Job& j2)
			{
				return j1.getId() < j2.getId();
			});

	for (const Job& job : finishedJobs)
	{
		std::cout << "Job "<< job.getId() << ": \t" << job.getEarliestStartTime() << "\t"
				<< job.getEarliestFinishTime() << std::endl;
	}
}

