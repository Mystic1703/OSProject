/*
 * kernelsm.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#include"kernelsm.h"
#include"semaphor.h"
#include"System.h"
#include"list.h"
#include"SCHEDULE.H"
#include"pcblist.h"
class Element;
extern int syncPrintf(const char* format,...);
KernelSem::KernelSem(int init):value(init)
{
	lock
	waitQueue=new Queue();
	timeList=new PcbList();
	System::semaphores->put(this);
	unlock
}
int KernelSem::signal()
{
lock
PCB* tmp=0;
if(value++<0)
{
tmp=waitQueue->get();
if(tmp==0) tmp=timeList->remove(0);
if(tmp==0) {
	unlock;
	syncPrintf("not found...\n");
	return 0;
}
tmp->state=PCB::READY;
tmp->returnValue=1;
Scheduler::put(tmp);
unlock
return 1;
}
unlock
return 0;
}
void KernelSem::updateSemaphores()
{
	for(int i=0;i<System::semaphores->getSize();i++)
	{
		/* if(e->sem==0) syncPrintf("nullptr...\n");
		if(e->sem->timeList->getCount()==0) continue;
		int ret=e->sem->timeList->update();
		//syncPrintf("%d ",ret);
		e->sem->value+=ret; */
		KernelSem* s=System::semaphores->find(i);
		if(s==0) {
			//syncPrintf("nullptr...\n");
			continue;
		}
		if(s->timeList->getCount()==0) continue;
		int ret=s->timeList->update();
		s->value+=ret;
	}
	//syncPrintf("end of updating... ");
}
void KernelSem::wait() {
	lock
	if(--value<0)
	{
		System::running->state=PCB::BLOCKED;
		waitQueue->put((PCB*)System::running);
		unlock
		System::dispatch();
	}
	else unlock
}
void KernelSem::wait(Time waitTime)
{
	lock
	if(--value<0)
	{
		System::running->state=PCB::BLOCKED;
		timeList->add((PCB*)System::running,waitTime);
		unlock
		System::dispatch();
	}
	else unlock;
}
KernelSem::~KernelSem()
{
	lock
	//System::semaphores->semDeleted(this);
	delete waitQueue;
	delete timeList;
	unlock
}
