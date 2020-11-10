/*
 * idletrd.cpp
 *
 *  Created on: Apr 21, 2020
 *      Author: OS1
 */


#include"System.h"
#include"Thread.h"
#include"idletrd.h"

extern int syncPrintf(const char* format,...);
IdleThread::IdleThread():Thread(0x1000,minTimeSlice()) {}

void IdleThread::start()
{
	lock;
    this->myPcb->state=PCB::READY;
    this->myPcb->createStack();
	unlock;
}

void IdleThread::run()
{
	while(1);
}


