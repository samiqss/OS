CC=g++
Flags=-Wall -Wextra

lab11x:	lab1.o 
	${CC} ${Flags} lab1.o -o lab1

lab11.o: lab1.cpp
	${CC} ${Flags} -c lab1.cpp

clean:
	rm -f lab1.o lab1

