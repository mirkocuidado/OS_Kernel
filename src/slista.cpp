/*
 * slista.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#include "slista.h"

SLista::SLista(){
	prvi=0;
	posl=0;
	duz=0;
}

SLista::~SLista(){
	while(prvi!=0){
			SElem* stari=prvi;
			prvi=prvi->sled;
			stari->sled=0;
			delete stari->sem;
			delete stari;
		}

		prvi=0;
		posl=0;
		duz=0;
}

int SLista::getduz() const{
	return duz;
}

void SLista::dodaj(KSem *s){

	SElem* novi=new SElem(s);
	if(prvi==0)
		prvi=novi;
	else posl->sled=novi;
	posl=novi;

	duz++;
}

KSem* SLista::izbaci(KSem *s){

	SElem* pom=prvi;
	SElem* pret=0;

	while( (pom!=0) && (pom->sem!=s) ){
			pret=pom;
			pom=pom->sled;
		}

		if(pom==0) return 0;

		KSem* kaki=pom->sem;
		SElem* stari=pom;

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

		return kaki;
}
