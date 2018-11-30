#ifndef ATRIBUTE_HH
#define ATRIBUTE_HH
#include <string>

class Atribute
{
private:
  struct struc
  {
    std::string atribute;
    std::string op;
    std::string value;
  };

  struc atribute;

public:
  std::string get_atribute();
  std::string get_op();
  std::string get_value();
  void set_atribute(const std::string &word);
  void set_op(const std::string &word);
  void set_value(const std::string &word);
  Atribute();
  ~Atribute();
};

#endif