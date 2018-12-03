#include <iostream>
#include <list>
#include <iterator>
#include <set>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "InferenceEngine.h"
#include "Atribute.h"

using namespace std;

bool InferenceEngine::ForwardChaining(KnowledgeBase &kb, Config &c, FactsBase &fb)
{
  // Get the list of facts
  list<Atribute> facts(fb.GetListFacts());
  // Create and fill ConflictSet
  list<Rule> rules(kb.GetRules());
  list<Rule> conflict;

  // Search for rules
  SearchRules(conflict, rules, facts);

  while (!GoalFound(facts, c.GetGoal()) && !conflict.empty())
  {
    facts.push_back(Resolve(conflict));
    if (!GoalFound(facts, c.GetGoal()))
      SearchRules(conflict, rules, facts);

    else
    {
      return true;
    }
  }

  if (GoalFound(facts, c.GetGoal()))
  {
    return true;
  }

  return false;
}

bool InferenceEngine::GoalFound(list<Atribute> &facts, string goal)
{
  for (list<Atribute>::iterator it = facts.begin(); it != facts.end(); ++it)
  {
    if (it->GetAtribute().compare(goal) == 0)
    {
      cout << "Solución: " << it->GetAtribute() << " " << it->GetOp() << " " << it->GetValue() << endl;
      return true;
    }
  }
  return false;
}

void InferenceEngine::SearchRules(list<Rule> &conflict, list<Rule> &rules, list<Atribute> &facts)
{
  int j = 1;
  for (list<Rule>::iterator it = rules.begin(); it != rules.end(); ++it)
  {
    Atribute *subrules = it->GetSubRules();

    bool flag = true;
    for (int i = 0; i < it->GetNumSubRules(); ++i)
    {
      bool flag_condition = false;

      for (list<Atribute>::iterator fact = facts.begin(); fact != facts.end(); ++fact)
      {
        if (CompareAtributes(subrules[i], *fact))
        {
          flag_condition = true;
        }
      }

      if (flag_condition == false)
      {
        flag = false;
        break;
      }
    }
    if (flag == true)
    {
      conflict.push_back(*it);
      it = rules.erase(it);
      --it;
    }
    ++j;
  }
}

bool InferenceEngine::CompareAtributes(Atribute &a1, Atribute &a2)
{
  if (a1.GetAtribute().compare(a2.GetAtribute()) == 0)
  {
    if (a1.GetType().compare("NU") == 0)
    {
      if (OpToCode(a1, a2))
      {
        return true;
      }
    }
    else if (a1.GetValue().compare(a2.GetValue()) == 0)
    {
      return true;
    }
  }
  return false;
}

bool InferenceEngine::OpToCode(Atribute &a1, Atribute &a2)
{
  char array1[a1.GetValue().size()];
  int v1 = atoi(strcpy(array1, a1.GetValue().c_str()));
  char array2[a2.GetValue().size()];
  int v2 = atoi(strcpy(array2, a2.GetValue().c_str()));
  if (a1.GetOp().compare(">") == 0)
  {
    if (v2 > v1)
    {
      return true;
    }
  }

  if (a1.GetOp().compare("<") == 0)
  {
    if (v2 < v1)
      return true;
  }

  if (a1.GetOp().compare(">=") == 0)
  {
    if (v2 >= v1)
    {
      return true;
    }
  }

  if (a1.GetOp().compare("<=") == 0)
  {
    if (v2 <= v1)
      return true;
  }

  if (a1.GetOp().compare("=") == 0)
  {
    if (v2 == v1)
      return true;
  }

  return false;
}

Atribute InferenceEngine::Resolve(list<Rule> &conflicto)
{
  list<Rule>::iterator it;
  int priority = -1;
  for (list<Rule>::iterator i = conflicto.begin(); i != conflicto.end(); ++i)
  {
    // cout << i->GetSubRules()[i->GetNumSubRules()].GetAtribute() << " "
    //      << i->GetSubRules()[i->GetNumSubRules()].GetOp() << " "
    //      << i->GetSubRules()[i->GetNumSubRules()].GetValue() << endl;
    if (i->GetRulePriority() > priority)
    {
      priority = i->GetRulePriority();
      it = i;
    }
  }
  conflicto.erase(it);
  // cout << "Añadimos conclusion: " << it->GetSubRules()[it->GetNumSubRules()].GetAtribute() << " "
  //      << it->GetSubRules()[it->GetNumSubRules()].GetOp() << " "
  //      << it->GetSubRules()[it->GetNumSubRules()].GetValue() << endl;

  return it->GetSubRules()[it->GetNumSubRules()];
}
void InferenceEngine::Test(KnowledgeBase &kb, Config &c, FactsBase &fb)
{
  // cout << c.GetArgumentType("NSemillas") << endl;
  // cout << kb.GetDomain() << endl;
  // list<Rule> lista(kb.GetRules());
  // cout << endl;
  // for (list<Rule>::iterator it = lista.begin(); it != lista.end(); ++it)
  // {
  //   cout << "Número de subreglas: " << it->GetNumSubRules() << endl;
  //   Atribute *atr = it->GetSubRules();
  //   for (int i = 0; i <= it->GetNumSubRules(); i++)
  //   {
  //     cout << atr[i].GetAtribute() << " " << atr[i].GetOp() << " "
  //          << atr[i].GetValue() << endl;
  //   }
  //   cout << endl;
  // }
  // cout << lista.size() << endl;

  // list<Atribute> lista1 = fb.GetListFacts();
  // for (list<Atribute>::iterator it = lista1.begin(); it != lista1.end(); ++it)
  // {
  //   cout << it->GetAtribute() << " " << it->GetOp() << " "
  //        << it->GetValue() << endl;
  // }
}