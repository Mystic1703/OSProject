/*
 * Queue.cpp

 *
 *  Created on: Apr 18, 2020
 *      Author: Aleksa Mitic 0025/2018
 */

#include"Queue.h"
#include"System.h"
#include"pcb.h"
#include"SCHEDULE.H"
extern int syncPrintf(const char* format,...);

Queue::Queue()
{
	//lock
	first=0;
	last=0;
	count=0;
	//unlock
}

int Queue::size() const
{
	return this->count;
}

void Queue::put(PCB* p)
{
	lock
	//syncPrintf("%d ",time);
	Elem *e=new Elem(p);
	if(first==0)
	{
		first=e;
		last=first;
	}
	else
		{
		last->next=e;
		last=last->next;
		}
	count++;
	unlock
}
PCB* Queue::get()
{
if(first==0) return 0;
lock
Elem *e=first;
first=first->next;
if(first==0) last=0;
count--;
PCB* tmp=e->pcb;
delete e;
unlock
return tmp;
}
Queue::~Queue()
{
lock
Elem* tek;
while(first!=0)
{
	tek=first;
	first=first->next;
	delete tek;
	count--;
}
last=0;
first=0;
unlock
}

PCB* Queue::get(unsigned id)
{
	lock
	for(Elem* cur=first;cur!=0;cur=cur->next)
	{
		if((cur->pcb->getThread())->getID()==id) {unlock; return cur->pcb;}
	}
	unlock
	return 0;
}

