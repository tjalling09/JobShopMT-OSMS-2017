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
	Jobshop(std::string aFilename);

	//Destructor
	virtual ~Jobshop();

private:
	//Atributes
	std::string filename;
	std::vector<Job> jobs;
	int nJobs;
	int nMachines;
	std::ifstream ifs;

	//Private functions
	void extractFirstLine(std::string filename);
	std::vector<std::vector<std::pair<int,int>>> extractJobs(std::string filename);
	void createJobs(std::vector<std::vector<std::pair<int,int>>> aJobs);
	Job getJobLeastSlackTime(std::vector<Job> jobs);
};

#endif /* JOBSHOP_H_ */
