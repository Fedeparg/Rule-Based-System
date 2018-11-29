#include <iostream>
#include "Config.hh"
#include <string>
#include "Knowledge_base.hh"

using namespace std;

int main(int argc, char const *argv[])
{
    Config *c = new Config();
    if (c->read_config_file(argv[2]))
    {
        cerr << "Could not parse configuration file" << endl;
        exit(1);
    }
    return 0;
}
