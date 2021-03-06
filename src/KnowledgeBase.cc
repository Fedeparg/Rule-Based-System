#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <fstream>
#include <list>

#include "Rule.h"
#include "Config.h"
#include "KnowledgeBase.h"
#include "Attribute.h"

using namespace std;

int KnowledgeBase::parsed_rules;

void KnowledgeBase::SetNumRules(int new_num_rules)
{
  num_rules = new_num_rules;
}

int KnowledgeBase::GetNumRules()
{
  return num_rules;
}

void KnowledgeBase::SetDomain(const string &new_domain)
{
  domain = new_domain;
}

string KnowledgeBase::GetDomain()
{
  return domain;
}

list<Rule> KnowledgeBase::GetRules()
{
  return rules;
}

void KnowledgeBase::SetRules(list<Rule> new_rules)
{
  rules = new_rules;
}

string KnowledgeBase::GetGoal()
{
  return conf.GetGoal();
}

void KnowledgeBase::ParseRules(const string &line)
{
  int num_sub_rules = 1;
  Attribute *table = new Attribute[10];
  int index = 0;
  string st1("");
  istringstream s(line);
  // Ignore number of Rule
  s >> st1;
  while (s >> st1)
  {
    char *tmp = new char[st1.size()+1];
    strcpy(tmp, st1.c_str());
    if (strcmp(tmp, "y") == 0)
      ++num_sub_rules;

    delete[] tmp;
    Attribute atr;
    s >> st1;
    atr.SetAttribute(st1);
    atr.SetType(conf.GetArgumentType(st1));
    s >> st1;
    atr.SetOp(st1);
    s >> st1;
    atr.SetValue(st1);

    table[index] = atr;
    ++index;
  }

  Rule r;
  r.SetRuleNumber(parsed_rules + 1);
  r.SetRulePriority(conf.GetRulePriority(parsed_rules));
  r.SetSubRules(*table);
  r.SetNumSubRules(num_sub_rules);
  rules.push_back(r);
  parsed_rules++;
}

void KnowledgeBase::ReadKnowledgeBase()
{
  getline(file_kb, domain); // Store the domain
  file_kb >> num_rules;     // Store the number of rules
  string line("");
  getline(file_kb, line); // Move pointer to next line
  for (int i = 0; i < num_rules; ++i)
  {
    getline(file_kb, line);
    ParseRules(line);
  }

  file_kb.close();
}

KnowledgeBase::KnowledgeBase(ifstream &file_kb, ifstream &file_conf)
    : file_kb(file_kb), file_conf(file_conf), conf(file_conf)
{
  // Initialize the values
  SetNumRules(0);
  SetDomain("");
  // Read the file
  ReadKnowledgeBase();
}

KnowledgeBase::~KnowledgeBase()
{
  for (list<Rule>::iterator i = rules.begin(); i != rules.end(); ++i)
  {
    delete[] i->GetSubRules();
  }
}