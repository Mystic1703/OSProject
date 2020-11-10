/*
 * IVTEntry.cpp
 *
 *  Created on: Aug 12, 2020
 *      Author: OS1
 */

#include"IVTEntry.h"
#include"dos.h"
#include"System.h"
#include"kernelev.h"

IVTEntry* IVTEntry::IVTable[256];
extern int syncPrintf(const char* format,...);
IVTEntry::IVTEntry(int ivtn,interruptRoutine newIR)
{
	lock
	this->ivtNo=ivtn;
	IVTable[ivtn]=this;
	myEvent=0;
	oldIR=getvect(ivtn);
	setvect(ivtn,newIR);
	unlock
}

IVTEntry::~IVTEntry()
{
	lock
	myEvent=0;
	this->callOldRoutine();
	setvect(ivtNo,oldIR);
	unlock
}

void IVTEntry::signal()
{
	lock
	if(myEvent!=0) myEvent->signal();
	unlock
}
void IVTEntry::callOldRoutine()
{
	lock
	if(oldIR!=0) (*oldIR)();
	unlock
}
