/*
 * pcb.cpp
 *
 *  Created on: May 1, 2020
 *      Author: OS1
 */

#include"pcb.h"
#include"Thread.h"
#include<dos.h>
#include<stdlib.h>
#include"SCHEDULE.H"
#include"Queue.h"
#include"System.h"
ID PCB::_id=0;
const StackSize PCB::maxsize=0x10000;
extern int syncPrintf(const char* format,...);
PCB::PCB(Thread* myThr,StackSize stacksize,Time timeslice):
		myThread(myThr),pcbTimeSlice(timeslice),PassedTicks(0),pcbSP(0),returnValue(0)
{
	lock
	this->state=NEW;
	 if(stacksize>maxsize) {
		pcbStackSize = maxsize;
	} else pcbStackSize = stacksize;
	id=++_id;
	waitQueue=new Queue();
	unlock
}
PCB::~PCB()
{
	lock
	delete pcbSP;
	delete waitQueue;
	unlock
}

void PCB::createStack()
{
	lock
	unsigned n = pcbStackSize/2;
	unsigned* temp=new unsigned[n];
	this->pcbSP=temp;
	temp[n-1]=0x200;
	temp[n-2]=FP_SEG(&(PCB::wrapper));
	temp[n-3]=FP_OFF(&(PCB::wrapper));
	this->sp=FP_OFF(temp+n-12);
	this->ss=FP_SEG(temp+n-12);
	unlock
}

void PCB::wrapper()
{
	//syncPrintf("Wrapper...\n");
	System::running->myThread->run();
	lock
	System::running->state=PCB::OVER;
	PCB* temp;
	while(System::running->waitQueue->size() > 0)
	{
		temp=System::running->waitQueue->get();
		if(temp!=0) {
		temp->state=PCB::READY;
		Scheduler::put(temp);
		}
	}
	unlock
	dispatch();
}


