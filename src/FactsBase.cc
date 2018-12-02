#include <fstream>
#include <string>

#include "FactsBase.h"

using namespace std;

list<Atribute> FactsBase::GetListFacts(){
  list<Atribute> facts_copy(facts);
  return facts_copy;
}

void FactsBase::AddFact(Atribute fact)
{
  facts.push_back(fact);
}

void FactsBase::ReadFacts()
{
  int num_facts = 0;
  file_facts >> num_facts;

  string line("");

  // Jump to the next line
  getline(file_facts, line);

  for(int i = 0; i < num_facts; i++)
  {
    Atribute *fact = new Atribute();
    string word("");

    file_facts >> word;
    fact->SetAtribute(word);
    file_facts >> word;
    fact->SetOp(word);
    file_facts >> word;
    fact->SetValue(word);

    AddFact(*fact);
    // Jump to next line
    getline(file_facts, line);
  }
}

FactsBase::FactsBase(std::ifstream &file_facts)
    : file_facts(file_facts)
{
  ReadFacts();
}

FactsBase::~FactsBase()
{
}