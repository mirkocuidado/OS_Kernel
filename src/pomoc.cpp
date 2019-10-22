/*
 * pomoc.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */
#include <stdio.h>
#include "ksem.h"
#include <iostream.h>
#include "pomoc.h"
#include "SCHEDULE.H"
#include "pcb.h"
#include "idle.h"
#include "lista.h"
#include "slista.h"

#include<conio.h>


unsigned oldTimerOFF, oldTimerSEG;
volatile unsigned tsp,tss,tbp;

volatile int brojac=0;
volatile int zahtevana = 0;
volatile unsigned int lockFlag=1;

Thread* PCB::idle=new Idle();

extern void tick();
//extern int KSem::blok;

void lock(){
	lockFlag++;
}

void unlock(){
	if(lockFlag==0) return;
	lockFlag--;
	if(zahtevana==1)
		dispatch();
}



void dispatch(){
	asm cli
	zahtevana=1;
	asm int 8h

	asm sti
}

void inic(){
	asm {
		cli
				push es
				push ax

				mov ax,0   //  ; inicijalizuje rutinu za tajmer
				mov es,ax

				mov ax, word ptr es:0022h //; pamti staru rutinu
				mov word ptr oldTimerSEG, ax
				mov ax, word ptr es:0020h
				mov word ptr oldTimerOFF, ax

				mov word ptr es:0022h, seg timer	 //postavlja
				mov word ptr es:0020h, offset timer //novu rutinu

				mov ax, oldTimerSEG	 //	postavlja staru rutinu
				mov word ptr es:0182h, ax //; na int 60h
				mov ax, oldTimerOFF
				mov word ptr es:0180h, ax

				pop ax
				pop es
				sti
		}

}

void restore(){
	asm {
		cli
	     push es
		 push ax

		 mov ax,0
		 mov es,ax

		 mov ax,word ptr oldTimerSEG
		 mov word ptr es:0022h,ax
		 mov ax, word ptr oldTimerOFF
		 mov word ptr es:0020h, ax

		 pop ax
		 pop es
		 sti
	}
}


void interrupt timer(...){

	if(zahtevana==0){
		//tick();
		brojac--;

		if(KSem::blok!=0)
			KSem::odradi();

		 asm int 60h;
	}

	if ( (zahtevana==1) || (brojac<=0 && PCB::running->kvant != 0) ){

		if(lockFlag==1){

			zahtevana=0;

#ifndef BCC_BLOCK_IGNORE
			asm{
				mov tsp,sp
				mov tss,ss
				mov tbp,bp

			}


			PCB::running->sp_off=tsp;
			PCB::running->sp_seg=tss;
			PCB::running->bp=tbp;
#endif

			if(PCB::running->myThread!=PCB::idle){

				if(PCB::running->lucky==1){

					Scheduler::put(PCB::running);
				}
			}

			PCB* pom=Scheduler::get();

			if(pom==0){
				PCB::running=PCB::idle->myPCB;
			}

			else PCB::running=pom;

			brojac=PCB::running->kvant;

			tsp=PCB::running->sp_off;
			tss=PCB::running->sp_seg;
			tbp=PCB::running->bp;

	#ifndef BCC_BLOCK_IGNORE
			asm{

				mov sp,tsp
				mov ss,tss
				mov bp,tbp
			}

		}
		else zahtevana=1;
}

#endif

}

