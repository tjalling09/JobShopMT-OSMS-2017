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
#undef max

Jobshop::Jobshop(std::string aFilename) :
		filename(aFilename), nJobs(0), nMachines(0), ifs(filename,
				std::ifstream::in)
{
	extractFirstLine(filename);
	createJobs(extractJobs(filename));
}

Jobshop::~Jobshop()
{
	// TODO Auto-generated destructor stub
}

void Jobshop::extractFirstLine(std::string filename)
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

std::vector<std::vector<std::pair<int, int>>> Jobshop::extractJobs(
		std::string fileName)
{
	std::vector<std::vector<std::pair<int, int>>> jobs;
	if (!ifs.is_open())
	{
		std::cout << "failed to open " << filename << std::endl;
	}
	else
	{
		std::vector<std::pair<int, int>> job;
		int machine, duration;
		while (ifs >> machine >> duration)
		{
			job.push_back(std::make_pair(machine, duration));
			if (ifs.peek() == '\n' || ifs.peek() == EOF)
			{
				jobs.push_back(job);
				job.clear();
			}
		}
	}
	return jobs;
}

void Jobshop::createJobs(std::vector<std::vector<std::pair<int, int>>> aJobs)
{
	for (size_t i = 0; i < aJobs.size(); i++)
	{
		Job job(i, aJobs[i]);
		jobs.push_back(job);
	}
}

Job Jobshop::getJobLeastSlackTime(std::vector<Job> jobs)
{
	return jobs.at(0);
}
