

#ifndef HASHCODE18_PARSER_H
#define HASHCODE18_PARSER_H

#include <string>
#include <vector>
#include "Map.h"
using namespace std;
class Parser {

public:
    Parser(string name);
    vector<string> split(string str, char delimiter);

    Map *map;

};


#endif //HASHCODE18_PARSER_H
