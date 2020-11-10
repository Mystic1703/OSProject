/*
 * kernelev.cpp
 *
 *  Created on: Aug 12, 2020
 *      Author: OS1
 */


#include"kernelev.h"
#include"System.h"
#include"IVTEntry.h"
extern int syncPrintf(const char*,...);
KernelEv::KernelEv(IVTNo ivtn)
{
	lock
	if(IVTEntry::IVTable[ivtn]!=0)
	{
		this->ivtNo=ivtn;
		this->owner=(PCB*)System::running;
		this->sem=new KernelSem(0);
		IVTEntry::IVTable[ivtNo]->myEvent=this;
	}
	unlock
}

KernelEv::~KernelEv()
{
lock
    IVTEntry::IVTable[ivtNo]->myEvent=0;
	delete sem;
	//syncPrintf("Event deleted...\n");
unlock
}

void KernelEv::wait()
{
	lock
	if(((PCB*)System::running)!=this->owner) {
		unlock
		return;
	}
	sem->wait();
	unlock
}
void KernelEv::signal()
{
lock
if(sem->getVal()>=1) {
	unlock
	return;
}
sem->signal();
unlock
}
