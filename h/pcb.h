/*
 * pcb.h
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
#include "lista.h"
#include <dos.h>
#include<conio.h>

class Lista;

class PCB {

public:

	static ID IDD;
	ID id;
	Thread* myThread;

	Time kvant;

	StackSize size;
	unsigned* stack;

	unsigned sp_off;
	unsigned sp_seg;
	unsigned bp;

	int startovan;
	int zavrsio;

	friend void interrupt timer();
	friend class Thread;
	friend class Lista;

	static Lista* sve;

	PCB(StackSize stsz,Time kvant,Thread* t);
	PCB();
	~PCB();

	static PCB* running;
	static PCB* PCBmain;
	static Thread* idle;

	int lucky;  //lucky==1 spreman za scheduler
	int flegic; //flegic==1 isteklo vreme
	int VREME;  //spavanje na semaforu

	Lista* blokirane;

	ID getId();

	static ID getRunningId();
	static Thread* getThreadById(ID id);
	static void wrapper();

	void waitToComplete();

	void setzavrsio(){ zavrsio=1; }
	void setstartovan() { startovan=1; }

	friend class Thread;
	friend class Idle;
	friend class Lista;
	friend class Pomoc;
	friend int main(int a, char** b);
};
#endif /* PCB_H_ */
