
#include "Utility.h"
//Un utilitaire est représenté par un identifiant d'utilitaire , d'une dimension X et Y ainsi que d'une matrice à deux dimensions explicitant le plan exact de celui ci

Utility::Utility(int type,int x,int y,int **matr)
{
    this->typeUtil=type;
    this->sizeX=x;
    this->sizeY=y;
    this->plan=matr;
}
Utility::Utility(int type, int x, int y) {
    this->sizeY=y;
    this->sizeX=x;
    this->typeUtil=type;
}