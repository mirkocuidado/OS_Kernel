/*
 * pcb.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#include "pcb.h"
#include "thread.h"
#include "lista.h"
#include "SCHEDULE.H"
#include <conio.h>
#include <iostream.h>

extern volatile int zahtevana;
extern void lock();
extern void unlock();
extern unsigned int lockFlag;

ID PCB::IDD=1;

Lista* PCB::sve=new Lista();

PCB* PCB::PCBmain=0;
PCB* PCB::running=0;

#ifndef BCC_BLOCK_IGNORE
PCB::PCB( StackSize ss,Time kvantt, Thread* t) {

	id=++IDD;

	myThread=t;
	kvant=kvantt;

	flegic=0;
	VREME=-1;

	if(ss>=65535){
		size=defaultStackSize;
	}
	else{
		size=ss;
	}

	size/=sizeof(unsigned);

	stack=new unsigned[size];

	stack[size-1]=0x200;
	stack[size-2]=FP_SEG(&(wrapper));
	stack[size-3]=FP_OFF(&(wrapper));
	sp_off=FP_OFF(stack+size-12);
	sp_seg=FP_SEG(stack+size-12);
	bp=FP_OFF(stack+size-12);


	startovan=0;
	zavrsio=0;
	lucky=1;

	blokirane=new Lista();  // niti koje cekaju da se ova nit zavrsi

	sve->put(this);

}

#endif


PCB::PCB(){
	id=1;
	lucky=1;
	kvant=2;
	VREME=0;
	flegic=0;
	blokirane=new Lista();
	sve->put(this);
}

PCB::~PCB() {
	delete blokirane;
	delete stack;

	sve->izbaci(this->getId());
}

void PCB::wrapper(){
	PCB::running->myThread->run();
	lock();
	PCB::running->blokirane->sviaktivni();
	PCB::running->setzavrsio();
	PCB::running->lucky=0;
	zahtevana=1;
	asm int 8h
	unlock();
}

void PCB::waitToComplete(){
	if (this != 0){
		if(!(zavrsio==1) && (startovan==1)){

			PCB::running->lucky=0;
			blokirane->put(PCB::running);

			zahtevana=1;
			asm int 8h;

		}
	}

}


ID PCB::getId(){
	return id;
}

ID PCB::getRunningId(){
		return (PCB::running)->getId();
}

Thread* PCB::getThreadById(int id){
		return sve->dohvati(id)->myThread;
}
