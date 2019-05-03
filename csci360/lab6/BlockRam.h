//BlockRam.h

class BlockRam {
public:
   BlockRam(int ramsize);
  ~BlockRam();
  int* getLinuxram();
private:
   const int BLOCKSIZE = 10;
   int *linuxram;
   int nblocks;
};
