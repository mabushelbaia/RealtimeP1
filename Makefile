CC = gcc

potato: clean parent.o child.o # Remove clean if you want to keep the object files
	./parent.o
parent.o: parent.c 
	$(CC) -o parent.o parent.c -lm -g
child.o: child.c
	$(CC) -o child.o child.c -lm -g
clean:
	rm -f *.o
	rm -f *.txt