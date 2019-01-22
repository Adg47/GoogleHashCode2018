//
// Created by anonymous on 13/12/18.
//

#include "Batiment.h"

Batiment::Batiment(int x, int y, std::vector<std::vector<int> > matr) {
    this->sizeX =x ;
    this->sizeY = y;
    this->plan = matr;
}
int Batiment::returnType() const{

    return this->type;
}


Batiment::Batiment() {

}
