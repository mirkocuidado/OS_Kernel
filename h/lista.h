/*
 * lista.h
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#ifndef LISTA_H_
#define LISTA_H_

#include "pcb.h"

class Lista{

public:
	 struct Elem{
		 PCB* pcb;
		 Elem *sled;
		 Elem(PCB* p){pcb=p; sled=0;}
	 };

	 Elem* prvi;
	 Elem* posl;
	 int duz;


 	 Lista();
    ~Lista();
    int getduz();

    void put(PCB* t); //doda novi PCB u listu

    PCB* get(); // izbaci prvi PCB iz liste

    PCB* dohvati(int id); // dohvatanje niti ciji PCB ima isti id kao parametar

    void izbaci(int id); // izbaci PCB iz liste ciji je id jednak parametru

    Thread* get(int id); //dohvarta nit ciji je ovo ID

    void sviaktivni(); // sve iz liste izbaciti i staviti lucky=1 i u Scheduler

};
#endif /* LISTA_H_ */
