#ifndef SBR_FACTSBASE_H
#define SBR_FACTSBASE_H

#include <list>

#include "Atribute.h"

// Represents the Facts that the Inference Engine've discovered so far.
// First it reads the "Base Facts" stored in a file. They are saved as
// 'Atributes' to make comparaisons for the Inference Engine easier 
class FactsBase {
 public:
  // Returns a copy of the current list of facts
  std::list<Atribute> GetListFacts();
  void AddFact(Atribute fact);
  FactsBase(std::ifstream &file_facts);
  ~FactsBase();
 private:
  std::ifstream &file_facts;
  std::list<Atribute> facts;
  void ReadFacts();

};
#endif