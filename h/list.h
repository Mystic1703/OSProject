/*
 * list.h
 *
 *  Created on: Aug 10, 2020
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_
#include"System.h"
class KernelSem;
class Element
{
public:
	KernelSem* sem;
	Element* next;
	Element(KernelSem* s) {
		this->sem=s;
		next=0;
	}
};

class List {
private:
	Element *head,*tail;
	int size;
public:
	friend class KernelSem;
	List();
	void semDeleted(KernelSem*);
	KernelSem* find(int i);
	void put(KernelSem* s);
	int getSize() const {return size;}
	~List();
};



#endif /* LIST_H_ */
