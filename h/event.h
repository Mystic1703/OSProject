/*
 * Event.h
 *
 *  Created on: Aug 12, 2020
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include"IVTEntry.h"
#include"KernelEv.h"
typedef unsigned char IVTNo;

#define PREPAREENTRY(ivtno,old) \
void interrupt routine##ivtno(...); \
IVTEntry ent##ivtno(ivtno,routine##ivtno); \
void interrupt routine##ivtno(...) { \
	if (old) ent##ivtno.callOldRoutine(); \
	ent##ivtno.signal(); \
	dispatch(); \
}


class Event {
public:
	Event(IVTNo ivtNo);
	~Event();
	void wait();
protected:
	friend class KernelEv;
	void signal();
private:
	KernelEv* myImpl;
};




#endif /* EVENT_H_ */
