#ifndef SBR_INFERENCEENGINE_H
#define SBR_INFERENCEENGINE_H

#include <string>
#include <list>

#include "Config.h"
#include "FactsBase.h"
#include "KnowledgeBase.h"
#include "Rule.h"

namespace InferenceEngine {
  bool ForwardChaining(KnowledgeBase &kb, FactsBase &facts);
  bool GoalFound(std::list<Attribute> &facts, std::string goal);
  void SearchRules(std::list<Rule> &conflict, std::list<Rule> &rules, std::list<Attribute> &facts);
  bool CompareAttributes(Attribute &a1, Attribute &a2);
  bool OpToCode(Attribute &a1, Attribute &a2);
  Attribute Resolve(std::list<Rule> &conflict, std::list<Attribute> &facts);
  bool CompareJustAttributes(Attribute &a1, Attribute &a2);
  void WriteConclusion(std::list<Attribute> facts, std::list<Rule> rules);
}

#endif