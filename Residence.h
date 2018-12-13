

#ifndef HASHCODE18_RESIDENCE_H
#define HASHCODE18_RESIDENCE_H

//Une résidence est représentée par un nombre d'habitants max , d'une dimension X et Y ainsi que d'une matrice à deux dimensions explicitant le plan exact de celle ci

#include <vector>

class Residence {
public:
    Residence(int capacite,int x,int y,std::vector<std::vector<int> > matr);
    Residence(int capacite, int x, int y);
    //~Residence();

    int capacity;
    int sizeX;
    int sizeY;
    std::vector<std::vector<int> > plan;
};


#endif //HASHCODE18_RESIDENCE_H
