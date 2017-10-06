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
	extractJobs(aFilename);
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
	while (!jobs.empty())
	{
		for (Job& job : jobs)
		{
			job.setEarliestStartTime(
					std::max(job.getEarliestStartTime(), currentTime));
		}

		calculateSlack();

		std::sort(jobs.begin(), jobs.end());

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

		unsigned long nextFreeMachineMoment = ULONG_MAX;
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
		std::regex numPairRegex("^\\s*(\\[0-9]+)\\s+(\\[0-9]+)\\s*"); //  to match some number, some white spaces, and some number again
		std::smatch matches;

		inputFile.open(filename);
		std::getline(inputFile, line);

		// Search for first pair (job amount and machine amount)
		if (std::regex_search(line, matches, numPairRegex))
		{
			nJobs = std::stoi(matches[1], 0, 10);
			nMachines = std::stoi(matches[2], 0, 10);

			for (size_t i = 0; i < nJobs; ++i)
			{
				getline(inputFile, line);
				if (std::regex_search(line, matches, numPairRegex)) //line contains job?
				{
					std::vector<Task> tempTasks;
					while (std::regex_search(line, matches, numPairRegex)) // read tasks
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
			std::cout << "No Job/Machine amounts found in first line of file: " << filename << std::endl;
		}
	}
	else
	{
		std::cout << "Cannot open file: " << filename << std::endl;
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

