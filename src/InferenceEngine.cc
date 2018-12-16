#include <iostream>
#include <list>
#include <iterator>
#include <set>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>

#include "InferenceEngine.h"
#include "Atribute.h"

using namespace std;

extern ofstream f1;
extern ofstream f2;

bool InferenceEngine::ForwardChaining(KnowledgeBase &kb, Config &c, FactsBase &fb)
{
  // Get the list of facts
  f1 << "-Dominio: " << kb.GetDomain() << endl
     << "-Atributo objetivo: \"" << c.GetGoal() << "\"" << endl
     << endl;

  f2 << "-Dominio: " << kb.GetDomain() << endl;
  f2 << "-Atributo objetivo: \"" << c.GetGoal() << "\"" << endl
     << endl;

  list<Atribute> facts(fb.GetListFacts());

  f1 << "La base de hechos inicial es la siguiente: " << endl;
  for (list<Atribute>::iterator it = facts.begin(); it != facts.end(); ++it)
  {
    f1 << "- " << it->GetAtribute() << " "
       << it->GetOp() << " " << it->GetValue() << endl;
  }
  f1 << endl;

  // Create and fill ConflictSet
  list<Rule> rules(kb.GetRules());
  list<Rule> conflict;

  // Search for rules
  SearchRules(conflict, rules, facts);

  while (!GoalFound(facts, c.GetGoal()) && !conflict.empty())
  {
    facts.push_front(Resolve(conflict, facts));

    f1 << "La base de hechos queda actualizada con los siguientes datos:" << endl;

    for (list<Atribute>::iterator it = facts.begin(); it != facts.end(); ++it)
    {
      f1 << "- " << it->GetAtribute() << " "
         << it->GetOp() << " " << it->GetValue() << endl;
    }
    f1 << endl;

    if (!GoalFound(facts, c.GetGoal()))
      SearchRules(conflict, rules, facts);

    else
    {
      WriteConclusion(facts, kb.GetRules());
      return true;
    }
  }

  if (GoalFound(facts, c.GetGoal()))
  {
    return true;
  }
  f1 << endl
     << "No quedan reglas posibles que comparar con los hechos actuales. "
        "No se ha podido llegar a una conclusion"
     << endl;

  f2 << endl
     << "No quedan reglas posibles que comparar con los hechos actuales. "
        "No se ha podido llegar a una conclusion"
     << endl;
  return false;
}

bool InferenceEngine::GoalFound(list<Atribute> &facts, string goal)
{
  for (list<Atribute>::iterator it = facts.begin(); it != facts.end(); ++it)
  {
    if (it->GetAtribute().compare(goal) == 0)
    {
      f1 << "Solucion: " << it->GetAtribute() << " " << it->GetOp() << " " << it->GetValue() << endl;
      return true;
    }
  }
  return false;
}

void InferenceEngine::SearchRules(list<Rule> &conflict, list<Rule> &rules, list<Atribute> &facts)
{
  f1 << "Analizando posibles reglas a aplicar con la configuracion actual..." << endl;
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

bool InferenceEngine::CompareJustAtributes(Atribute &a1, Atribute &a2)
{
  if (a1.GetAtribute().compare(a2.GetAtribute()) == 0)
  {
    return true;
  }
  return false;
}

Atribute InferenceEngine::Resolve(list<Rule> &conflicto, list<Atribute> &facts)
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
      f1 << i->GetSubRules()[j].GetAtribute() << " "
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

  /* EN OBRAS */
  list<int> list_this;
  for (int i = 0; i < r.GetNumSubRules(); i++)
  {
    list<int> temp;
    for (list<Atribute>::iterator fact = facts.begin(); fact != facts.end(); ++fact)
    {
      if (CompareJustAtributes(r.GetSubRules()[i], *fact))
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

  /* EN OBRAS */

  f1 << "Tras comparar prioridades, añadimos la conclusion: '"
     << r.GetSubRules()[r.GetNumSubRules()].GetAtribute() << " "
     << r.GetSubRules()[r.GetNumSubRules()].GetOp() << " "
     << r.GetSubRules()[r.GetNumSubRules()].GetValue()
     << "' a la base de hechos." << endl
     << endl;

  return r.GetSubRules()[r.GetNumSubRules()];
}

void InferenceEngine::WriteConclusion(list<Atribute> facts, list<Rule> rules)
{
  Atribute final_atribute = facts.front();
  list<int> rules_final = final_atribute.GetRulesApplied();

  f2 << "He seguido el siguiente razonamiento para alcanzar la conclusión. La última regla se corresponde con la que devuelve la conclusión:" << endl;

  for (list<int>::iterator i = rules_final.begin(); i != rules_final.end(); ++i)
  {
    list<Rule>::iterator it = rules.begin();
    advance(it, *i - 1);
    for (int j = 0; j <= it->GetNumSubRules(); j++)
    {
      if (j == 0)
        f2 << "- ";
      f2 << it->GetSubRules()[j].GetAtribute() << " "
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

// void InferenceEngine::Test(KnowledgeBase &kb, Config &c, FactsBase &fb)
// {
//   f1 << c.GetArgumentType("NSemillas") << endl;
//   f1 << kb.GetDomain() << endl;
//   list<Rule> lista(kb.GetRules());
//   f1 << endl;
//   for (list<Rule>::iterator it = lista.begin(); it != lista.end(); ++it)
//   {
//     f1 << "Numero de subreglas: " << it->GetNumSubRules() << endl;
//     Atribute *atr = it->GetSubRules();
//     for (int i = 0; i <= it->GetNumSubRules(); i++)
//     {
//       f1 << atr[i].GetAtribute() << " " << atr[i].GetOp() << " "
//            << atr[i].GetValue() << endl;
//     }
//     f1 << endl;
//   }
//   f1 << lista.size() << endl;

//   list<Atribute> lista1 = fb.GetListFacts();
//   for (list<Atribute>::iterator it = lista1.begin(); it != lista1.end(); ++it)
//   {
//     f1 << it->GetAtribute() << " " << it->GetOp() << " "
//          << it->GetValue() << endl;
//   }
// }