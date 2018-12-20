#ifndef SBR_RULE_H
#define SBR_RULE_H

#include <string>

#include "Attribute.h"


// Store the rules composed by sub-statements, stored
// as 'Attribute' objects and the priority of the rule
class Rule
{
 public:
  void SetSubRules(Attribute &new_sub_rules);
  Attribute *GetSubRules();
  void SetNumSubRules(int new_num_sub_rules);
  int GetNumSubRules();
  void SetRulePriority(int new_priority);
  int GetRulePriority();
  void SetRuleNumber(int n);
  int GetRuleNumber();
  Rule();
  ~Rule();

 private:
  int rule_number;
  int num_sub_rules;
  int rule_priority;
  Attribute *sub_rules;
};

#endif