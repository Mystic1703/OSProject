/*
 * IVTEntry.h
 *
 *  Created on: Aug 12, 2020
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

typedef void interrupt (*interruptRoutine)(...);

class KernelEv;
class Event;
class IVTEntry {
protected:
	friend class KernelEv;
	friend class Event;
public:
IVTEntry(int,interruptRoutine);
~IVTEntry();
void signal();
void callOldRoutine();
private:
	static IVTEntry* IVTable[];
	interruptRoutine oldIR;
	KernelEv* myEvent;
	unsigned ivtNo;
};




#endif /* IVTENTRY_H_ */
