#ifndef SBR_ATTRIBUTE_H
#define SBR_ATTRIBUTE_H

#include <string>
#include <list>

// Stores the name of the attribute, the operator and the value assigned.
// Created as a class to improve the workflow when comparing rules with
// the FactsBase
class Attribute
{
 public:
  std::string GetAttribute();
  std::string GetOp();
  std::string GetValue();
  std::string GetType();
  std::list<int> GetRulesApplied();
  void SetAttribute(const std::string &word);
  void SetOp(const std::string &word);
  void SetValue(const std::string &word);
  void SetType(const std::string &word);
  void SetRulesApplied(std::list<int> rules);
  Attribute();
  ~Attribute();

 private:
  std::list<int> rules_applied;

  struct struc
  {
    std::string attribute;
    std::string op;
    std::string value;
    std::string type;
  };

  struc attribute;
};

#endif