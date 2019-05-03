CC=g++
Flags=-Wall -Wextra -lpthread

all: receiver sender

sender: sender.o 
	${CC} ${Flags} sender.o -o sender

sender.o: sender.c 
	${CC} ${Flags} -c sender.c 

receiver: receiver.o
	${CC} ${Flags} receiver.o -o receiver

receiver.o: receiver.c 
	${CC} ${Flags} -c receiver.c 

clean:
	rm -f sender.o sender receiver.o receiver

