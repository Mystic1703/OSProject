/*
 * pcb.h
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include"Thread.h"
#include"Queue.h"
//typedef unsigned long TimeTicks;
class Thread;
class Queue;
class KernelSem;
class PCB
{
private:
	Thread* myThread;
	static ID _id;
	ID id;
	static const StackSize maxsize;
	friend class System;
public:
	friend class Thread;
	friend class KernelSem;
	volatile int returnValue;
	static void wrapper();
	 PCB(Thread* myT,StackSize stacksize,Time timeslice);
	 volatile Time PassedTicks;
	 Time pcbTimeSlice;
	 unsigned* pcbSP;
	 StackSize pcbStackSize;
	 unsigned int ss,sp;
	 //int getReturnValue() const volatile {return returnValue;}
	 Thread* getThread() const {return myThread;}
	enum State {NEW,READY,BLOCKED,OVER};
	volatile State state;
    void createStack();
    Queue *waitQueue;
    ~PCB();
};



#endif /* PCB_H_ */
