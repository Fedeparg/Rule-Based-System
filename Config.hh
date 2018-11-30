#ifndef CONFIG_HH
#define CONFIG_HH
#include <string>
#include <map>

class Config
{
private:
  int *rules_priority;
  std::string goal;
  std::map<std::string, std::string> map_arguments;
  std::ifstream &config_file;
  void parse_atributes();
  void parse_rules_priority();
  int keywords(const std::string &keyword);
  void read_config_file();

public:
  void set_goal(const std::string &new_goal);
  std::string get_goal();
  void set_rules_priority(int *new_rules_priority);
  int get_rule_priority(int nrule);
  std::string get_argument_type(std::string);
  Config(std::ifstream &file);
  ~Config();
};

#endif