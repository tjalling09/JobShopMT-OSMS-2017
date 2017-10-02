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
	Job(const unsigned int aId, const std::vector<int>& aTasks);
	//Copy Constructor
	Job(const Job& aJob);

	//Destructor
	virtual ~Job();

	Job& operator=(const Job& aJob);
	bool operator<(const Job& aJob);

	//Public functions
	int calculateLeastSlackTime();
	void increaseCurrentTaskIndex();
	int getCurrentMachine();
	void addTime(int time);
	void printJob();
	int getId() const;

private:
	//Atributes
	unsigned int id;
	std::vector<Task> tasks;
	unsigned int currentTaskIndex;
	unsigned long currentTime;
	unsigned long startTime;
	unsigned long endTime;

	//Private functions
	void createTasks(const std::vector<int>& aTasks);
};

#endif /* JOB_H_ */
