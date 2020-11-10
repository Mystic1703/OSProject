/*
 * event.cpp
 *
 *  Created on: Aug 12, 2020
 *      Author: OS1
 */

#include"event.h"
#include"System.h"
#include"IVTEntry.h"
#include"kernelev.h"

Event::Event(IVTNo ivtNo)
{
	lock
	myImpl=new KernelEv(ivtNo);
	//IVTEntry::IVTable[ivtNo]->myEvent=myImpl;
	unlock
}

Event::~Event()
{
	lock
	delete myImpl;
	unlock
}

void Event::wait()
{
	lock
	myImpl->wait();
	unlock
}

void Event::signal()
{
	lock
	myImpl->signal();
	unlock
}


