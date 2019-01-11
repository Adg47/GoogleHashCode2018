

#ifndef HASHCODE18_RESIDENCE_H
#define HASHCODE18_RESIDENCE_H

//Une résidence est représentée par un nombre d'habitants max , d'une dimension X et Y ainsi que d'une matrice à deux dimensions explicitant le plan exact de celle ci

#include "Batiment.h"
#include <vector>

class Residence : public Batiment{
public:
    Residence(int capacite,int x,int y,std::vector<std::vector<int> > matr,int idOrder);
    Residence(int capacite, int x, int y);
    //~Residence();
    virtual int returnType() const;
	int returnIdOrder() const;
    int type;
	int idOrder;
};


#endif //HASHCODE18_RESIDENCE_H
