#include "Atribute.h"
#include <string>
#include <string.h>

using namespace std;

string Atribute::GetAtribute()
{
  return atribute.atribute;
}

string Atribute::GetOp()
{
  return atribute.op;
}

string Atribute::GetValue()
{
  return atribute.value;
}

string Atribute::GetType()
{
  return atribute.type;
}

void Atribute::SetRulesApplied(list<int> rules)
{
  rules_applied = rules;
}

list<int> Atribute::GetRulesApplied()
{
  return rules_applied;
}

void Atribute::SetAtribute(const std::string &word)
{
  atribute.atribute = word;
}

void Atribute::SetOp(const std::string &word)
{
  atribute.op = word;
}

void Atribute::SetValue(const std::string &word)
{
  atribute.value = word;
}

void Atribute::SetType(const std::string &word)
{
  atribute.type = word;
}

Atribute::Atribute()
{
}

Atribute::~Atribute()
{
}