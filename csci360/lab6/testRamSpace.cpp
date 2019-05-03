#include <stdio.h>
#include "RamSpace.h"
#include <iostream>
using namespace std;
int main() {

   printf("Welcome to Test RamSpace\n");
	
   int ramsize = 103;
   RamSpace *ramspace = new RamSpace(ramsize);
   
   //fill memory

   int *address =ramspace->getAddress();
   for(int i=0; i<ramsize ;i++){
	   int v = rand() % 100;
	  ramspace->write(address,v);
   }

   
   //bubble sort
 
	   int i, j;
	   for (i = 0; i < ramsize-1; i++){
		   // Last i elements are already in place 
		   for (j = 0; j < ramsize-i-1; j++){
			   if (ramspace->read((address)+j) > ramspace->read((address)+j+1)){
				   int xp=ramspace->read((*address)+j);
				   int yp=ramspace->read((*address)+j+1);
				   int temp = xp;
				   ramspace->write((*address)+j,yp);
				   ramspace->write((*address)+j+1,temp);
			   }
		   }
	   }
	   
   //print it
	   for(int i=0; i<ramsize ;i++){
		   cout<<"linuxram["<<i<<"]: "<<ramspace->read((*address+i))<<endl;
	   }
   

   printf("got a ramspace\n");
   delete ramspace;
   return 0;
}
