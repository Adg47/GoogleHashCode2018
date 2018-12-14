//
// Created by anonymous on 13/12/18.
//

#ifndef HASHCODE18_PARSEROUT_H
#define HASHCODE18_PARSEROUT_H

#include <string>
#include <vector>
#include "Map.h"
using namespace std;
class ParserOut {

public:
    ParserOut(string name,Map *map);
    void Print(Map *map);
    int Score(Map  *map);
    vector<string> split(string str, char delimiter);
    bool Validation(Map *map);
    int nbBatiment;

};
#endif //HASHCODE18_PARSEROUT_H
