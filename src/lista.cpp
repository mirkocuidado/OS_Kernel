/*
 * lista.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#include "lista.h"
#include "schedule.h"

Lista::Lista(){
	prvi=0;
	posl=0;
	duz=0;
}

int Lista::getduz() { return duz; }

Lista::~Lista(){

	while(prvi!=0){
		Elem* stari=prvi;
		prvi=prvi->sled;
		stari->sled=0;
		delete stari->pcb;
		delete stari;
	}

	prvi=0;
	posl=0;
	duz=0;
}


void Lista::put(PCB* t){

	Elem* novi=new Elem(t);

	if(prvi==0) prvi=novi;
	else posl->sled=novi;
	posl=novi;

	duz++;;
}

PCB* Lista::get(){

	if(duz==0) return 0;

	PCB*pom=prvi->pcb;

	Elem*stari=prvi;
	prvi=prvi->sled;

	stari->sled=0;

	if(prvi==0) posl=0;

	delete stari;
	duz--;
	return pom;
}

PCB* Lista::dohvati(int id){
	Elem* tek;
	for(tek=prvi; tek!=0; tek=tek->sled)
		if(tek->pcb->getId() == id)
			return tek->pcb;

	if(tek==0) return 0;
	return 0;
}


void Lista::sviaktivni(){

	PCB* pom= get();
	while(pom!=0){
		pom->lucky=1;
		Scheduler::put(pom);
		pom=get();
	}
}

void Lista::izbaci(int id){

	Elem*pom=prvi;
	Elem*pret=0;

	while( (pom!=0) && (pom->pcb->getId()!=id) ){
		pret=pom;
		pom=pom->sled;
	}

	if(pom==0) return;
	Elem* stari=pom;

	if(pret==0){
		prvi=pom->sled;
		if(prvi==0) posl=0;
	}
	else {
		pret->sled=pom->sled;
		if(pom->sled==0) posl=pret;
	}

	delete stari;
	duz--;
}

Thread* Lista::get(int idd){

  	Elem*pom=0;

  	for(pom=prvi; pom!=0; pom=pom->sled){
  		if(pom->pcb->getId()==idd)
  			return pom->pcb->myThread;
  	}

  	return 0;
  }

