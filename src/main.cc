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
#include "Atribute.h"
#include "InferenceEngine.h"

using namespace std;

ofstream f1;
ofstream f2;

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
  ifstream file_kb(argv[1]);
  ifstream config_file(argv[2]);
  ifstream file_facts(argv[3]);
  string st1(argv[3]);
  st1 = st1.substr(st1.size()-6, st1.size());
  string concat1 = "Salida1-" + st1;
  string concat2 = "Salida2-" + st1;
  f1.open(concat1);
  f2.open(concat2);

  // Checks if the files can be opened
  for (int i = 1; i <= 3; i++)
  {
    if (argv[i] == NULL || !CheckFile(file_kb, argv[i]))
    {
      cerr << "Arguments are not correct." << endl
           << "Use: ./sbr KnowledgeBase.txt ConfigFile.txt FactsFile.txt" << endl
           << "Stop." << endl;
      exit(1);
    }
  }

  Config *c = new Config(config_file);
  KnowledgeBase *kb = new KnowledgeBase(file_kb, c);
  FactsBase *fb = new FactsBase(file_facts);

  InferenceEngine::ForwardChaining(*kb, *c, *fb);

  delete kb;
  delete fb;
  return 0;
}
