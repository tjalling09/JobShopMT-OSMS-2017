/*
 * Task.h
 *
 *  Created on: 22 sep. 2017
 *      Author: mees9
 */

#ifndef TASK_H_
#define TASK_H_

class Task
{
public:
	Task(const unsigned int aMachine, const unsigned long aDuration);
	virtual ~Task();

	void setEarliestStartTime(const unsigned long aEarliestStartTime);
	void setLastStartTime(const unsigned long aLastStartTime);

	//Getters
	unsigned long getEarliestStartTime() const;
	unsigned long getLastStartTime() const;
	unsigned long getDuration() const;
	unsigned long getMachine() const;
	unsigned long getSlackTime() const;

private:
	unsigned int machine;
	unsigned long duration;
	unsigned long earliestStartTime;
	unsigned long lastStartTime;
};

#endif /* TASK_H_ */
