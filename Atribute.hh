#ifndef ATRIBUTE_HH
#define ATRIBUTE_HH
#include <string>

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