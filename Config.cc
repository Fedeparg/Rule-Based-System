#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "Config.hh"
#include "Knowledge_base.hh"

using namespace std;

void Config::set_goal(const string &goal)
{
    this->goal = goal;
}

string Config::get_goal()
{
    return this->goal;
}

void Config::set_rules_priority(int *rules_priority)
{
    this->rules_priority = rules_priority;
}

int *Config::get_rules_priority()
{
    return this->rules_priority;
}

void Config::parse_rules_priority(ifstream &config_file)
{
    string str;
    int num_rules;
    config_file >> num_rules;
    int *rules_priority = new int[num_rules];
    int value = 0;
    for(int i = 0; i < num_rules; i++)
    {
        config_file >> value;
        rules_priority[i] = value;
    }
    set_rules_priority(rules_priority);
}

void Config::parse_atributes(ifstream &config_file)
{
    string str;
    int num_atributes;
    config_file >> num_atributes;

    for (int i = 0; i < num_atributes; i++)
    {
        config_file >> str;
        cout << str << endl;
        char type[4];
        memset(type, 0, 4);
        config_file >> type;
        cout << type << endl;
        if (strcmp(type, "NU") != 0)
        {
            config_file >> str;
            size_t pos = str.find("}");
            str = str.substr(1, pos - 1);
            cout << str << endl;
        }
        cout << endl;
    }
    getline(config_file, str);
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

    return 0;
}

int Config::read_config_file(const string &file)
{
    ifstream config_file;   // var to read a file
    string str;             // Buffer to place the lines
    config_file.open(file); // Open the file

    // Check errors
    if (!config_file)
    {
        cerr << "Unable to open configuration file" << endl;
        return 1;
    }

    // Read file line by line
    while (getline(config_file, str))
    {
        string goal;
        int keyword = keywords(str);
        switch (keyword)
        {
        case 1:
            parse_atributes(config_file);
            break;

        case 2:
            getline(config_file, goal);
            set_goal(goal);
            break;

        case 3:
            parse_rules_priority(config_file);
            break;
            
        default:
            break;
        }
    }

    // Close file
    config_file.close();

    return 0;
}

Config::~Config(){
    delete[]rules_priority;
}