CC = g++
CFLAGS = -c -Wall	# All warnings to be treated as errors
CXXVER = -std=c++11	# Set the C11 standard

sbr: main.o config.o KnowledgeBase.o rule.o atribute.o facts.o
	$(CC) $(CXXVER) -Wall main.o config.o knowledgebase.o rule.o atribute.o factsbase.o -o sbr

main.o: src/main.cc
	$(CC) $(CXXVER) $(CFLAGS) src/main.cc

config.o: src/Config.cc
	$(CC) $(CXXVER) $(CFLAGS) src/Config.cc

KnowledgeBase.o: src/KnowledgeBase.cc
	$(CC) $(CXXVER) $(CFLAGS) src/KnowledgeBase.cc

rule.o: src/Rule.cc
	$(CC) $(CXXVER) $(CFLAGS) src/Rule.cc

atribute.o: src/Atribute.cc
	$(CC) $(CXXVER) $(CFLAGS) src/Atribute.cc

facts.o: src/FactsBase.cc
	$(CC) $(CXXVER) $(CFLAGS) src/FactsBase.cc


cleanall:
	rm -f *.o *.gch sbr

clean:
	rm -f *.o *.gch
	