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
  f1 << "-Dominio: " << kb.GetDomain() << endl;
  f1 << "-Atributo objetivo: \"" << c.GetGoal() << "\"" << endl
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
    facts.push_back(Resolve(conflict));
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
      f2 << "La suma de las anteriores reglas me llevan a la conclusion de que la solucion es: "
         << it->GetAtribute() << " " << it->GetOp() << " " << it->GetValue() << endl;
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

Atribute InferenceEngine::Resolve(list<Rule> &conflicto)
{
  f1 << "Las conclusiones de las siguientes reglas pueden ser incluidas:" << endl;
  list<Rule>::iterator it;
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
  f1 << "Tras comparar prioridades, añadimos la conclusion: '"
     << it->GetSubRules()[it->GetNumSubRules()].GetAtribute() << " "
     << it->GetSubRules()[it->GetNumSubRules()].GetOp() << " "
     << it->GetSubRules()[it->GetNumSubRules()].GetValue()
     << "' a la base de hechos." << endl
     << endl;

  f2 << "Deduzco la conclusion de la siguiente regla con la base de hechos actual: "
     << endl;
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

  return it->GetSubRules()[it->GetNumSubRules()];
}
void InferenceEngine::Test(KnowledgeBase &kb, Config &c, FactsBase &fb)
{
  // f1 << c.GetArgumentType("NSemillas") << endl;
  // f1 << kb.GetDomain() << endl;
  // list<Rule> lista(kb.GetRules());
  // f1 << endl;
  // for (list<Rule>::iterator it = lista.begin(); it != lista.end(); ++it)
  // {
  //   f1 << "Numero de subreglas: " << it->GetNumSubRules() << endl;
  //   Atribute *atr = it->GetSubRules();
  //   for (int i = 0; i <= it->GetNumSubRules(); i++)
  //   {
  //     f1 << atr[i].GetAtribute() << " " << atr[i].GetOp() << " "
  //          << atr[i].GetValue() << endl;
  //   }
  //   f1 << endl;
  // }
  // f1 << lista.size() << endl;

  // list<Atribute> lista1 = fb.GetListFacts();
  // for (list<Atribute>::iterator it = lista1.begin(); it != lista1.end(); ++it)
  // {
  //   f1 << it->GetAtribute() << " " << it->GetOp() << " "
  //        << it->GetValue() << endl;
  // }
}