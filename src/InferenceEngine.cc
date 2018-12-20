#include <iostream>
#include <list>
#include <iterator>
#include <set>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#include "InferenceEngine.h"
#include "Attribute.h"

using namespace std;

extern ofstream f1;
extern ofstream f2;

// Main algorithm for the program
bool InferenceEngine::ForwardChaining(KnowledgeBase &kb, Config &c, FactsBase &fb)
{
  // Put the requested things on the files
  f1 << "-Dominio: " << kb.GetDomain() << endl
     << "-Atributo objetivo: \"" << c.GetGoal() << "\"" << endl
     << endl;

  f2 << "-Dominio: " << kb.GetDomain() << endl;
  f2 << "-Atributo objetivo: \"" << c.GetGoal() << "\"" << endl
     << endl;

  // Gets the list of facts
  list<Attribute> facts(fb.GetListFacts());

  // Shows the starting facts base
  f1 << "La base de hechos inicial es la siguiente: " << endl;
  for (list<Attribute>::iterator it = facts.begin(); it != facts.end(); ++it)
  {
    f1 << "- " << it->GetAttribute() << " "
       << it->GetOp() << " " << it->GetValue() << endl;
  }
  f1 << endl;

  // Creates and fill ConflictSet
  list<Rule> rules(kb.GetRules());
  list<Rule> conflict;

  // Search for rules to fill conflict set (represented by a list)
  SearchRules(conflict, rules, facts);

  // Start to apply rules
  while (!GoalFound(facts, c.GetGoal()) && !conflict.empty())
  {
    // We resolve the conflict set and adds it as a new fact
    facts.push_front(Resolve(conflict, facts));

    f1 << "La base de hechos queda actualizada con los siguientes datos:" << endl;

    // Shows the update in the facts base
    for (list<Attribute>::iterator it = facts.begin(); it != facts.end(); ++it)
    {
      f1 << "- " << it->GetAttribute() << " "
         << it->GetOp() << " " << it->GetValue() << endl;
    }
    f1 << endl;

    // If the goal is still not found, search for rules again and repeat
    if (!GoalFound(facts, c.GetGoal()))
    {
      SearchRules(conflict, rules, facts);
    }
    // In other case, we re-build the conclusion, showing the steps followed
    else
    {
      WriteConclusion(facts, kb.GetRules());
      // Returns true because the goal was found
      return true;
    }
  }

  // If we got here, it's because we could not find a solution, so we should
  // inform the user in BOTH files (just in case the user thinks the program
  // is broken)
  f1 << endl
     << "No quedan reglas posibles que comparar con los hechos actuales. "
        "No se ha podido llegar a una conclusion"
     << endl;

  f2 << endl
     << "No quedan reglas posibles que comparar con los hechos actuales. "
        "No se ha podido llegar a una conclusion"
     << endl;
  // Returns false because no goals were found
  return false;
}

// Checks if the goal has been found
bool InferenceEngine::GoalFound(list<Attribute> &facts, string goal)
{
  for (list<Attribute>::iterator it = facts.begin(); it != facts.end(); ++it)
  {
    if (it->GetAttribute().compare(goal) == 0)
    {
      f1 << "Solucion: " << it->GetAttribute() << " " << it->GetOp() << " " << it->GetValue() << endl;
      return true;
    }
  }
  return false;
}

