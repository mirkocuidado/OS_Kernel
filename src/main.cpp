/*
 * main.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */


#include "pcb.h"
#include "thread.h"
#include "pomoc.h"
#include "idle.h"
#include "schedule.h"
#include "lista.h"
#include <conio.h>
#include "semafor.h"
#include "ksem.h"
#include "slista.h"
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>


int retvalue;

#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>

extern int userMain(int argc, char* argv[]);

int main(int argc, char* argv[]){
	inic();

	PCB::PCBmain=new PCB();
	PCB::running=PCB::PCBmain;

	cout<<PCB::PCBmain->getId()<<" je main."<<endl;
	cout<<PCB::idle->getId()<<" je idle."<<endl;

	retvalue = userMain(argc, argv);
	cout<<"Retvalue is "<<retvalue<<endl;

	delete PCB::idle;
	delete PCB::sve;
	delete KSem::svi;

	cout<<PCB::sve->getduz()<<endl;
	cout<<KSem::svi->getduz()<<endl;

	cout<<"USPEH";

	restore();
	delete PCB::PCBmain;


	return 0;
}
