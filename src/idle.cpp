/*
 * idle.cpp
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#include "idle.h"
#include "thread.h"
#include "iostream.h"
#include <conio.h>


Idle::Idle():Thread(defaultStackSize,1) {}

void Idle::run(){
	//cout<<"IDLE RADI!";

	while(1){

	}

}
