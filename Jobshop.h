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
#include <fstream>
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
	std::string filename;
	std::ifstream ifs;
	unsigned int nJobs;
	std::vector<Job> jobs;
	unsigned int nMachines;
	std::map<unsigned int, unsigned long> machines;
	std::vector<Job> finishedJobs;

	//Private functions
	void extractFirstLine();
	std::vector<std::vector<unsigned int>> extractJobs();
	void createJobs(const std::vector<std::vector<unsigned int>>& aJobs);
	void calculateSlack();
	unsigned long getFreeMachineAt(const unsigned int machineId);
	void getJobLeastSlackTime(std::vector<Job>& jobs);
};

#endif /* JOBSHOP_H_ */
