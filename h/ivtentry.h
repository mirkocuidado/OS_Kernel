/*
 * ivtentry.h
 *
 *  Created on: Jun 10, 2019
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef unsigned char IVTNo;
typedef void interrupt(*pInterrupt)(...);
class Event;

class IVTEntry {

	Event* myEvent;
	pInterrupt stara;
	IVTNo br;

public:

	IVTEntry(IVTNo n, pInterrupt prek);
	~IVTEntry();

	static IVTEntry* getEntry(IVTNo a);
	static IVTEntry* niz[256];

	Event* getEvent();

	void setEvent(Event* e);

	void otkaciEvent();

	void zovistaru();

	void signal();

};

/* Pripremicemo prekidnu rutinu tako sto cemo je staviti u odredjeni ulaz i napraviti objekat klase IVTEntry.
 * Za svaki dogadjaj se pravi posebna prekidna rutina, pa zbog toga postoje ove tarabice. */

#define PREPAREENTRY(br, stara)\
	void interrupt prekid##br(...);\
	IVTEntry ivtentry##br(br, prekid##br);\
	void interrupt prekid##br(...){\
		ivtentry##br.signal();\
		if (stara == 1)\
			ivtentry##br.zovistaru();\
	}\





#endif /* IVTENTRY_H_ */
