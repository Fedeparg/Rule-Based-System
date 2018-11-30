#include "Rule.hh"

using namespace std;

void Rule::set_sub_rules(Atribute &new_sub_rules)
{
    sub_rules = &new_sub_rules;
}

int Rule::get_num_sub_rules()
{
    return num_sub_rules;
}

Atribute *Rule::get_sub_rules()
{
    return sub_rules;
}

void Rule::set_num_sub_rules(int new_num_sub_rules)
{
    num_sub_rules = new_num_sub_rules;
}

Rule::Rule()
{
}
Rule::~Rule()
{
}