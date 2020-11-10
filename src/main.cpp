/*
 * main.cpp
 *
 *  Created on: Apr 18, 2020
 *      Author: OS1
 */

#include"Queue.h"
#include"System.h"
#include<stdio.h>

extern int userMain(int argc,char* argv[]);
extern int syncPrintf(const char* format,...);
int main(int argc,char* argv[])
{
System::load();
int value=userMain(argc,argv);
System::unload();
syncPrintf("Unloaded sucessfully...\n");
return value;
}


