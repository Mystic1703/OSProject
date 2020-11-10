/*
 * System.h
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include"idletrd.h"
#include"Thread.h"
#include"pcb.h"
#include"Queue.h"
#include"semaphor.h"
#include"kernelsm.h"

class List;
#define lock {asm{pushf;cli;}}
#define unlock {asm {popf;}}
class System
{
public:
	static void load();
	static void unload();
	static void dispatch();

private:
	friend class PCB;
	friend class Thread;
	friend class KernelSem;
	friend class KernelEv;
	friend class Semaphore;
	static List* semaphores;
	static Queue* Threads;
	static Thread* starting;
	static volatile PCB* running;
	static IdleThread* idle;
	static volatile int dispatched;
    static void interrupt (*oldRoutine)(...);
	static void interrupt timerIR(...);
};



#endif /* SYSTEM_H_ */
