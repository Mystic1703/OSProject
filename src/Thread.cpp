/*
 * Thread.cpp
 *
 *  Created on: May 1, 2020
 *      Author: OS1
 */



#include"Thread.h"
#include"pcb.h"
#include"System.h"
#include"SCHEDULE.H"

extern int syncPrintf(const char* format,...);
Thread::Thread(StackSize stacksize,Time timeslice)
{
	lock
	myPcb=new PCB(this,stacksize,timeslice);
	if(System::Threads==0) System::Threads=new Queue();
	System::Threads->put(myPcb);
	unlock
}
Thread::~Thread()
{
	lock
	waitToComplete();
	delete myPcb;
	unlock
}
void Thread::start()
{
lock
this->myPcb->state=PCB::READY;
this->myPcb->createStack();
Scheduler::put(myPcb);
unlock
}

void Thread::run() { }

Thread* Thread::getThread(int id)
{
	lock
	PCB* temp=System::Threads->get(id);
	if(temp==0) {
		unlock
		return 0;
	}
	else {unlock
		return temp->myThread;
	}
}

int Thread::getRunningID()
{
	return System::running->id;
}
void Thread::waitToComplete()
{
	lock
	if(myPcb->state==PCB::OVER || myPcb->state==PCB::NEW) {unlock; return;}
	if(myPcb==(PCB*)System::running) {unlock; return;}
	if(this==System::starting || this==System::idle) {unlock;return;}
	System::running->state=PCB::BLOCKED;
	myPcb->waitQueue->put((PCB*)System::running);
	unlock
	dispatch();
}
int Thread::getID()
{
	return this->myPcb->id;
}

void dispatch()
{
	lock
	System::dispatch();
	unlock
}


