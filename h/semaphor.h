/*
 * semaphor.h
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#ifndef SEMAPHOR_H_
#define SEMAPHOR_H_

class KernelSem;
typedef unsigned Time;
class Semaphore {
public:
	Semaphore(int init=1);
	virtual ~Semaphore();
	virtual int wait(Time waitTime);
	virtual int signal(int n=0);

	int val() const;
private:
	KernelSem* myImpl;
};



#endif /* SEMAPHOR_H_ */
