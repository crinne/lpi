CC = gcc -std=c99
CFLAGS = -Wall -Wno-deprecated-declarations -g
OBJECTS = main.o

ex7_2 : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o ex7_2

.PHONY : clean

clean :
	rm -f ex7_2 $(OBJECTS)
