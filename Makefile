CC = g++
CFLAGS = -c -Wall	# All warnings to be treated as errors
CXXVER = -std=c++11 -g	# Set the C11 standard

sbr: main.o Config.o KnowledgeBase.o Rule.o Atribute.o FactsBase.o InferenceEngine.o
	$(CC) $(CXXVER) -Wall main.o Config.o KnowledgeBase.o Rule.o Atribute.o FactsBase.o InferenceEngine.o -o sbr

main.o: src/main.cc
	$(CC) $(CXXVER) $(CFLAGS) src/main.cc

Config.o: src/Config.cc
	$(CC) $(CXXVER) $(CFLAGS) src/Config.cc

KnowledgeBase.o: src/KnowledgeBase.cc
	$(CC) $(CXXVER) $(CFLAGS) src/KnowledgeBase.cc

Rule.o: src/Rule.cc
	$(CC) $(CXXVER) $(CFLAGS) src/Rule.cc

Atribute.o: src/Atribute.cc
	$(CC) $(CXXVER) $(CFLAGS) src/Atribute.cc

FactsBase.o: src/FactsBase.cc
	$(CC) $(CXXVER) $(CFLAGS) src/FactsBase.cc

InferenceEngine.o: src/InferenceEngine.cc
	$(CC) $(CXXVER) $(CFLAGS) src/InferenceEngine.cc


cleanall:
	rm -f *.o *.gch sbr

clean:
	rm -f *.o *.gch
	
