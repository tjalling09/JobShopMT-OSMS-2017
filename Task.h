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
	Task(const int aMachine, const int aDuration);
	virtual ~Task();
	int getDuration() const;
	int getMachine() const;

private:
	int machine;
	int duration;
	int earliestStartTime;
	int lastStartTime;
};

#endif /* TASK_H_ */
