/*
 * kernelev.h
 *
 *  Created on: Jun 10, 2019
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

class PCB;
typedef unsigned char IVTNo;

class KernelEv {

	PCB* owner;
	PCB* blokirana;
	IVTNo broj;
	int val;

public:

	KernelEv(IVTNo br);
	~KernelEv();

	void wait();

protected:

	void signal();

	friend class IVTEntry;
	friend class Event;

};

#endif /* KERNELEV_H_ */