// Search for rules that can be applied with the current facts base
void InferenceEngine::SearchRules(list<Rule> &conflict, list<Rule> &rules, list<Attribute> &facts)
{
  f1 << "Analizando posibles reglas a aplicar con la configuracion actual..." << endl;
  int j = 1;
  for (list<Rule>::iterator it = rules.begin(); it != rules.end(); ++it)
  {
    Attribute *subrules = it->GetSubRules();

    bool flag = true;
    for (int i = 0; i < it->GetNumSubRules(); ++i)
    {
      bool flag_condition = false;

      for (list<Attribute>::iterator fact = facts.begin(); fact != facts.end(); ++fact)
      {
        if (CompareAttributes(subrules[i], *fact))
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

// Compare 2 attributes to check if the first one meets the requirements of
// the second
bool InferenceEngine::CompareAttributes(Attribute &a1, Attribute &a2)
{
  if (CompareJustAttributes(a1, a2))
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

// Turns an operation into code. Used for numeric attributes
bool InferenceEngine::OpToCode(Attribute &a1, Attribute &a2)
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

// Function to compare only the attributes. Returns true if they refer to the
// same attribute (as text). False otherwise
bool InferenceEngine::CompareJustAttributes(Attribute &a1, Attribute &a2)
{
  if (a1.GetAttribute().compare(a2.GetAttribute()) == 0)
  {
    return true;
  }
  return false;
}

// With the rules in conflict, we select which rule to be applied, based on
// priority and order of appearence
Attribute InferenceEngine::Resolve(list<Rule> &conflicto, list<Attribute> &facts)
{
  f1 << "Las conclusiones de las siguientes reglas pueden ser incluidas:" << endl;
  list<Rule>::iterator it;
  Rule r;
  int priority = -1;
  for (list<Rule>::iterator i = conflicto.begin(); i != conflicto.end(); ++i)
  {

    for (int j = 0; j <= i->GetNumSubRules(); j++)
    {
      if (j == 0)
        f1 << "- ";
      f1 << i->GetSubRules()[j].GetAttribute() << " "
         << i->GetSubRules()[j].GetOp() << " "
         << i->GetSubRules()[j].GetValue();
      if (j < i->GetNumSubRules() - 1)
      {
        f1 << " Y ";
      }
      else if (j == i->GetNumSubRules() - 1)
      {
        f1 << " ENTONCES ";
      }
    }
    f1 << endl;
    if (i->GetRulePriority() > priority)
    {
      priority = i->GetRulePriority();
      it = i;
    }
  }
  conflicto.erase(it);
  r = *it;

  // Adding the rules applied to the new attribute used as fact
  list<int> list_this;
  for (int i = 0; i < r.GetNumSubRules(); i++)
  {
    list<int> temp;
    for (list<Attribute>::iterator fact = facts.begin(); fact != facts.end(); ++fact)
    {
      if (CompareJustAttributes(r.GetSubRules()[i], *fact))
      {
        temp = fact->GetRulesApplied();
        break;
      }
    }
    for (list<int>::iterator iter = temp.begin(); iter != temp.end(); ++iter)
    {
      list_this.push_back(*iter);
    }
  }
  list_this.push_back(r.GetRuleNumber());
  r.GetSubRules()[r.GetNumSubRules()].SetRulesApplied(list_this);

  f1 << "Tras comparar prioridades, añadimos la conclusion: '"
     << r.GetSubRules()[r.GetNumSubRules()].GetAttribute() << " "
     << r.GetSubRules()[r.GetNumSubRules()].GetOp() << " "
     << r.GetSubRules()[r.GetNumSubRules()].GetValue()
     << "' a la base de hechos." << endl
     << endl;

  return r.GetSubRules()[r.GetNumSubRules()];
}

// Exports to file 2 the conclusion from the begining, only including rules
// that lead us to the final goal
void InferenceEngine::WriteConclusion(list<Attribute> facts, list<Rule> rules)
{
  Attribute final_attribute = facts.front();
  list<int> rules_final = final_attribute.GetRulesApplied();

  f2 << "He seguido el siguiente razonamiento para alcanzar la conclusion. La "
     << "ultima regla se corresponde con la que devuelve la conclusion:" << endl;

  for (list<int>::iterator i = rules_final.begin(); i != rules_final.end(); ++i)
  {
    list<Rule>::iterator it = rules.begin();
    advance(it, *i - 1);
    for (int j = 0; j <= it->GetNumSubRules(); j++)
    {
      if (j == 0)
        f2 << "- ";
      f2 << it->GetSubRules()[j].GetAttribute() << " "
         << it->GetSubRules()[j].GetOp() << " "
         << it->GetSubRules()[j].GetValue();
      if (j < it->GetNumSubRules() - 1)
      {
        f2 << " Y ";
      }
      else if (j == it->GetNumSubRules() - 1)
      {
        f2 << " ENTONCES ";
      }
    }
    f2 << endl;
  }
}
