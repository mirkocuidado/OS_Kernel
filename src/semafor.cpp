/*
 * semafor.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#include "semafor.h"
#include "ksem.h"
#include "pcb.h"

extern void lock();
extern void unlock();
extern unsigned int lockFlag;


Semaphore::Semaphore(int i){

	myImpl=new KSem(i, this);
}

Semaphore::~Semaphore(){
	lock();
	delete myImpl;
	unlock();
}

int Semaphore::getval() const {
	return myImpl->getval();
}

int Semaphore::wait(Time t){
	myImpl->wait(t);
}

int Semaphore::signal(int n){
	myImpl->signal(n);
}

