#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <map>

#include "Config.hh"
#include "KnowledgeBase.hh"

using namespace std;

string Config::GetArgumentType(string key)
{
  return map_arguments.find(key)->second;
}

void Config::SetGoal(const string &new_goal)
{
  goal = new_goal;
}

string Config::GetGoal()
{
  return goal;
}

ifstream &Config::GetFile()
{
  return config_file;
}

void Config::SetRulesPriority(int *new_rules_priority)
{
  rules_priority = new_rules_priority;
}

int Config::GetRulePriority(int nrule)
{
  return rules_priority[nrule];
}

void Config::ParseRulesPriority()
{
  int num_rules = 0;
  config_file >> num_rules;
  int *rules_priority = new int[num_rules];
  int value = 0;

  for (int i = 0; i < num_rules; ++i)
  {
    config_file >> value;
    rules_priority[i] = value;
  }

  SetRulesPriority(rules_priority);
}

void Config::ParseAtributes()
{
  string atribute, type;
  int num_atributes;
  config_file >> num_atributes;

  for (int i = 0; i < num_atributes; ++i)
  {
    config_file >> atribute;
    config_file >> type;
    map_arguments.insert(pair<string, string>(atribute, type));

    int tmp_size = type.size() + 1;
    char tmp[tmp_size];
    strcpy(tmp, type.c_str());
    if (strcmp(tmp, "NU") != 0)
    {
      config_file >> atribute;
    }
  }
  getline(config_file, atribute);
}

int Config::keywords(const string &keyword)
{
  int kyw_size = keyword.size() + 1;
  char kyw[kyw_size];
  strcpy(kyw, keyword.c_str());

  for (int i = 0; i < kyw_size; ++i)
  {
    kyw[i] = toupper(kyw[i]);
  }

  if (strcmp(kyw, "ATRIBUTOS") == 0)
  {
    return 1;
  }
  else if (strcmp(kyw, "OBJETIVO") == 0)
  {
    return 2;
  }
  else if (strcmp(kyw, "PRIORIDADES-REGLAS") == 0)
  {
    return 3;
  }

  // If the keyword is not recognized, is ignored
  return 0;
}

void Config::ReadConfigFile()
{
  string line; // Buffer to place the lines

  // Read file line by line
  while (getline(config_file, line))
  {
    string goal;
    int keyword = keywords(line);
    switch (keyword)
    {
    case 1:
      ParseAtributes();
      break;

    case 2:
      getline(config_file, goal);
      SetGoal(goal);
      break;

    case 3:
      ParseRulesPriority();
      break;

    default:
      break;
    }
  }
}

Config::Config(ifstream &file) : config_file(file)
{
  // Initialize the values
  SetRulesPriority(nullptr);
  SetGoal("");

  // Read the file
  ReadConfigFile();
}

Config::~Config()
{
  delete[] rules_priority;
}