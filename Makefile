CC = g++
CFLAGS = -c -Wall -Werror	# All warnings to be treated as errors
CXXVER = -std=c++11	# Set the C11 standard

sbr: main.o Config.o KnowledgeBase.o Rule.o Attribute.o FactsBase.o InferenceEngine.o
	$(CC) $(CXXVER) -g -Wall main.o Config.o KnowledgeBase.o Rule.o Attribute.o FactsBase.o InferenceEngine.o -o sbr

main.o: src/main.cc
	$(CC) $(CXXVER) $(CFLAGS) src/main.cc

Config.o: src/Config.cc
	$(CC) $(CXXVER) $(CFLAGS) src/Config.cc

KnowledgeBase.o: src/KnowledgeBase.cc
	$(CC) $(CXXVER) $(CFLAGS) src/KnowledgeBase.cc

Rule.o: src/Rule.cc
	$(CC) $(CXXVER) $(CFLAGS) src/Rule.cc

Attribute.o: src/Attribute.cc
	$(CC) $(CXXVER) $(CFLAGS) src/Attribute.cc

FactsBase.o: src/FactsBase.cc
	$(CC) $(CXXVER) $(CFLAGS) src/FactsBase.cc

InferenceEngine.o: src/InferenceEngine.cc
	$(CC) $(CXXVER) $(CFLAGS) src/InferenceEngine.cc


cleanall:
	rm -f *.o *.gch sbr

clean:
	rm -f *.o *.gch
	
