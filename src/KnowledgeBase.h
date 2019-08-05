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
  std::string GetGoal();
  void SetDomain(const std::string &new_domain);
  std::list<Rule> GetRules();
  void SetRules(std::list<Rule>);
  std::string GetDomain();
  KnowledgeBase(std::ifstream &file_kb, std::ifstream &file_conf);
  ~KnowledgeBase();

 private:
  std::list<Rule> rules;
  std::string domain;
  std::string goal;
  std::ifstream &file_kb;
  std::ifstream &file_conf;
  static int parsed_rules;
  Config conf;
  int num_rules;
  void ReadKnowledgeBase();
  void ParseRules(const std::string &rules);
};

#endif