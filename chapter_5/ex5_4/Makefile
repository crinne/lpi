CC = gcc -std=c11
CFLAGS = -Wall -g
OBJECTS = main.o

ex5_4 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o ex5_4

main.o : main.c headers.h
	$(CC) $(CFLAGS) -c main.c

.PHONY : clean
clean :
	rm -f ex5_4 $(OBJECTS)
