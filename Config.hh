#ifndef CONFIG_HH
#define CONFIG_HH
#include <string>

class Config
{
  private:
    int *rules_priority;
    std::string goal;
    void parse_atributes(std::ifstream &config_file);
    void parse_rules_priority(std::ifstream &config_file);
    int keywords(const std::string &keyword);

  public:
    int read_config_file(const std::string &file);
    void set_goal(const std::string &goal);
    std::string get_goal();
    void set_rules_priority(int *rules_priority);
    int *get_rules_priority();
    ~Config();
};

#endif