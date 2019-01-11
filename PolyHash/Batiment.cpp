#include "Batiment.h"

Batiment::Batiment(int x, int y, std::vector<std::vector<int> > matr, int idOrder) {
	this->sizeX = x;
	this->sizeY = y;
	this->plan = matr;
	this->idOrder = idOrder;
}
int Batiment::returnType() const {

	return this->type;
}

int Batiment::returnIdOrder() const {
	return this->idOrder;
}


Batiment::Batiment() {

}
