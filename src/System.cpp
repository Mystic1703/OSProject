/*
 * System.cpp
 *
 *  Created on: May 2, 2020
 *      Author: OS1
 */



#include"System.h"
#include<dos.h>
#include"SCHEDULE.H"
#include"idletrd.h"
#include"kernelsm.h"
#include"list.h"
volatile int System::dispatched=0;
Queue* System::Threads=0;
void interrupt (*System::oldRoutine)(...)=0;
IdleThread* System::idle=0;
List* System::semaphores=0;
volatile PCB* System::running=0;
Thread* System::starting=0;
extern int syncPrintf(const char* format,...);

void System::dispatch()
{
	lock
	dispatched=1;
	timerIR();
	dispatched=0;
	unlock
}

void System::load()
{
	lock
	oldRoutine=getvect(0x08);
	setvect(0x08,timerIR);
	//semaphores=new List();
	//Threads=new Queue();
	starting=new Thread(0x1000,minTimeSlice());
	starting->myPcb->state=PCB::READY;
	running=(volatile PCB*)starting->myPcb;
	idle=new IdleThread();
	idle->start();
	unlock
}
void System::unload()
{
   if((PCB*)running != starting->myPcb) return;
   lock
   setvect(0x08,oldRoutine);
   delete starting;
   delete idle;
   delete Threads;
   delete semaphores;
   unlock
}

void interrupt System::timerIR(...)
{
	static volatile unsigned tsp,tss;
	static volatile PCB* newThr=0;
	if(!dispatched)
	{
		KernelSem::updateSemaphores();
		tick();
		(*oldRoutine)();
	}
	if(!dispatched && running->pcbTimeSlice!=0) running->PassedTicks++;
	if(!dispatched && (running->pcbTimeSlice > running->PassedTicks || running->pcbTimeSlice==0)) {
		return;
	}
	dispatched=0;
	if(running->state==PCB::READY && running->myThread!=idle) Scheduler::put((PCB*)running);
	//sada ide uzimanje nove niti iz schedulera:
	//syncPrintf(" %d -> ",running->id);
	newThr=Scheduler::get();
	if(newThr==0) newThr=idle->myPcb;
	asm {
		mov tsp,sp
		mov tss,ss
	}
	running->sp=tsp;
	running->ss=tss;
	running=newThr;
	tsp=running->sp;
	tss=running->ss;
	asm {
		mov sp,tsp
		mov ss,tss
	}
	running->PassedTicks=0;
	//syncPrintf("%d ",running->id);
}
