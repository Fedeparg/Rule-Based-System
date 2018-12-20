#include "Attribute.h"
#include <string>
#include <string.h>

using namespace std;

string Attribute::GetAttribute()
{
  return attribute.attribute;
}

string Attribute::GetOp()
{
  return attribute.op;
}

string Attribute::GetValue()
{
  return attribute.value;
}

string Attribute::GetType()
{
  return attribute.type;
}

void Attribute::SetRulesApplied(list<int> rules)
{
  rules_applied = rules;
}

list<int> Attribute::GetRulesApplied()
{
  return rules_applied;
}

void Attribute::SetAttribute(const std::string &word)
{
  attribute.attribute = word;
}

void Attribute::SetOp(const std::string &word)
{
  attribute.op = word;
}

void Attribute::SetValue(const std::string &word)
{
  attribute.value = word;
}

void Attribute::SetType(const std::string &word)
{
  attribute.type = word;
}

Attribute::Attribute()
{
}

Attribute::~Attribute()
{
}