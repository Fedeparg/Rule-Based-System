#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include "Config.hh"
#include "Knowledge_base.hh"
#include "Rule.hh"

using namespace std;

int main(int argc, char const *argv[])
{
    ifstream file_kb(argv[1]);
    ifstream config_file(argv[2]);

    if (!config_file || !file_kb)
    {
        cerr << "Unable to open file" << endl;
        return 1;
    }

    Config *c = new Config(config_file);
    Knowledge_base *kb = new Knowledge_base(file_kb);

        list<Rule> lista = kb->get_rules();
    Rule r = lista.front();
    for (list<Rule>::iterator it = lista.begin(); it != lista.end(); ++it)
    {
        cout << "Número de subreglas " << it->get_num_sub_rules() << endl;
        cout << it->get_sub_rules()[it->get_num_sub_rules()].get_atribute();
        cout << " " << it->get_sub_rules()[it->get_num_sub_rules()].get_op();
        cout << " " << it->get_sub_rules()[it->get_num_sub_rules()].get_value() << endl;
    }
    cout << lista.size();

    delete c;
    delete kb;
    return 0;
}
