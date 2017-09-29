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

std::vector<std::vector<int>> Jobshop::extractJobs()
{
	std::vector<std::vector<int>> jobs;
	if (!ifs.is_open())
	{
		std::cout << "failed to open " << filename << std::endl;
	}
	else
	{
		std::vector<int> job;
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
		const std::vector<std::vector<int>>& aJobs)
{
	for (size_t i = 0; i < aJobs.size(); i++)
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

void Jobshop::getJobLeastSlackTime(std::vector<Job>& jobs)
{
}

void Jobshop::schedule()
{
//	int machines[nJobs];
//
//	for (int i = 0; i < nJobs; ++i)
//	{
//		machines[i] = jobs[i].getCurrentMachine();
//	}
//	std::vector<int> conflictingMachines = getConflictingMachines(machines);
//
//	for (size_t i = 0; i < conflictingMachines.size(); ++i)
//	{
//		if()
//		for (size_t j = 0; j < machines; ++j)
//		{
//			if (machines[j] == conflictingMachines[i])
//			{
//				jobs[j].calculateLeastSlackTime();
//			}
//		}
//
//	}

}
std::vector<int> Jobshop::getConflictingMachines(int machines[])
{
}