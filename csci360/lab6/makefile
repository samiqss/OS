testram: testRamSpace.o RamSpace.o BlockRam.o
	g++ -o testram testRamSpace.o RamSpace.o BlockRam.o

testRamSpace.o: testRamSpace.cpp
	g++ -c testRamSpace.cpp

RamSpace.o: RamSpace.cpp RamSpace.h
	g++ -c RamSpace.cpp

BlockRam.o: BlockRam.cpp BlockRam.h
	g++ -c BlockRam.cpp

clean:
	rm -f *.o
	rm -r testram
