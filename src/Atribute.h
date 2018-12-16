#ifndef SBR_ATRIBUTE_H
#define SBR_ATRIBUTE_H

#include <string>
#include <list>

// Stores the name of the atribute, the operator and the value assigned.
// Created as a class to improve the workflow when comparing rules with
// the FactsBase
class Atribute
{
 public:
  std::string GetAtribute();
  std::string GetOp();
  std::string GetValue();
  std::string GetType();
  std::list<int> GetRulesApplied();
  void SetAtribute(const std::string &word);
  void SetOp(const std::string &word);
  void SetValue(const std::string &word);
  void SetType(const std::string &word);
  void SetRulesApplied(std::list<int> rules);
  Atribute();
  ~Atribute();

 private:
  std::list<int> rules_applied;

  struct struc
  {
    std::string atribute;
    std::string op;
    std::string value;
    std::string type;
  };

  struc atribute;
};

#endif