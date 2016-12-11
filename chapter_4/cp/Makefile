CC = gcc -std=c99
CFLAGS = -g -Wall
OBJECTS = main.o

mycp : $(OBJECTS) 
	$(CC) $(CFLAGS) $(OBJECTS) -o mycp


main.o : main.c headers.h
	$(CC) $(CFLAGS) -c main.c


.PHONY : clean
clean :
	rm mycp $(OBJECTS)
