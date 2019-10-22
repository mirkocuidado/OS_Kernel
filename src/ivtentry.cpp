/*
 * ivtentry.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: OS1
 */

#include "ivtentry.h"
#include <dos.h>
#include "event.h"

extern void lock();
extern void unlock();
extern unsigned int lockFlag;

IVTEntry * IVTEntry::niz[256];

IVTEntry::IVTEntry(IVTNo a, pInterrupt b){

//zapamtimo staru prekidnu rutinu i postavimo nasu novu na njeno meso

#ifndef BCC_BLOCK_IGNORE
	stara=getvect(a);
	setvect(a, b);
#endif

	br=a;
	IVTEntry::niz[br]=this;
}

IVTEntry::~IVTEntry(){
	lock();

	//zovistaru(); - moze, a ne mora

#ifndef BCC_BLOCK_IGNORE
	if(stara!=0)
		setvect(br, stara); //vratimo staru na mesto njeno
#endif

	IVTEntry::niz[br]=0;
	unlock();
}

void IVTEntry::setEvent(Event* e){
	myEvent = e;
}

IVTEntry* IVTEntry::getEntry(IVTNo i){
	return niz[i];
}

Event* IVTEntry::getEvent(){
	return myEvent;
}

void IVTEntry::zovistaru(){
	stara();
}

void IVTEntry::signal(){
	if(myEvent!=0)
		myEvent->signal();
}
