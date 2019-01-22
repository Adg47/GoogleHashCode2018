#ifndef HASHCODE18_BATIMENT_H
#define HASHCODE18_BATIMENT_H


#include <vector>

class Batiment {

public:
	Batiment();
	Batiment(int x, int y, std::vector<std::vector<int> > matr, int idOrder);
	std::vector<std::vector<int> > plan;
	int sizeX;
	int sizeY;
	int type;
	int capacity;
	int idOrder;
	virtual int returnType() const;

	virtual int returnIdOrder() const;

	std::vector<int> posX;
	std::vector<int> posY;
};


#endif //HASHCODE18_BATIMENT_H