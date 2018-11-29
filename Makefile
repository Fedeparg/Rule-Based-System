CC = g++
CFLAGS = -c -Wall

sbr: main.o config.o knowledge_base.o
	$(CC) main.o config.o knowledge_base.o -o sbr

main.o: main.cc
	$(CC) $(CFLAGS) main.cc

config.o: Config.cc
	$(CC) $(CFLAGS) Config.cc

knowledge_base.o: Knowledge_base.cc
	$(CC) $(CFLAGS) Knowledge_base.cc

clean:
	rm -f *.o *.gch
	