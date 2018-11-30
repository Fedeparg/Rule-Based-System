#ifndef KNOWLEDGE_BASE_HH
#define KNOWLEDGE_BASE_HH
#include <list>
#include <string>
#include "Rule.hh"

class Knowledge_base
{
private:
  std::list<Rule> rules;
  std::string domain;
  std::ifstream &file_kb;
  int num_rules;
  void read_knowledge_base();
  void parse_rules(const std::string &rules);

public:
  void set_num_rules(int new_num_rules);
  int get_num_rules();
  void set_domain(const std::string &new_domain);
  std::list<Rule> get_rules();
  std::string get_domain();
  Knowledge_base(std::ifstream &file_kb);
  ~Knowledge_base();
};

#endif