#ifndef SBR_FACTSBASE_H
#define SBR_FACTSBASE_H

#include <list>

#include "Attribute.h"

// Represents the Facts that the Inference Engine've discovered so far.
// First it reads the "Base Facts" stored in a file. They are saved as
// 'Attributes' to make comparaisons for the Inference Engine easier 
class FactsBase {
 public:
  // Returns a copy of the current list of facts
  std::list<Attribute> GetListFacts();
  void AddFact(Attribute fact);
  FactsBase(std::ifstream &file_facts);
  ~FactsBase();
 private:
  std::ifstream &file_facts;
  std::list<Attribute> facts;
  void ReadFacts();

};
#endif