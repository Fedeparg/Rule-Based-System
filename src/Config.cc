#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <map>

#include "Config.h"
#include "KnowledgeBase.h"

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
  rules_priority = new int[num_rules];
  int value = 0;

  for (int i = 0; i < num_rules; ++i)
  {
    config_file >> value;
    rules_priority[i] = value;
  }

  // SetRulesPriority(rules_priority);
}

void Config::ParseAttributes()
{
  string attribute, type;
  int num_attributes;
  config_file >> num_attributes;

  for (int i = 0; i < num_attributes; ++i)
  {
    config_file >> attribute;
    config_file >> type;
    map_arguments.insert(pair<string, string>(attribute, type));

    int tmp_size = type.size() + 1;
    char *tmp = new char[tmp_size];
    strcpy(tmp, type.c_str());
    if (strcmp(tmp, "NU") != 0)
    {
      config_file >> attribute;
    }
    delete[] tmp;
  }
  getline(config_file, attribute);
}

int Config::keywords(const string &keyword)
{
  int kyw_size = keyword.size() + 1;
  char *kyw = new char[kyw_size];
  strcpy(kyw, keyword.c_str());

  for (int i = 0; i < kyw_size; ++i)
  {
    kyw[i] = toupper(kyw[i]);
  }

  int result = 0;
  if (strcmp(kyw, "ATRIBUTOS") == 0)
  {
    result = 1;
  }
  else if (strcmp(kyw, "OBJETIVO") == 0)
  {
    result = 2;
  }
  else if (strcmp(kyw, "PRIORIDADES-REGLAS") == 0)
  {
    result = 3;
  }

  delete[] kyw;
  // If the keyword is not recognized, is ignored
  return result;
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
      ParseAttributes();
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

Config::Config(ifstream &config_file) : config_file(config_file)
{
  // Initialize the values
  SetRulesPriority(nullptr);
  SetGoal("");

  // Read the file
  ReadConfigFile();
  config_file.close();
}

Config::~Config()
{
  delete[] rules_priority;
}