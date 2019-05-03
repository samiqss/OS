all: nru genData fifo

nru: nru.o
	g++ -o nru nru.o 

fifo: fifo.o
	g++ -o fifo fifo.o

genData: memoryReferenceSimulator.o 
	g++ -o genData memoryReferenceSimulator.o 

memoryReferenceSimulator.o: memoryReferenceSimulator.c
	g++ -c memoryReferenceSimulator.c

nru.o: nru.c
	g++ -c nru.c

fifo.o: fifo.c 
	g++ -c fifo.c 

clean:
	rm -f *.o
	rm -r genData
	rm -r nru
	rm -r fifo
