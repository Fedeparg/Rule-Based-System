#ifndef CONFIG_HH
#define CONFIG_HH
#include <string>
#include <map>

class Config
{
 public:
  void SetGoal(const std::string &new_goal);
  std::string GetGoal();
  std::ifstream& GetFile();
  void SetRulesPriority(int *new_rules_priority);
  int GetRulePriority(int nrule);
  std::string GetArgumentType(std::string);
  Config(std::ifstream &file);
  ~Config();

 private:
  int *rules_priority;
  std::string goal;
  std::map<std::string, std::string> map_arguments;
  std::ifstream &config_file;
  void ParseAtributes();
  void ParseRulesPriority();
  int keywords(const std::string &keyword);
  void ReadConfigFile();
};

#endif