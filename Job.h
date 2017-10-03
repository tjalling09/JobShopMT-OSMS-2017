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
	void addTime(unsigned long time);
	void printJob();

	void setEarliestStartTime(const unsigned long aEarliestStart);
	void calculateEarliestStartTime();
	void CalculateLatestStartTime(unsigned long maxFinishTime);
	bool checkIfDone() const;

	unsigned int getCurrentTaskIndex() const;
	unsigned int getCurrentMachine();
	unsigned int getId() const;
	unsigned long getEarliestFinishTime() const;
	unsigned long getEarliestStartTime() const;
	unsigned short getFirstMachine() const;
	unsigned long getFirstTaskDuration() const;
	bool getDone() const;
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
	void createTasks(const std::vector<unsigned int>& aTasks);
};

#endif /* JOB_H_ */
