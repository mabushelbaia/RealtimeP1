CC = gcc
CFLAGS = -lm -g -pg
INCDIRS = -I/usr/openwin/include -I/usr/local/include
LIBDIRS = -L/usr/openwin/lib -L/usr/local/lib    
CC = gcc
CFLAGS = -g $(INCDIRS)
LIBS = -lX11 -lglut -lGL -lGLU -lm 


run: clean ./bin/parent.o ./bin/child.o # Remove clean if you want to keep the object files
	./bin/parent.o ./opengl

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
opengl: main.o
	./src/./opengl
main.o: main.c
	$(CC) $(CFLAGS) -o main.o $(LIBDIRS) main.c $(LIBS)  



clean:
	mkdir -p ./bin ./txt
	rm -f ./txt/*.txt
	rm -f ./bin/*.o

