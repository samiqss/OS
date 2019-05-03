CC=g++
Flags=-Wall -Wextra

all: receiver sender

receiver: receiver.o 
	${CC} ${Flags} receiver.o -o receiver

receiver.o: receiver.cpp
	${CC} ${Flags} -c receiver.cpp

sender: sender.o
	${CC} ${Flags} sender.o -o sender

sender.o: sender.cpp
	${CC} ${Flags} -c sender.cpp

clean:
	rm -f receiver.o receiver sender.o sender

