#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <list>

#include "Config.h"
#include "KnowledgeBase.h"
#include "Rule.h"

using namespace std;

bool CheckFile(ifstream &file, const char *file_name)
{
  if (!file)
  {
    cerr << "Unable to open file \"" << file_name << "\"" << endl;
    return false;
  }

  return true;
}

int main(int argc, char const *argv[])
{
  ifstream file_kb(argv[1]);
  ifstream config_file(argv[2]);

  // Checks if the files can be opened
  if (!CheckFile(file_kb, argv[1]) ||
      !CheckFile(config_file, argv[2]))
  {
    exit(1);
  }

  Config *c = new Config(config_file);
  KnowledgeBase *kb = new KnowledgeBase(file_kb, *c);

  cout << c->GetArgumentType("NSemillas") << endl;
  cout << kb->GetDomain() << endl;
  list<Rule> lista = kb->GetRules();
  Rule r = lista.front();
  for (list<Rule>::iterator it = lista.begin(); it != lista.end(); ++it)
  {
    cout << "Número de subreglas " << it->GetNumSubRules() << endl;
    cout << it->GetSubRules()[it->GetNumSubRules()].GetAtribute();
    cout << " " << it->GetSubRules()[it->GetNumSubRules()].GetOp();
    cout << " " << it->GetSubRules()[it->GetNumSubRules()].GetValue() << endl;
  }
  cout << lista.size() << endl;

  // 'kb' contains a reference to c, so it will call his destructor
  delete kb;
  return 0;
}
