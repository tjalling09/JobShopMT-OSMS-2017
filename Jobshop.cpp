/*
 * Jobshop.cpp
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#include "Jobshop.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <regex>
//#define DEV

//Constructor
Jobshop::Jobshop(const std::string& aFilename)
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	extractJobs(aFilename);
}

//Destructor
Jobshop::~Jobshop()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
}

//Public functions
void Jobshop::schedule()
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	unsigned long globalTickTime = 0;
	while (!jobs.empty())
	{
		for (Job& job : jobs)
		{
			job.setEarliestStartTime(
					std::max(job.getEarliestStartTime(), globalTickTime));
		}

		unsigned long maxFinishTime = 0;

		for (Job& job : jobs)
		{
			job.calculateEarliestStartTime();
			maxFinishTime = std::max(maxFinishTime, job.getEarliestFinishTime());
		}

		for (Job& job : jobs)
		{
			job.calculateLatestStartTime(maxFinishTime);
		}

		std::sort(jobs.begin(), jobs.end());

		for (auto i = jobs.begin(); i != jobs.end(); ++i)
		{
			if ((i->getEarliestStartTime() <= globalTickTime)
					&& (getFreeMachineAt(i->getFirstMachine()) <= globalTickTime))
			{
				machines[i->getFirstMachine()] = globalTickTime
						+ i->getFirstTaskDuration();
				i->increaseCurrentTaskIndex();
			}
		}

		auto job = jobs.end();
		while (job > jobs.begin())
		{
			--job;
			if (job->checkIfDone())
			{
				finishedJobs.push_back(*job);
				jobs.erase(job);
			}
		}

		unsigned long nextFreeMachineMoment = INT_MAX;
		for (auto machine : machines)
		{
			if (machine.second > globalTickTime
					&& machine.second < nextFreeMachineMoment)
			{
				nextFreeMachineMoment = machine.second;
			}
		}
		globalTickTime = nextFreeMachineMoment;
	}
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
	std::cout << "\nJobs: " << nJobs << "\tMachines: " << nMachines << "\n"
			<< std::endl;
	std::cout << "id\t" << "start\t" << "finish" << std::endl;
	for (const Job& job : finishedJobs)
	{
		std::cout << job.getId() << "\t" << job.getEarliestStartTime() << "\t"
				<< job.getEarliestFinishTime() << std::endl;
	}
}

void Jobshop::extractJobs(const std::string& filename)
{
	std::ifstream inputFile;
	inputFile.open(filename);
	if (inputFile.is_open())
	{
		std::string line;
		std::regex numPairRegex("^\\s*([0-9]+)\\s+([0-9]+)\\s*");
		std::smatch matches;

		std::getline(inputFile, line);
		if (std::regex_search(line, matches, numPairRegex))
		{
			nJobs = std::stoi(matches[1]);
			nMachines = std::stoi(matches[2]);

			for (size_t i = 0; i < nJobs; ++i)
			{
				std::getline(inputFile, line);
				if (std::regex_search(line, matches, numPairRegex))
				{
					std::vector<Task> tempTasks;
					while (std::regex_search(line, matches, numPairRegex))
					{
						unsigned int machineId = stoi(matches[1]);
						unsigned long duration = stoul(matches[2]);
						Task tempTask(machineId, duration);
						tempTasks.push_back(tempTask);
						machines[machineId] = 0;
						line = matches.suffix().str();
					}
					Job tempJob(i, tempTasks);
					jobs.push_back(tempJob);
				}
			}
		}
		else
		{
			throw std::logic_error(
					"No jobs/machine specified on the first line!");
		}
	}
	else
	{
		throw std::logic_error("No input file given!");
	}
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

