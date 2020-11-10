/*
 * Thread.h
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */

#ifndef THREAD_H_
#define THREAD_H_


typedef unsigned long StackSize;
const StackSize defaultStackSize = 4096;
typedef unsigned int Time; // time, x 55ms
const Time defaultTimeSlice = 2;
typedef int ID;
class PCB;
class Thread
{
protected:
	PCB* myPcb;
	Thread(StackSize stacksize=defaultStackSize,Time timeslice = defaultTimeSlice);
	virtual void run();
	friend class PCB;
	friend class System;
public:
	static Thread* getThread(ID id);
	static ID getRunningID();
	void waitToComplete();
	ID getID();
	void start();
	virtual ~Thread();
};
inline Time minTimeSlice() {return 1;}
void dispatch();
extern void tick();

#endif /* THREAD_H_ */
