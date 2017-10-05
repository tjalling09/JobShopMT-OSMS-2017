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
#include <regex>

//#define DEV

//Constructor
Jobshop::Jobshop(const std::string& aFilename)
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	extractJobs (aFilename);
}

//Destructor
Jobshop::~Jobshop()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	// TODO Auto-generated destructor stub
}

//Public functions
void Jobshop::schedule()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	unsigned long currentTime = 0;
	while (jobsInProces())
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
//		auto job = jobs.end();
//		while (job > jobs.begin())
//		{
//
//			--job;
//			if (job->checkIfDone())
//			{
//				finishedJobs.push_back(*job);
//				jobs.erase(job);
//			}
//		}

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

void Jobshop::printJobs()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	for (Job& job : jobs)
	{
		job.setCurrentTaskIndex(0);
	}

	std::sort(jobs.begin(), jobs.end(), [](const Job& j1, const Job& j2)
	{
		return j1.getId() < j2.getId();
	});
	std::cout << "id\t" << "start\t" << "finish" << std::endl;
	for (const Job& job : jobs)
	{
		std::cout << job.getId() << "\t" << job.getEarliestStartTime() << "\t"
				<< job.getEarliestFinishTime() << std::endl;
	}
}

//Private functions
//void Jobshop::extractFirstLine()
//{
//#ifdef DEV
//	std::cout << __PRETTY_FUNCTION__ << std::endl;
//#endif
//	if (!ifs.is_open())
//	{
//		std::cout << "failed to open " << filename << std::endl;
//	}
//	else
//	{
//		ifs >> nJobs >> nMachines;
//	}
//}

//std::vector<std::vector<unsigned int>> Jobshop::extractJobs()
//{
//#ifdef DEV
//	std::cout << __PRETTY_FUNCTION__ << std::endl;
//#endif
//	std::vector<std::vector<unsigned int>> jobs;
//	if (!ifs.is_open())
//	{
//		std::cout << "failed to open " << filename << std::endl;
//	}
//	else
//	{
//		std::vector<unsigned int> job;
//		int machine, duration;
//			while(ifs.peek() != EOF)
//			{
//				ifs >> machine >> duration;
//				machines[machine] = 0;
//				job.push_back(machine);
//				job.push_back(duration);
//				if (ifs.peek() == '\n')
//				{
//					jobs.push_back(job);
//					job.clear();
//				}
//			}
//	}
//	return jobs;
//
//}

void Jobshop::extractJobs(const std::string& filename)
{
	std::ifstream source;
	std::string line;
	std::regex rNumberPair("^\\s*([0-9]+)\\s+([0-9]+)\\s*"); //  to match some number, some white spaces, and some number again
	std::smatch matches;

	source.open(filename);
	std::getline(source, line);

	// Search for first pair (job amount and machine amount)
	if (!std::regex_search(line, matches, rNumberPair))
	{
		throw std::logic_error("no jobs/machine amount found on first line");
	}

	size_t jobAmount = std::stoul(matches[1], 0, 10);
//	size_t machineAmount = std::stoul(matches[2], 0, 10);

	for (size_t i = 0; i < jobAmount; ++i)
	{
		std::vector<Task> tasks;
		for (std::getline(source, line);
				std::regex_search(line, matches, rNumberPair);
				line = matches.suffix())
		{
			// Get machineId and duration
			unsigned int machineId = std::stoul(matches[1], 0, 10);
			unsigned int duration = std::stoul(matches[2], 0, 10);

			machines[machineId] = 0;

			Task task(machineId, duration);
			tasks.push_back(task);

		}
		Job job(i, tasks);
		jobs.push_back(job);
	}
}

//void Jobshop::createJobs(const std::vector<std::vector<unsigned int>>& aJobs)
//{
//#ifdef DEV
//	std::cout << __PRETTY_FUNCTION__ << std::endl;
//#endif
//	for (unsigned int i = 0; i < aJobs.size(); i++)
//	{
//		Job job(i, aJobs[i]);
//		jobs.push_back(job);
//	}
//}

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
		job.calculateLatestStartTime(maxFinishTime);
	}
}

bool Jobshop::jobsInProces()
{
	for (Job& job : jobs)
	{
		if (job.checkIfDone() == false)
		{
			return true;
		}
	}
	return false;
}

//Getter
unsigned long Jobshop::getFreeMachineAt(const unsigned int machineId)
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	auto machine = machines.find(machineId);
	return machine->second;
}

