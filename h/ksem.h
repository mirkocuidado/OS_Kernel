/*
 * ksem.h
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#ifndef KSEM_H_
#define KSEM_H_

#include "lista.h"
#include "semafor.h"
#include "thread.h"

class SLista;

class KSem{
private:
	Semaphore* mySem;

	static int IDDD;
	int id;

	int myval;

public:

	KSem(int a, Semaphore* s);
	~KSem();

	static SLista* svi;
	Lista* blokirane;

	int wait(Time maxTimeToWait);
	int signal(int nn);

	void block();
	void deblock();

	int getid() const;
	int getval() const;
	void incval();

	static void odradi();
	static int blok;

protected:
	friend void interrupt timer(...);
	friend int main(int argc, char** argv);
	friend class SLista;
};

#endif /* KSEM_H_ */
