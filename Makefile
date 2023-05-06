CC = gcc

potato: clean ./bin/parent.o ./bin/child.o # Remove clean if you want to keep the object files
	./bin/parent.o
./bin/parent.o: ./src/parent.c 
	$(CC) -o ./bin/parent.o ./src/parent.c -lm -g
./bin/child.o: ./src/child.c
	$(CC) -o ./bin/child.o ./src/child.c -lm -g
clean:
	mkdir -p ./txt ./bin
	rm -f ./bin/*.o
	rm -f ./txt/*.txt