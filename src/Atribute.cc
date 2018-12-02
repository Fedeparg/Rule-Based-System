#include "Atribute.h"
#include <string>
#include <string.h>

using namespace std;

string Atribute::GetAtribute()
{
  return atribute.atribute;
}

string Atribute::GetOp()
{
  return atribute.op;
}

string Atribute::GetValue()
{
  return atribute.value;
}

void Atribute::SetAtribute(const std::string &word)
{
  atribute.atribute = word;
}
void Atribute::SetOp(const std::string &word)
{
  atribute.op = word;
}
void Atribute::SetValue(const std::string &word)
{
  atribute.value = word;
}

Atribute::Atribute()
{
  memset(&atribute, 0, sizeof(atribute));
}

Atribute::~Atribute()
{
}