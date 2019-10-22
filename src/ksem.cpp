/*
 * ksem.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#include "ksem.h"
#include "pcb.h"
#include "lista.h"
#include "SCHEDULE.h"
#include "slista.h"
#include <stdio.h>
#include <iostream.h>

extern volatile int zahtevana;
extern void lock();
extern void unlock();
extern unsigned int lockFlag;

int KSem::blok=0;
int KSem :: IDDD=0;

SLista* KSem::svi = new SLista();

KSem::KSem(int a, Semaphore* s){
	id=++IDDD;

	if(a<0) a=0;
	myval=a;
	mySem=s;

	blokirane=new Lista();
	svi->dodaj(this);

}

KSem::~KSem(){

	if(myval<0){
		myval=-myval;
		for(int i=0; i<myval; i++)
			deblock();
	}

	delete blokirane;
	KSem* s=KSem::svi->izbaci(this);
}

int KSem::getid() const { return id; }

int KSem::getval() const { return myval; }

void KSem::incval() { myval++; }

int KSem::signal(int n){

	lock();
	if(n<0) {
		unlock();
		return n;
	}

	if(n==0){
		myval++;
		if(myval<=0) deblock();

		unlock();
		return 1;
	}

	if( (n>0) && (myval<0) ){
		int pom=n;

		if ( (  myval*(-1) ) < n) pom= myval*(-1);

		for(int i=0; i<pom; i++){
			deblock();
		}
		myval+=pom;

		unlock();
		return pom;
	}
	else if ( (n>0) && (myval>=0) ) {
		myval+=n;

		unlock();
		return 0;
	}

	unlock();
	return 0;
}

int KSem::wait(Time t){

	lock();

	myval--;

	if(myval<0){

		if(t==0)
			PCB::running->VREME=-1;
		else{
			KSem::blok++;
			PCB::running->VREME=t;
		}

		blokirane->put(PCB::running);

		PCB::running->lucky=0;
		zahtevana=1;

		lockFlag--;
		asm int 8h

	}
	else unlock();

	if(PCB::running->flegic==0) return 1;
	if(PCB::running->flegic==1) return 0;

	return 1;
}

void KSem::deblock(){
	PCB* pom=blokirane->get();

	pom->lucky=1;
	pom->flegic=0; //moze i bez ove linije.

	if(pom->VREME>0) {
		KSem::blok--;
		pom->VREME=-1;
	}

	Scheduler::put(pom);
}

void KSem::odradi() {

		for(SLista::SElem* tek= KSem::svi->prvi; tek!=0; tek=tek->sled){

			Lista::Elem* pom1 = tek->sem->blokirane->prvi;
			Lista::Elem* pret=0;

			while (pom1 != 0) {

				if (pom1->pcb->VREME > 0) {
					pom1->pcb->VREME--;

					if (pom1->pcb->VREME == 0) {

						Lista::Elem* stari = pom1;

						if (pret == 0) {

							tek->sem->blokirane->prvi = tek->sem->blokirane->prvi->sled;

							if (tek->sem->blokirane->prvi == 0) { tek->sem->blokirane->posl = 0; pom1 = 0; }
							else { pom1 = pom1->sled; }
						}

						else {
							pret->sled = pom1->sled;

							if (pom1->sled == 0) {

								tek->sem->blokirane->posl = pret;
								pom1 = 0;

							}

							else {

								pom1 = pom1->sled;

							}
						}

						stari->pcb->lucky=1;
						stari->pcb->flegic=1;

						Scheduler::put(stari->pcb);

						delete stari;

						tek->sem->incval();
					}

					else {
						pret = pom1;
						pom1 = pom1->sled;
					}
				}
				else {
					pret = pom1;
					pom1 = pom1->sled;
				}
			}
	}

}
