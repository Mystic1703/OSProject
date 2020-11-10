/*
 * pcblist.h
 *
 *  Created on: Aug 15, 2020
 *      Author: OS1
 */

#ifndef PCBLIST_H_
#define PCBLIST_H_

#include"kernelsm.h"

class PCB;

class El {
public:
	PCB* pcb;
	Time time;
	El *next,*prev;
	El(PCB* p,Time timeLeft) {
		this->pcb=p;
		time=timeLeft;
		next=0;
		prev=0;
	}
};

class PcbList {
private:
	El *first,*last;
	unsigned count;
public:
	friend class PCB;
	PcbList();
	unsigned update();
	void add(PCB* p,Time t);
	PCB* remove(unsigned i);
	unsigned getCount() const {return count;}
	~PcbList();
};


#endif /* PCBLIST_H_ */
