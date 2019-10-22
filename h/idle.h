/*
 * idle.h
 *
 *  Created on: Jun 6, 2019
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "thread.h"

class Idle: public Thread {
public:
	Idle();

	void run();
};

#endif /* IDLE_H_ */
