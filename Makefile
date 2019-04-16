CC=g++

bc:	main.o lexical.o symTable.o top-down.o
	${CC} -o bc main.o lexical.o symTable.o top-down.o

main.o:			main.cpp general.h
	${CC} -c main.cpp
symTable.o:		symTable.cpp symTable.h general.h
	${CC} -c symTable.cpp
top-down.o:		top-down.cpp symTable.h general.h
	${CC} -c top-down.cpp
lexical.o:			lexical.cpp symTable.h general.h
	${CC} -c lexical.cpp

clean:
	rm bc *.o