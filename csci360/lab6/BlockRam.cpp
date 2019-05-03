//BlockRam
//Sami Al-Qusus
//lab 6 csci350 oct 23, 2018
////Credits: Dr. LoPinto lab6 examples.
#include <stdio.h>
#include "BlockRam.h"
#include <cstdlib>
#include <iostream>
using namespace std;
//void bubbleSort(int arr[], int n);
BlockRam::BlockRam(int ramsize) { //ctor
   //Compute number of blocks needed to hold ram of this size
   nblocks = ramsize / BLOCKSIZE;
   if(ramsize > BLOCKSIZE*nblocks) nblocks++;

   linuxram = new int[nblocks*BLOCKSIZE];
   printf("BlockRam ctor: linuxram = 0x%x, size = %d\n",
           linuxram, nblocks*BLOCKSIZE);
   int BlockRam::getLinuxram(){
   	return *linuxram;
   }
/* for(int i=0; i<ramsize ;i++){
	int v = rand() % 100;  
	linuxram[i]=v;
   }

   bubbleSort(linuxram,ramsize);
   for(int i=0; i<ramsize ;i++){
	   cout<<"linuxram["<<i<<"]: "<<linuxram[i]<<endl;
   }
   */
}
   // A function to implement bubble sort 
/*   void bubbleSort(int arr[], int n) {
	   int i, j; 
	   for (i = 0; i < n-1; i++){
	        // Last i elements are already in place 
	        for (j = 0; j < n-i-1; j++){
		   if (arr[j] > arr[j+1]){
			int *xp=&arr[j];
			int *yp=&arr[j+1];
		   	int temp = *xp; 
			*xp = *yp;
			*yp = temp;
		   }		
	   	}	   
	   }
   }
*/

BlockRam::~BlockRam() { //dtor
   delete linuxram;
   printf("Deleted linuxram\n");
}
