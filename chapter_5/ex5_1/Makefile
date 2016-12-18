CC = gcc -std=c99
CFLAGS = -Wall -g
OBJECTS = main.o

ex5_1 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o ex5_1

main.o : main.c headers.h
	$(CC) $(CFLAGS) -c main.c

.PHONY : clean
clean :
	rm -f ex5_1 $(OBJECTS)
