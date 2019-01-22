//
// Created by Jeanne on 11/12/2018.
//
#include <vector>
#include "Batiment.h"

#ifndef HASHCODE18_UTILITY_H
#define HASHCODE18_UTILITY_H

//Un utilitaire est représenté par un identifiant d'utilitaire , d'une dimension X et Y ainsi que d'une matrice à deux dimensions explicitant le plan exact de celui ci
class Utility : public Batiment {
public:
    Utility(int type,int x,int y,std::vector<std::vector<int> > matr, int idOrder);
    Utility(int type, int x, int y);
   // ~Utility();
    virtual int returnType() const;

	int returnIdOrder() const;

    int type;
	int idOrder;

};


#endif //HASHCODE18_UTILITY_H
