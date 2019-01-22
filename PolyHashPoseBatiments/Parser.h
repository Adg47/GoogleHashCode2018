

#ifndef HASHCODE18_PARSER_H
#define HASHCODE18_PARSER_H

#include <string>
#include <vector>
using namespace std;
class Parser {

public:
    Parser(string name);
    vector<string> split(string str, char delimiter);

        string namefile;

};


#endif //HASHCODE18_PARSER_H
