/*
 * event.cpp
 *
 *  Created on: Jun 10, 2019
 *      Author: OS1
 */

#include "event.h"

Event::Event(IVTNo a){ //napravim novi event i postavim ga na dati ulaz u IVT

	myImpl=new KernelEv(a);
	IVTEntry::getEntry(a)->setEvent(this);
}

void Event::wait() {
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}

Event::~Event(){
	delete myImpl;
}
