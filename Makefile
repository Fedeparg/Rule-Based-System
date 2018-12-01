CC = g++
CFLAGS = -c -Wall
CXXVER = -std=c++11 # Set the C11 standard

sbr: main.o config.o KnowledgeBase.o rule.o atribute.o
	$(CC) $(CXXVER) main.o config.o KnowledgeBase.o rule.o atribute.o -o sbr

main.o: main.cc
	$(CC) $(CXXVER) $(CFLAGS) main.cc

config.o: Config.cc
	$(CC) $(CXXVER) $(CFLAGS) Config.cc

KnowledgeBase.o: KnowledgeBase.cc
	$(CC) $(CXXVER) $(CFLAGS) KnowledgeBase.cc

rule.o: Rule.cc
	$(CC) $(CXXVER) $(CFLAGS) Rule.cc

atribute.o: Atribute.cc
	$(CC) $(CXXVER) $(CFLAGS) Atribute.cc

cleanall:
	rm -f *.o *.gch sbr

clean:
	rm -f *.o *.gch
	