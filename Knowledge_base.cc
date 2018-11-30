#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <list>
#include "Rule.hh"
#include "Config.hh"
#include "Knowledge_base.hh"
#include "Atribute.hh"

using namespace std;

void Knowledge_base::set_num_rules(int new_num_rules)
{
    num_rules = new_num_rules;
}

int Knowledge_base::get_num_rules()
{
    return num_rules;
}

void Knowledge_base::set_domain(const string &new_domain)
{
    domain = new_domain;
}

string Knowledge_base::get_domain()
{
    return domain;
}

list<Rule> Knowledge_base::get_rules()
{
    return rules;
}

void Knowledge_base::parse_rules(const string &line)
{
    istringstream s(line);
    string st1;
    int num_sub_rules = 1;
    Rule r;
    Atribute *table = new Atribute[10];
    int index = 0;

    // Ignore number of Rule
    s >> st1;
    while (s >> st1)
    {
        // Ignore first two words
        char tmp[st1.size()];
        strcpy(tmp, st1.c_str());
        if (strcmp(tmp, "y") == 0)
            num_sub_rules = num_sub_rules + 1;

        Atribute *atr = new Atribute();
        s >> st1;
        atr->set_atribute(st1);
        s >> st1;
        atr->set_op(st1);
        s >> st1;
        atr->set_value(st1);

        table[index] = *atr;
        index++;
    }

    r.set_sub_rules(*table);
    r.set_num_sub_rules(num_sub_rules);
    rules.push_back(r);
}

void Knowledge_base::read_knowledge_base()
{
    getline(file_kb, domain); // Store the domain
    file_kb >> num_rules;     // Store the number of rules

    string line = "";
    getline(file_kb, line); // Move pointer to next line
    for (int i = 0; i < num_rules; i++)
    {
        getline(file_kb, line);
        parse_rules(line);
    }

    file_kb.close();
}

Knowledge_base::Knowledge_base(ifstream &file_kb) : file_kb(file_kb)
{
    // Initialize the values
    set_num_rules(0);
    set_domain("");

    // Read the file
    read_knowledge_base();
}

Knowledge_base::~Knowledge_base()
{
}