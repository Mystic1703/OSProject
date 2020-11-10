/*
 * pcblist.cpp
 *
 *  Created on: Aug 15, 2020
 *      Author: OS1
 */


#include"pcblist.h"
#include"kernelsm.h"
#include"System.h"
#include"SCHEDULE.H"
extern int syncPrintf(const char* format,...);
PcbList::PcbList()
{
first=0;
last=0;
count=0;
}

PcbList::~PcbList()
{
	lock;
	El* cur=0;
	while(first!=0)
	{
		cur=first;
		first=first->next;
		first->prev=0;
		delete cur;
		count--;
	}
	last=0;
	unlock;
}

void PcbList::add(PCB* p,Time t)
{
	lock;
	if(p==0 || t==0) {
		unlock;
		return;
	}
   El* e=new El(p,t);
   if(first==0)
    {
	  first=last=e;
    }
   else {
	   last->next=e;
	   e->prev=last;
	   last=last->next;
   }
   count++;
   unlock;
}

PCB* PcbList::remove(unsigned id)
{
	lock;
	if(id>=count) {
		unlock;
		return 0;
	}
	El* cur=first;
	PCB* thr=0;
	if(cur==0) return 0;
	for(unsigned i=0;i<id;i++) cur=cur->next;
	if(cur->prev==0)
	{
		first=first->next;
		if(first==0) last=0;
		else first->prev=0;
		thr=cur->pcb;
		delete cur;
		count--;
	}
	else
	{
		cur->prev->next=cur->next;
		if(cur->next) cur->next->prev=cur->prev;
		else {
			last=cur->prev;
			last->next=0;
		}
		thr=cur->pcb;
		delete cur;
		count--;
	}
	unlock;
	return thr;
}
unsigned PcbList::update() {
	//lock;
	int i=0;
	unsigned ret=0;
	for(El* e=first;e!=0;e=e->next)
	{
		if(e->time>0) e->time--;
		if(e->time==0)
		{
			if(e->prev==0)
				{
					first=first->next;
					if(first==0) last=0;
					else first->prev=0;
				}
				else
				{
					e->prev->next=e->next;
					if(e->next) e->next->prev=e->prev;
					else {
						last=e->prev;
						last->next=0;
					}
				}
			e->pcb->state=PCB::READY;
			e->pcb->returnValue=0;
			Scheduler::put(e->pcb);
			delete e;
			count--;
			ret++;
		}
		i++;
	}
    //unlock;
	return ret;
}
