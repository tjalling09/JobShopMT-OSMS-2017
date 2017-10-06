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
//De "#define DEV" zorgt ervoor dat van alle functies in Jobshop.cpp "__PRETTY_FUNCTION__" wordt uitgeprint in de comandline.
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
	unsigned long globalTickTime = 0; //Dit houd bij waar we op de tijdlijn zitten.

	while (!jobs.empty())
	{
		//Hier word voor elke job de earliestStartTime gezet door de huidige earliestStartTime te vergelijken met de global ticktime en daar het hoogste getal van te pakken.
		for (Job& job : jobs)
		{
			job.setEarliestStartTime(std::max(job.getEarliestStartTime(), globalTickTime));
		}
		
		unsigned long maxFinishTime = 0;
		for (Job& job : jobs) //Hier wordt van elke job de snelste finish tijd (ES) berekend en met elkaar vergeleken. maxFinishTime wordt gezet op de hoogste waarde.
		{
			job.calculateEarliestStartTime();
			maxFinishTime = std::max(maxFinishTime, job.getEarliestFinishTime());
		}

		//Hier word voor elke job de lateststarttime (LS) berekent door vanaf maxfinishTime terug te rekenen.
		for (Job& job : jobs)
		{
			job.calculateLatestStartTime(maxFinishTime);
		}

		//Hier worden alle jobs gesorteerd op basis van hun slacktime van laag naar hoog.
		std::sort(jobs.begin(), jobs.end());

		/*
		 * Dit is het moment waar de jobs daadwerkelijk gescheduled worden.
		 *
		 * 1. Er wordt gekeken of de ES van de job op dat moment kleiner is dan de global tick time.
		 *    Als de ES van een job namelijk groter zou zijn de de global tick time, betekend dat van deze job de huidige taak nog bezig is.
		 *
	     * 2. Er wordt gekeken of de machine van de huidige taak beschikbaar is.
	     *    De machines map heeft als key de machineId en als value de tijd waarop hij weer beschikbaar is.
	     *    Deze tijd moet dus kleiner of gelijk zijn aan de global tick time, anders is een andere taak dus nog bezig met deze machine.
	     *
	     * 3. In de machines map wordt dan de value (tijd wanneer weer beschikbaar) gezet op de global tick time + de duratie van de taak die wordt uitgevoerd.
	     *
		 * 4. De job heeft nu een taak afgerond dus wordt de current task index opgehoogt.
		 */
		for (auto i = jobs.begin(); i != jobs.end(); ++i)
		{
			if ((i->getEarliestStartTime() <= globalTickTime) && (getFreeMachineAt(i->getCurrentMachine()) <= globalTickTime))
			{
				machines[i->getCurrentMachine()] = globalTickTime + i->getCurrentTaskDuration();
				i->increaseCurrentTaskIndex();
			}
		}

		/*
		 * Hier wordt gekeken of er jobs klaar zijn met het uitvoeren van hun taken.
		 *
		 * 1. Zolang er nog taken in de jobs vector zitten wordt er gekeken of deze jobs klaar zijn met het uitvoeren van hun taken.
		 *
		 * 2. De jobs die klaar zijn met het uitvoeren van hun taken worden overgeplaatst naar de finishedJobs vector en uit de jobs vector verwijderd.
		 */
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

		/*
		 * Hier wordt de global tick time gezet op het eerste moment dat er weer een machine vrij is.
		 * Dat moment is namelijk het eerste moment dat er weer een taak gescheduled kan worden.
		 * Op deze manier wordt de global tick time niet onnodig opgehoogd.
		 */
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
	// Hier worden de begin- en eindtijden van elke job uitgeprint.

	/*
	 * De current task wordt voor elke job op 0 gezet. Dit doen we omdat we bij het uiteindelijke uitprinten de begin- en de eindtijd van elke job moeten uitprinten
	 * en de functie die de begintijd van een job ophaald doet dat vanaf de current task index.
	 */
	for (Job& job : finishedJobs)
	{
		job.setCurrentTaskIndex(0);
	}

	/*
	 * Hier sorteren we de vector zodat de finished jobs geordend worden op hun ids.
	 * Dit doen we m.b.v. een lambda functie.
	 */
	std::sort(finishedJobs.begin(), finishedJobs.end(),
			[](const Job& j1, const Job& j2)
			{
				return j1.getId() < j2.getId();
			});

	std::cout << "id\t" << "start\t" << "finish" << std::endl;
	for (const Job& job : finishedJobs)
	{
		std::cout << job.getId() << "\t" << job.getEarliestStartTime() << "\t" << job.getEarliestFinishTime() << std::endl;
	}
}

void Jobshop::extractJobs(const std::string& filename)
{
	//Hier wordt een ifstream aangemaakt die het bestand opend.
	std::ifstream inputFile;
	inputFile.open(filename);
	if (inputFile.is_open())
	{
		std::string line; //Dit is één regel uit het bestand.
		std::regex numPairRegex("([0-9]+)\\s+([0-9]+)"); //Bepaald op wat voor soort tekens de regex_search gaat letten.
		std::smatch matches; //Hier komen alle matches in die regex_search tegenkomt.

		std::getline(inputFile, line); //Pakt de eerste regel uit het bestand.

		if (std::regex_search(line, matches, numPairRegex)) //Hier wordt in de eerste regel gezocht naar de bovenstaand gedefinieerde tekens.
		{
			nJobs = std::stoi(matches[1]); //Aantal jobs.
			nMachines = std::stoi(matches[2]); //Aantal machines.

			//Het aantal jobs staat gelijk aan het aantal regels in het bestand.
			for (unsigned int i = 0; i < nJobs; ++i)
			{
				std::getline(inputFile, line); //Voor elke job pakken we dus een regel uit het bestand.

				std::vector<Task> tempTasks; //In deze vector worden tijdelijk de taken per job opgeslagen.

				while (std::regex_search(line, matches, numPairRegex)) //Voor elke job/regel gaan we taken uit de regel pakken.
				{
					unsigned int machineId = stoi(matches[1]); //id van de machine.
					unsigned long duration = stoul(matches[2]); //duratie van de taak.
					Task tempTask(machineId, duration); //Hier wordt een tijdelijke taak aangemaakt met bovenstaande variabelen.
					tempTasks.push_back(tempTask); //De taak worden aan de tempTasks vector toegevoegd.
					machines[machineId] = 0; //Hier wordt voor elke machine een key aangemaakt met de machineId en als value 0 voor in de machines map.
					line = matches.suffix().str();
				}
				Job tempJob(i, tempTasks); //Hier wordt een tijdelijke Job aangemaakt met de taken uit de tempTasks vector verzameld.
				jobs.push_back(tempJob); //Hier wordt bovenstaande Job toegevoegd aan het jobs (een atribuut van de klasse Jobshop).
			}
		}
		else
		{
			throw std::logic_error("No jobs/machine specified on the first line!"); //Als er geen Jobs of machine aantallen worden gespecificeerd stopt het programma en geeft een foutmelding.
		}
	}
	else
	{
		throw std::logic_error("No input file given!"); //Als er geen bestand is meegeven aan het programma stopt het programma en geeft een foutmelding.
	}
}

unsigned long Jobshop::getFreeMachineAt(const unsigned int machineId)
{
#ifdef DEV
	std::cout << __PRETTY_FUNCTION__ << std::endl;
#endif
	//Hier wordt de tijd dat een machine weer gescheduled kan worden terug gegeven op basis van het id.
	auto machine = machines.find(machineId);
	return machine->second;
}

