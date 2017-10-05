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
	Job(const unsigned int aId, const std::vector<Task>& aTasks);

	//Destructor
	virtual ~Job();

	//Operators
	Job& operator=(const Job& aJob);
	bool operator<(const Job& aJob);

	//Public functions
	void calculateEarliestStartTime();
	void calculateLatestStartTime(unsigned long maxFinishTime);
	void increaseCurrentTaskIndex();
	void addTime(unsigned long time);
	bool checkIfDone() const;
	void printJob();

	//Setters
	void setEarliestStartTime(const unsigned long aEarliestStart);
	void setCurrentTaskIndex(const unsigned int index);

	//Getters
	unsigned int getId() const;
	unsigned long getEarliestStartTime() const;
	unsigned long getEarliestFinishTime() const;
	unsigned int getCurrentTaskIndex() const;
	unsigned int getFirstMachine() const;
	unsigned long getFirstTaskDuration() const;
	unsigned long getSlackTime() const;


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
//	void createTasks(const std::vector<unsigned int>& aTasks);
};

#endif /* JOB_H_ */
