/*
 * event.h
 *
 *  Created on: Jun 10, 2019
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "kernelev.h"
#include "ivtentry.h"

typedef unsigned char IVTNo;
class KernelEv;
class IVTEntry;

class Event {
public:
	Event(IVTNo ivtno);
	~Event();

	void wait();

protected:
	friend class KernelEv;
	friend class IVTEntry;
	void signal();

private:

	KernelEv* myImpl;
};

#endif /* EVENT_H_ */
