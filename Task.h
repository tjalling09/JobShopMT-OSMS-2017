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
	unsigned long getDuration() const;
	unsigned long getMachine() const;

private:
	unsigned int machine;
	unsigned long duration;
	unsigned long earliestStartTime;
	unsigned long lastStartTime;
};

#endif /* TASK_H_ */
