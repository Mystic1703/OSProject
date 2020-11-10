/*
 * semaphor.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#include"semaphor.h"
#include"kernelsm.h"
#include"System.h"
#include"list.h"
extern int syncPrintf(const char* format,...);

Semaphore::Semaphore(int init)
{
	lock
	this->myImpl=new KernelSem(init);
	if(System::semaphores==0) System::semaphores=new List();
	//System::semaphores->put(myImpl);
	unlock
}

Semaphore::~Semaphore()
{
	lock
	delete myImpl;
	unlock
}

int Semaphore::signal(int n)
{
 lock
 if(n==0)
   {
	myImpl->signal();
	unlock
	return 0;
   }
 else if(n>0)
   {
	unsigned num=0;
	 for(int i=0;i<n;i++)
		if(myImpl->signal()>0) num++;
	 unlock
	 return num;
   }
  else
  {
	 unlock
	 return n;
  }
}
int Semaphore::wait(Time waitTime)
{
lock
if(waitTime==0) myImpl->wait();
else myImpl->wait(waitTime);
unlock
return System::running->returnValue;
}
int Semaphore::val() const {
	return myImpl->getVal();
}
