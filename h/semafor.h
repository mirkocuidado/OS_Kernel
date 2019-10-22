/*
 * semafor.h
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#ifndef SEMAFOR_H_
#define SEMAFOR_H_

typedef unsigned int Time;

class KSem;

class Semaphore {
public:
	Semaphore(int init=1);
	virtual ~Semaphore();

	virtual int wait(Time maxTimeToWait);
	virtual int signal(int n=0);

	int getval() const;

private:
	KSem* myImpl;
};

#endif /* SEMAFOR_H_ */
