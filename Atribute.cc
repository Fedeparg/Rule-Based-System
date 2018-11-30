#include "Atribute.hh"
#include <string>

using namespace std;

string Atribute::get_atribute()
{
    return atribute.atribute;
}

string Atribute::get_op()
{
    return atribute.op;
}

string Atribute::get_value()
{
    return atribute.value;
}

void Atribute::set_atribute(const std::string &word)
{
    atribute.atribute = word;
}
void Atribute::set_op(const std::string &word)
{
    atribute.op = word;
}
void Atribute::set_value(const std::string &word)
{
    atribute.value = word;
}

Atribute::Atribute()
{
}

Atribute::~Atribute()
{
}