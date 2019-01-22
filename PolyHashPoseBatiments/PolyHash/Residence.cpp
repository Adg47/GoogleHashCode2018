
#include "Residence.h"

//Une résidence est représentée par un nombre d'habitants max , d'une dimension X et Y ainsi que d'une matrice à deux dimensions explicitant le plan exact de celle ci
Residence::Residence(int capacite,int x, int y,std::vector<std::vector<int> > matr, int idOrder)
{
    this->capacity=capacite;
    this->sizeX=x;
    this->sizeY=y;
    this->plan=matr;
    this->type=-4;
	this->idOrder = idOrder;
}
Residence::Residence(int capacite, int x, int y) {
    this->capacity = capacite;
    this->sizeX = x;
    this->sizeY = y;
    this->type=-4;
}
int Residence::returnType() const{
    return this->type;
}

int Residence::returnIdOrder() const {
	return this->idOrder;
}
/*Residence::~Residence() {
    for (int i = 0; i < this->sizeX; i++) {
        delete[] this->plan[i];
    }
    delete[] this->plan;
}*/