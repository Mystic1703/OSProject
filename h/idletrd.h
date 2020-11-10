/*
 * idletrd.h
 *
 *  Created on: Apr 21, 2020
 *      Author: OS1
 */

#ifndef IDLETRD_H_
#define IDLETRD_H_
#include"Thread.h"

class IdleThread:public Thread
{
public:
	IdleThread();
	void start();
	virtual void run();
};





#endif /* IDLETRD_H_ */
