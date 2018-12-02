#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <list>

#include "Config.h"
#include "KnowledgeBase.h"
#include "Rule.h"
#include "FactsBase.h"
#include "Atribute.h"

using namespace std;

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
  KnowledgeBase *kb = new KnowledgeBase(file_kb, *c);
  FactsBase *fb = new FactsBase(file_facts);

  cout << c->GetArgumentType("NSemillas") << endl;
  cout << kb->GetDomain() << endl;
  // list<Rule> lista = kb->GetRules();
  // cout << endl;
  // for (list<Rule>::iterator it = lista.begin(); it != lista.end(); ++it)
  // {
  //   cout << "Número de subreglas: " << it->GetNumSubRules() << endl;
  //   Atribute *atr = it->GetSubRules();
  //   for (int i = 0; i <= it->GetNumSubRules(); i++)
  //   {
  //     cout << atr[i].GetAtribute();
  //     cout << " " << atr[i].GetOp();
  //     cout << " " << atr[i].GetValue() << endl;
  //   }
  //   cout << endl;
  // }
  // cout << lista.size() << endl;

  list<Atribute> lista = fb->GetListFacts();
  for (list<Atribute>::iterator it = lista.begin(); it != lista.end(); ++it)
  {
    cout << it->GetAtribute();
    cout << " " << it->GetOp();
    cout << " " << it->GetValue() << endl;
  }

  // 'kb' contains a reference to c, so it will call his destructor
  delete kb;
  return 0;
}
