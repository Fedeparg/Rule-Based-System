#include <fstream>
#include <iostream>
#include <string>

#include "FactsBase.h"

using namespace std;

list<Attribute> FactsBase::GetListFacts(){
  return facts;
}

void FactsBase::AddFact(Attribute fact)
{
  facts.push_front(fact);
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
    Attribute fact;
    string word("");

    file_facts >> word;
    fact.SetAttribute(word);
    file_facts >> word;
    fact.SetOp(word);
    file_facts >> word;
    fact.SetValue(word);

    AddFact(fact);
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
  file_facts.close(); 
}