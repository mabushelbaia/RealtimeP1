CC = gcc

default: parent.o child.o
	./parent.o

parent.o: parent.c 
	$(CC) -o parent.o parent.c -lm
child.o: child.c
	$(CC) -o child.o child.c -lm
clean:
	rm -f *.os