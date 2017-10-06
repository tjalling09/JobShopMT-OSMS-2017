/*
 * Jobshop.h
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#ifndef JOBSHOP_H_
#define JOBSHOP_H_

#include "Job.h"
#include <vector>
#include <string>
#include <map>

class Jobshop
{
public:
	//Constructor
	Jobshop(const std::string& aFilename);

	//Destructor
	virtual ~Jobshop();

	//Public functions
	void schedule();
	void printJobs();

private:
	//Atributes
	unsigned int nJobs;
	std::vector<Job> jobs;
	std::vector<Job> finishedJobs;
	unsigned int nMachines;
	std::map<unsigned int, unsigned long> machines;

	//Private functions
	void extractFirstLine();
	void extractJobs(const std::string& filename);
	void createJobs(const std::vector<std::vector<unsigned int>>& aJobs);
	unsigned long getFreeMachineAt(const unsigned int machineId);
};

#endif /* JOBSHOP_H_ */
