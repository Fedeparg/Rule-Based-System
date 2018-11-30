#ifndef RULE_HH
#define RULE_HH
#include <string>
#include "Atribute.hh"

class Rule
{
private:
  int num_sub_rules;
  Atribute *sub_rules;

public:
  void set_sub_rules(Atribute &new_sub_rules);
  int get_num_sub_rules();
  Atribute *get_sub_rules();
  void set_num_sub_rules(int new_num_sub_rules);
  Rule();
  ~Rule();
};

#endif