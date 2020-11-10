/*
 * Queue

 *
 *  Created on: Apr 18, 2020
 *      Author: Aleksa Mitic 0025/2018
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include"pcb.h"
class PCB;
class Elem
	{
public:
		PCB* pcb;
		Elem* next;
		Elem(PCB* p) {
		if(p!=0) pcb=p;
			next=0;
		}
	};
class Queue
{
private:
	Elem *first,*last;
	int count;
public:
    friend class KernelSem;
	Queue();
    int size() const;
    int decrementAndDelete();
    PCB* get(unsigned id);
    void put(PCB* p);
    PCB* get();
    ~Queue();
};




#endif /* QUEUE_H_ */
