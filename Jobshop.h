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

class Jobshop
{
public:
	//Constructor
	Jobshop(const std::string& aFilename);

	//Destructor
	virtual ~Jobshop();

	//Public functions
	void printJobs();

private:
	//Atributes
	std::string filename;
	std::vector<Job> jobs;
	int nJobs;
	int nMachines;
	std::ifstream ifs;

	//Private functions
	void extractFirstLine();
	std::vector<std::vector<int>> extractJobs();
	void createJobs(const std::vector<std::vector<int>>& aJobs);
	void getJobLeastSlackTime(std::vector<Job>& jobs);
	void schedule();
	std::vector<int> getConflictingMachines(int machines[]);
};

#endif /* JOBSHOP_H_ */
