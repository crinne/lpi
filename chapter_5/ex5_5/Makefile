CC = gcc -std=c11
CFLAGS = -Wall -g
OBJECTS = main.o

ex5_5 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o ex5_5

main.o : main.c headers.h
	$(CC) $(CFLAGS) -c main.c

.PHONY : clean
clean : 
	rm -f $(OBJECTS) ex5_5

