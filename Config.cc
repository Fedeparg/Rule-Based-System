#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include "Config.hh"
#include "Knowledge_base.hh"

using namespace std;

string Config::get_argument_type(string key)
{
    return map_arguments.find(key)->second;
}

void Config::set_goal(const string &new_goal)
{
    goal = new_goal;
}

string Config::get_goal()
{
    return goal;
}

void Config::set_rules_priority(int *new_rules_priority)
{
    rules_priority = new_rules_priority;
}

int Config::get_rule_priority(int nrule)
{
    return rules_priority[nrule];
}

void Config::parse_rules_priority()
{
    int num_rules;
    config_file >> num_rules;
    int *rules_priority = new int[num_rules];
    int value = 0;
    for (int i = 0; i < num_rules; i++)
    {
        config_file >> value;
        rules_priority[i] = value;
    }
    set_rules_priority(rules_priority);
}

void Config::parse_atributes()
{
    string atribute, type;
    int num_atributes;
    config_file >> num_atributes;

    for (int i = 0; i < num_atributes; i++)
    {
        config_file >> atribute;
        config_file >> type;
        map_arguments.insert(pair<string, string>(atribute, type));

        int tmp_s = type.size() + 1;
        char tmp[tmp_s];
        strcpy(tmp, type.c_str());
        if (strcmp(tmp, "NU") != 0)
        {
            config_file >> atribute;
            // size_t pos = atribute.find("}") - 1;
            // atribute = atribute.substr(1, pos);
            // cout << atribute << endl;
        }
    }
    getline(config_file, atribute);
}

int Config::keywords(const string &keyword)
{
    int kyw_size = keyword.size() + 1;
    char kyw[kyw_size];
    strcpy(kyw, keyword.c_str());

    for (int i = 0; i < kyw_size; i++)
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

void Config::read_config_file()
{
    string str; // Buffer to place the lines

    // Read file line by line
    while (getline(config_file, str))
    {
        string goal;
        int keyword = keywords(str);
        switch (keyword)
        {
        case 1:
            parse_atributes();
            break;

        case 2:
            getline(config_file, goal);
            set_goal(goal);
            break;

        case 3:
            parse_rules_priority();
            break;

        default:
            break;
        }
    }

    // Close file
    config_file.close();
}

Config::Config(ifstream &file) : config_file(file)
{
    // Initialize the values
    set_rules_priority(nullptr);
    set_goal("");

    // Read the file
    read_config_file();
}

Config::~Config()
{
    delete[] rules_priority;
}