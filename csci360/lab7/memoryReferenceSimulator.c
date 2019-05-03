#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* 
   Memory Reference simulator.  Code and data are in different segments.
   At any time the code occupies two pages and the data occupies three.

   At times, controlled by LOR, the code starts executing in a different
   place (e.g., a function was called) and on different data (e.g., the
   new function operates on its own data.)

*/

#define LOR .95  //Locality of reference. Probability that next instruction 
                 //will reference the same pages as the previous one.


//Simple segmentation model with separate code and data segments
//
#define NCODE 50 //# pages needed to hold program code
#define NDATA 50 //# pages needed to hold program data

#define PSIZE   256  //# bytes per page which is 128 16 bit spaces becasue 256 bytes = 2048 bits / 16 bits =128 

#define CODESEGMENTBASE 0            //virtual address of start of code segment
#define DATASEGMENTBASE PSIZE*NCODE  //virtual address of start of data segment

#define MAXINSTRUCTIONS 2500          //number of instructions to simulate

//Prototypes
void mmu(int address, int rwFlag);
 

int main() {

   printf("Address Request Simulator\n\n");

   //Create arrays needed to hold the code and data pages required at
   //a given instant
   int cp[2];
   int dp[3];

   //Seed the random number generator using a number related to the time
   struct timeval tv;
   gettimeofday(&tv, NULL);
  
   int seed = tv.tv_sec*1000000 + tv.tv_usec;
   srand(seed); 

   //Select initial code and data pages in use
   cp[0] = rand() % NCODE;
   cp[1] = cp[0]+1; if(cp[1] >= NCODE) cp[1] = 0;

   dp[0] = rand() % NDATA; 
   dp[1] = dp[0]+1; if(dp[1] >= NDATA) dp[1] = 1;
   dp[2] = dp[1]+1; if(dp[2] >= NDATA) dp[2] = 0;   

   //Simulate memory references.
   int instructions = 0;
   float f,r;

   //Gather statistics to validate segmentation model
   int lowestC, lowestD;
   int highestC, highestD;
   highestC = highestD = 0;
   lowestC = lowestD = 1000000;

   while(instructions++ < MAXINSTRUCTIONS) {

      //Toss a random number to see if this is a local reference
      r = rand();
      f = r /RAND_MAX;
      if(f > LOR) { 
   	cp[0] = rand() % NCODE;
   	cp[1] = cp[0]+1; if(cp[1] >= NCODE) cp[1] = 0;

        dp[0] = rand() % NDATA; 
   	dp[1] = dp[0]+1; if(dp[1] >= NDATA) dp[1] = 1;
   	dp[2] = dp[1]+1; if(dp[2] >= NDATA) dp[2] = 0;   
      }

      //Select code and data addresses
      int codePage;
      int dataPage;
      double f;

      r = rand();
      f = r / RAND_MAX;
      if(f < 0.5) codePage = 0;
      else codePage = 1;
   
      r = rand();
      f = r /RAND_MAX;
      if(f < 0.33333)      dataPage = 0;
      else if(f < 0.66666) dataPage = 1;
      else                 dataPage = 2;

      //Compute starting addresses of code and data pages
      int codeBase = CODESEGMENTBASE + cp[codePage]*PSIZE;
      int dataBase = DATASEGMENTBASE + dp[dataPage]*PSIZE;
 
      //Compute offsets into code and data pages.
      int codeOffset = rand() % PSIZE;
      int dataOffset = rand() % PSIZE;

      //Compute the pages referenced in this simulated instruction
      int codeAddress = codeBase + codeOffset;
      int dataAddress = dataBase + dataOffset;

      //Track highest and lowest code and data references
      if(codeAddress > highestC) highestC = codeAddress;
      if(codeAddress < lowestC)  lowestC  = codeAddress;
      if(dataAddress > highestD) highestD = dataAddress;
      if(dataAddress < lowestD)  lowestD  = dataAddress;

      //Access the code segment for reading
      mmu(codeAddress,0);

      //Access the data segment. Decide if it's for reading or writing
      r = rand();
      f = r/RAND_MAX;
      if(f < 0.5) mmu(dataAddress,0);
      else        mmu(dataAddress,1);
   }

   printf("after %d simulated memory references:\n",MAXINSTRUCTIONS);

   printf("Low/High Code reference = %x / %x\n",lowestC, highestC);
   printf("Low/High Data reference = %x / %x\n",lowestD, highestD);

   return 0;
}

void mmu(int address, int rwFlag){
   
   if(rwFlag) printf("Write to %x\n",address);
   else       printf("Read from %x\n",address);
}

