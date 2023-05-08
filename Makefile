CC = gcc
CFLAGS = -lm -g -pg
run: clean ./bin/parent.o ./bin/child.o # Remove clean if you want to keep the object files
	./bin/parent.o

debug: 
	$(CC) -o ./bin/parent.o ./src/parent.c ./src/local.c $(CFLAGS) 
	$(CC) -o ./bin/child.o ./src/child.c ./src/local.c $(CFLAGS) -D DEBUG
	echo "Children are asleep for 10 sec try to attach to them with gdb from another terminal"
	gdb ./bin/parent.o
cli: 
	$(CC) -o ./bin/parent.o ./src/parent.c ./src/local.c $(CFLAGS) -D CLI
	$(CC) -o ./bin/child.o ./src/child.c ./src/local.c $(CFLAGS) -D CLI
	./bin/parent.o
./bin/parent.o: ./src/parent.c  ./src/local.c
	$(CC) -o ./bin/parent.o ./src/parent.c ./src/local.c $(CFLAGS)
./bin/child.o: ./src/child.c  ./src/local.c
	$(CC) -o ./bin/child.o ./src/child.c ./src/local.c $(CFLAGS)

clean:
	mkdir -p ./bin ./txt
	rm -f ./txt/*.txt

