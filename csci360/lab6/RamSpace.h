//RamSpace.h - class definitions for RAM simulator.
//October, 2016
#include "BlockRam.h"

class RamSpace {
public:
   RamSpace(int bytes); //ctor
  ~RamSpace();          //dtor  

   void write(int &address, int byte);
   int read(int &address);
   int* getAddress();
private:
   BlockRam *blockram;
   int ramsize;
};

