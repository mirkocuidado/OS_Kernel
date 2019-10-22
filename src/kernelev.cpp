/*
 * kernelev.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: OS1
 */

#include "kernelev.h"
#include "pcb.h"
#include "SCHEDULE.h"

extern void lock();
extern void unlock();
extern unsigned int lockFlag;
extern volatile int zahtevana;

KernelEv::KernelEv(IVTNo a){
	broj=a;
	val=0;
	blokirana = 0;
	owner = PCB::running;
}

KernelEv::~KernelEv(){
	lock();
	if(blokirana!=0){ //ako je blokirana postojala, mora se odblokirati

		blokirana->lucky=1;
		Scheduler::put(blokirana);

	}

	blokirana=0;
	val=0;
	unlock();
}

void KernelEv::signal(){
	lock();
	if(blokirana==0){
		val=1;
		unlock();
		return;
	}

	blokirana->lucky=1;
	Scheduler::put(blokirana);

	blokirana=0;
	val=0;
	unlock();

	//opcioni deo, ne mora
	zahtevana=1;
	asm int 8h;
}

void KernelEv::wait(){
	lock();
	if(PCB::running!=owner) {
		unlock();
		return;
	}

	if(val==1){
		val=0;
	}
	else {
		blokirana=PCB::running;
		owner->lucky=0;
		unlock();

		zahtevana=1;
		asm int 8h;
	}
}
