//
// Created by anonymous on 13/12/18.
//

#ifndef HASHCODE18_BATIMENT_H
#define HASHCODE18_BATIMENT_H


#include <vector>

class Batiment {

public:
    Batiment();
    Batiment(int x,int y,std::vector<std::vector<int> > matr);
    std::vector<std::vector<int> > plan;
    int sizeX;
    int sizeY;
    int type;
    int capacity;
    virtual int returnType() const;

    std::vector<int> posX;
    std::vector<int> posY;
};


#endif //HASHCODE18_BATIMENT_H
