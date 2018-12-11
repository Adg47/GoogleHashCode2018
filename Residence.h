

#ifndef HASHCODE18_RESIDENCE_H
#define HASHCODE18_RESIDENCE_H

//Une résidence est représentée par un nombre d'habitants max , d'une dimension X et Y ainsi que d'une matrice à deux dimensions explicitant le plan exact de celle ci

class Residence {
public:
    Residence(int capacite,int x,int y,int **matr);
    Residence(int capacite, int x, int y);

        int capacity;
    int sizeX;
    int sizeY;
    int **plan;
};


#endif //HASHCODE18_RESIDENCE_H
