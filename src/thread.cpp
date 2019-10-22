/*
 * thread.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#include "thread.h"

#include"pcb.h"
#include"SCHEDULE.H"
#include"lista.h"
#include"pomoc.h"
#include <stdio.h>
#include <iostream.h>

extern void lock();
extern void unlock();

Thread::Thread(StackSize stacksize, Time timeSlice) {
	lock();
	myPCB=new PCB(stacksize,timeSlice,this);
	unlock();
}

Thread::~Thread() {
	lock();
	delete myPCB;
	unlock();
}

void Thread::start(){
	lock();
	if (myPCB != 0 && myPCB->myThread != PCB::idle && myPCB->startovan == 0){
		Scheduler::put(myPCB);
		myPCB->startovan=1;
	}

	unlock();
}

void Thread::waitToComplete() {
	lock();

	myPCB->waitToComplete();

	unlock();
}

ID Thread::getId() {
	return myPCB->getId();
}

ID Thread::getRunningId() {
	return PCB::getRunningId();
}

Thread* Thread::getThreadById(ID id) {
	return PCB::getThreadById(id);
}
