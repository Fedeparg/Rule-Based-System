#include "Rule.h"

using namespace std;

void Rule::SetSubRules(Atribute &new_sub_rules)
{
  sub_rules = &new_sub_rules;
}

int Rule::GetNumSubRules()
{
  return num_sub_rules;
}

int Rule::GetRulePriority()
{
  return rule_priority;
}

void Rule::SetRulePriority(int new_rule_priority)
{
  rule_priority = new_rule_priority;
}

Atribute *Rule::GetSubRules()
{
  return sub_rules;
}

void Rule::SetNumSubRules(int new_num_sub_rules)
{
  num_sub_rules = new_num_sub_rules;
}

Rule::Rule()
{
}
Rule::~Rule()
{
}