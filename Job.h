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
	Job(const int aId, const std::vector<int>& aTasks);

	//Destructor
	virtual ~Job();

	//Public functions
	int calculateLeastSlackTime();
	void increaseCurrentTaskIndex();
	int getCurrentMachine();
	void addTime(int time);
	void printJob();
	int getId() const;

private:
	//Atributes
	int id;
	std::vector<Task> tasks;
	int currentTaskIndex;
	int currentTime;
	int startTime;
	int endTime;

	//Private functions
	void createTasks(const std::vector<int>& aTasks);
};

#endif /* JOB_H_ */
