/*
 * kernelev.h
 *
 *  Created on: Aug 12, 2020
 *      Author: OS1
 */

#ifndef KERNELEV_H_
#define KERNELEV_H_

#include"event.h"
class PCB;
class KernelSem;
typedef unsigned char IVTNo;
class KernelEv {

public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void wait();
	void signal();
private:
	PCB* owner;
	IVTNo ivtNo;
	KernelSem* sem;
};




#endif /* KERNELEV_H_ */
