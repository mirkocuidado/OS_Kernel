/*
 * slista.h
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */


#ifndef SLISTA_H_
#define SLISTA_H_

#include "ksem.h"

class SLista{

public:

	struct SElem{
		KSem* sem;
		SElem* sled;

		SElem(KSem* s){
			sem=s;
			sled=0;
		}
	};


	SElem* prvi;
	SElem* posl;
	int duz;



	SLista();
	~SLista();

	int getduz() const;

	KSem* izbaci( KSem* s);
	void dodaj( KSem* s);
};

#endif /* SLISTA_H_ */
