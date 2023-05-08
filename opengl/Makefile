
INCDIRS = -I/usr/openwin/include -I/usr/local/include
LIBDIRS = -L/usr/openwin/lib -L/usr/local/lib      

CC = gcc
CFLAGS = -g $(INCDIRS)
LIBS = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 

default: main.o
	./main.o
main.o: main.c
	$(CC) $(CFLAGS) -o main.o $(LIBDIRS) main.c $(LIBS)  
