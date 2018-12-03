#ifndef SBR_KNOWLEDGEBASE_H
#define SBR_KNOWLEDGEBASE_H

#include <list>
#include <string>

#include "Rule.h"
#include "Config.h"

// Reads the Knowledge base that store the rules and are used by the inference
// engine
class KnowledgeBase
{
 public:
  void SetNumRules(int new_num_rules);
  int GetNumRules();
  void SetDomain(const std::string &new_domain);
  std::list<Rule> GetRules();
  void SetRules(std::list<Rule>);
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