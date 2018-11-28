CC = g++

SE: main.o reader.o
	$(CC) main.o reader.o -o SE

main.o: main.cc
	$(CC) -Wall -c main.cc

reader.o: reader.cc
	$(CC) -c -Wall reader.cc

clean:
	rm -f *.o *.gch