#ifndef SBR_ATRIBUTE_H
#define SBR_ATRIBUTE_H

#include <string>

// Stores the name of the atribute, the operator and the value assigned.
// Created as a class to improve the workflow when comparing rules with
// the FactsBase
class Atribute
{
 public:
  std::string GetAtribute();
  std::string GetOp();
  std::string GetValue();
  void SetAtribute(const std::string &word);
  void SetOp(const std::string &word);
  void SetValue(const std::string &word);
  Atribute();
  ~Atribute();

 private:
  struct struc
  {
    std::string atribute;
    std::string op;
    std::string value;
  };

  struc atribute;
};

#endif