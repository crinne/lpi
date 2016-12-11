CC = gcc -std=c99
CFLAGS = -g -Wall
OBJECTS = main.o

mytee : $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o mytee


main.o : main.c headers.h
	$(CC) $(CFLAGS) -c main.c


.PHONY : clean
clean :
	rm mytee $(OBJECTS)
