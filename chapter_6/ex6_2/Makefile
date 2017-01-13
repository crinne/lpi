CC = gcc -std=c11
CFLAGS = -Wall -g
OBJECTS = main.o

ex6_2 : ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ex6_2

.PHONY : clean

clean :
	rm -f ex6_2 ${OBJECTS}
