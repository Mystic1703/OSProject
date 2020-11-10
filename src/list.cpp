/*
 * list.cpp
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#include"list.h"
#include"System.h"

extern int syncPrintf(const char* format,...);

List::List()
{
	lock
	head=0;
	tail=0;
	size=0;
	unlock
}
List::~List()
{
lock
 while(head!=0)
  {
	Element* e=head;
	head=head->next;
	delete e;
	size--;
  }
  tail=0;
  size=0;
unlock
}
KernelSem* List::find(int i)
{
	lock
	if((i<0) || (i>=size)) {
		unlock;
		return 0;
	}
	Element* e=head;
	while(i>0)
		{
			i--;
			e=e->next;
		//if(e==tail) syncPrintf("end of list...\n");
		}
	unlock
	if(e->sem==0) syncPrintf("zero in find...\n");
	return e->sem;
}
void List::put(KernelSem* s)
{
	lock
	if(s==0) {unlock ;return;}
	Element* e=new Element(s);
	if(head==0) {
		head=e;
		tail=e;
	}
	else {
		tail->next=e;
		tail=tail->next;
	}
	size++;
	unlock
}
void List::semDeleted(KernelSem* s)
{
	lock
	Element *cur=head,*prev=0;
	while(cur!=0)
	{
		if(cur->sem == s)
		{
			if(prev==0)
			{
				head=head->next;
				if(head==0) tail=0;
				delete cur;
				size--;
				break;
			}
			else
			{
				prev->next=cur->next;
				cur=cur->next;
				if(cur==0) tail=prev;
				delete cur;
				size--;
				break;
			}
		}
		prev=cur;
		cur=cur->next;
	}
	unlock
}

