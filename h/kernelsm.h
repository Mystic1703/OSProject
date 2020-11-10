/*
 * kernelsm.h
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#ifndef KERNELSM_H_
#define KERNELSM_H_
#include"semaphor.h"
class Queue;
class PcbList;

class KernelSem {
public:
	friend class Semaphore;
	static void updateSemaphores();
	KernelSem(int init=1);
	void wait();
	void wait(Time ticks);
	int signal();
	int getVal() const {return value;}
	~KernelSem();
private:
	volatile int value;
	Queue *waitQueue;
	PcbList *timeList;
};



#endif /* KERNELSM_H_ */
