#ifndef RULE_HH
#define RULE_HH
#include <string>

#include "Atribute.hh"

class Rule
{
public:
  void SetSubRules(Atribute &new_sub_rules);
  int GetNumSubRules();
  int GetRulePriority();
  void SetRulePriority(int new_priority);
  Atribute *GetSubRules();
  void SetNumSubRules(int new_num_sub_rules);
  Rule();
  ~Rule();

private:
  int num_sub_rules;
  int rule_priority;
  Atribute *sub_rules;
};

#endif