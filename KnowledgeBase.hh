#ifndef KnowledgeBase_HH
#define KnowledgeBase_HH
#include <list>
#include <string>

#include "Rule.hh"
#include "Config.hh"

class KnowledgeBase
{
public:
  void SetNumRules(int new_num_rules);
  int GetNumRules();
  void SetDomain(const std::string &new_domain);
  std::list<Rule> GetRules();
  std::string GetDomain();
  KnowledgeBase(std::ifstream &file_kb, Config &conf);
  ~KnowledgeBase();

private:
  std::list<Rule> rules;
  std::string domain;
  std::ifstream &file_kb;
  static int parsed_rules;
  Config conf;
  int num_rules;
  void ReadKnowledgeBase();
  void ParseRules(const std::string &rules);
};

#endif