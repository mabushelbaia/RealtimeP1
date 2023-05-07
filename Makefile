CC = gcc
CFLAGS = -lm -g -pg
potato: clean ./bin/parent.o ./bin/child.o # Remove clean if you want to keep the object files
	./bin/parent.o
debug: clean ./bin/parent.o ./bin/child.o
	gdb ./bin/parent.o
./bin/parent.o: ./src/parent.c  ./src/local.c
	$(CC) -o ./bin/parent.o ./src/parent.c ./src/local.c $(CFLAGS)
./bin/child.o: ./src/child.c  ./src/local.c
	$(CC) -o ./bin/child.o ./src/child.c ./src/local.c $(CFLAGS)

clean:
	mkdir -p ./bin ./txt
	rm -f ./bin/*.o
	rm -f ./txt/*.txt