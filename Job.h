/*
 * Job.h
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#ifndef JOB_H_
#define JOB_H_

#include "Task.h"
#include <vector>
#include <utility>

class Job
{
public:
	//Constructor
	Job(const unsigned int aId, const std::vector<unsigned int>& aTasks);

	//Destructor
	virtual ~Job();

	Job& operator=(const Job& aJob);
	bool operator<(const Job& aJob);

	//Public functions
	unsigned int calculateLeastSlackTime();
	void increaseCurrentTaskIndex();
	unsigned int getCurrentMachine();
	void addTime(unsigned long time);
	void printJob();
	unsigned int getId() const;
	bool getDone() const;


private:
	//Atributes
	bool done;
	unsigned int id;
	std::vector<Task> tasks;
	unsigned int currentTaskIndex;
	unsigned long currentTime;
	unsigned long startTime;
	unsigned long endTime;

	//Private functions
	void createTasks(const std::vector<unsigned int>& aTasks);
};

#endif /* JOB_H_ */
