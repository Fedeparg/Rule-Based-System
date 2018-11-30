CC = g++
CFLAGS = -c -Wall

sbr: main.o config.o knowledge_base.o rule.o atribute.o
	$(CC) main.o config.o knowledge_base.o rule.o atribute.o -o sbr

main.o: main.cc
	$(CC) $(CFLAGS) main.cc

config.o: Config.cc
	$(CC) $(CFLAGS) Config.cc

knowledge_base.o: Knowledge_base.cc
	$(CC) $(CFLAGS) Knowledge_base.cc

rule.o: Rule.cc atribute.o
	$(CC) $(CFLAGS) Rule.cc

atribute.o: Atribute.cc
	$(CC) $(CFLAGS) Atribute.cc

clean:
	rm -f *.o *.gch sbr
	