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
//als de "#define DEV" dan worden in alle functies de "__PRETTY_FUNCTION__" uitgeprint in de comandline in de main.cpp file
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
	//dit houd bij waar we in de tijd lijn zitten
	unsigned long globalTickTime = 0;
	while (!jobs.empty())
	{
		//hier word voor elke job de earliestStartTime gezet door de huidige te vergelijken met de global ticktime en daar word het hoogste getal van gepakt.
		for (Job& job : jobs)
		{
			job.setEarliestStartTime(
					std::max(job.getEarliestStartTime(), globalTickTime));
		}

		
		unsigned long maxFinishTime = 0;
		//hier wordt de hoogste maxfinishTime gezet 
		for (Job& job : jobs)
		{
			job.calculateEarliestStartTime();
			maxFinishTime = std::max(maxFinishTime, job.getEarliestFinishTime());
		}

		//hier word voor elke job de lateststarttime berekent door de maxfinishTime mee tegeven
		for (Job& job : jobs)
		{
			job.calculateLatestStartTime(maxFinishTime);
		}

		//hier worden alle jobs gesorteerd op basis van hun slacktime van laag naar hoog
		std::sort(jobs.begin(), jobs.end());

		//hier word er gekeken voor elke job of hij zijn task kan gaan uitvoeren door te kijken of er niet een task bezig is op het moment en als dat niet het geval is word er gekeken of de machine die de job wil gebruiken wel vrij is en niet word gebruikt door een andere job.
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

		//hier wordt er gekeken of er nog jobs over zijn
		//zoja wordt er gekeken of je job al klaar is.
		//zoja word de job overgeplaatst naar finishedJobs.
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

		//hier word de globalticktime gezet naar het eerste moment dat er weer een machine vrij is zodat er dan kan worden gekeken of er een job die ischien wilt gebruiken.
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
	// hier wordt voor elke job alle tasks uigeprint in de jobshop
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
	//hier word er de eerste mogelijke tijd terug gegeven dat de opgevraagde machine vrij is
	auto machine = machines.find(machineId);
	return machine->second;
}

