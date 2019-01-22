
#include "Utility.h"
//Un utilitaire est représenté par un identifiant d'utilitaire , d'une dimension X et Y ainsi que d'une matrice à deux dimensions explicitant le plan exact de celui ci

Utility::Utility(int type,int x,int y,std::vector<std::vector<int> > matr, int idOrder)
{
    this->type=type;
    this->sizeX=x;
    this->sizeY=y;
    this->plan=matr;
	this->idOrder = idOrder;
}
Utility::Utility(int type, int x, int y) {
    this->sizeY=y;
    this->sizeX=x;
    this->type=type;
}
int Utility::returnType() const{
    return this->type;
}

int Utility::returnIdOrder() const {
	return this->idOrder;
}
/*Utility::~Utility() {
    for (int i = 0; i < this->sizeX; i++) {
        delete[] this->plan[i];
    }
    delete[] this->plan;
}*/