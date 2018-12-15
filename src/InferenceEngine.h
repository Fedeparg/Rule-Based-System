#ifndef SBR_INFERENCEENGINE_H
#define SBR_INFERENCEENGINE_H

#include <string>
#include <list>

#include "Config.h"
#include "FactsBase.h"
#include "KnowledgeBase.h"
#include "Rule.h"

namespace InferenceEngine {
  bool ForwardChaining(KnowledgeBase &kb, Config &conf, FactsBase &facts);
  bool GoalFound(std::list<Atribute> &facts, std::string goal);
  void SearchRules(std::list<Rule> &conflict, std::list<Rule> &rules, std::list<Atribute> &facts);
  bool CompareAtributes(Atribute &a1, Atribute &a2);
  bool OpToCode(Atribute &a1, Atribute &a2);
  Atribute Resolve(std::list<Rule> &conflict);
  // void Test(KnowledgeBase &kb, Config &conf, FactsBase &facts);
}

#endif