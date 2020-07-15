#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <list>

#include "Config.h"
#include "KnowledgeBase.h"
#include "Rule.h"
#include "FactsBase.h"
#include "Attribute.h"
#include "InferenceEngine.h"

using namespace std;

ofstream f1;
ofstream f2;

// Returns false if the file cannot be opened. True otherwise
bool CheckFile(ifstream &file, const char *file_name)
{
  if (!file)
  {
    cerr << "Unable to open file \"" << file_name << "\"." << endl;
    return false;
  }

  return true;
}

int main(int argc, char const *argv[])
{
  // Stream for the 3 files
  ifstream file_kb(argv[1]);
  ifstream config_file(argv[2]);
  ifstream file_facts(argv[3]);

  // Sets the name of the exit files
  string st1(argv[3]);
  st1 = st1.substr(st1.size() - 6, st1.size());
  string concat1 = "Salida1-" + st1;
  string concat2 = "Salida2-" + st1;

  // Opens the files to write in them
  f1.open(concat1);
  f2.open(concat2);

  // Checks if the files can be opened
  for (int i = 1; i < argc; i++)
  {
    if (argv[i] == NULL || !CheckFile(file_kb, argv[i]))
    {
      cerr << "Arguments are not correct." << endl
           << "Usage: ./sbr KnowledgeBase.txt ConfigFile.txt FactsFile.txt" << endl
           << "Stop." << endl;
      exit(1);
    }
  }

  // Creates the 3 objects used for the 3 files
  KnowledgeBase *kb = new KnowledgeBase(file_kb, config_file);
  FactsBase *fb = new FactsBase(file_facts);

  // Calls the inference engine and start processing the solution
  InferenceEngine::ForwardChaining(*kb, *fb);

  // Delete the objects and all his allocated memory
  delete kb;
  delete fb;

  // Program succeded!
  return 0;
}
