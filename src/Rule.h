#ifndef SBR_RULE_H
#define SBR_RULE_H

#include <string>

#include "Atribute.h"


// Store the rules composed by sub-statements, stored
// as 'Atribute' objects and the priority of the rule
class Rule
{
 public:
  void SetSubRules(Atribute &new_sub_rules);
  Atribute *GetSubRules();
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
  Atribute *sub_rules;
};

#endif