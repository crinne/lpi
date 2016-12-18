CC = gcc -std=c99
CFLAGS = -Wall -g
OBJECTS = main.o

ex5_2 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o ex5_2

main.o : main.c headers.h
	$(CC) $(CFLAGS) -c main.c


.PHONY : clean
clean : 
	rm -f ex5_2 $(OBJECTS)

