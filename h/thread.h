/*
 * thread.h
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */


#ifndef THREAD_H_
#define THREAD_H_

typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time;
const Time defaultTimeSlice = 2;
typedef int ID;

class PCB; // Kernel's implementation of a user's thread

class Thread {
public:

	void start();
	void waitToComplete();
	virtual ~Thread();

	ID getId();

	static ID getRunningId();

	static Thread* getThreadById(ID id);
protected:
	friend class PCB;
	friend class Pomoc;
	friend class Idle;

	Thread(StackSize stacksize=defaultStackSize, Time timeSlice=defaultTimeSlice);

	friend void interrupt timer(...);
	friend int main(int argc, char** argv);
	friend int userMain(int argc, char** argv);
	friend class Idle;

	virtual void run(){};

private:
	PCB* myPCB;
};

void dispatch();

#endif /* THREAD_H_ */
