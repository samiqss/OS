//RamSpace.cpp - implementation of RamSpace class
#include <stdio.h>
#include "RamSpace.h"

//Methods for class RamSpace
RamSpace::RamSpace(int size) {
   ramsize = size;
   blockram = new BlockRam(size);
}

RamSpace::~RamSpace() {
   delete blockram;
}

int * RamSpace::getAddress(){
	return blockram->getLinuxram();
}


void RamSpace::write(int &address, int byte){
	int *p;
	p = &address;
	*p = byte;
	
}
int RamSpace::read(int &address){
	int *p;
	p=&address;
	return *p;
}
