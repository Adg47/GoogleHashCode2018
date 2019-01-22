//
// Created by Jeanne on 11/12/2018.
//

#ifndef HASHCODE18_UTILITY_H
#define HASHCODE18_UTILITY_H

//Un utilitaire est représenté par un identifiant d'utilitaire , d'une dimension X et Y ainsi que d'une matrice à deux dimensions explicitant le plan exact de celui ci
class Utility {
public:
    Utility(int type,int x,int y,int **matr);
    Utility(int type, int x, int y);

    int typeUtil;
    int sizeX;
    int sizeY;
    int **plan;

};


#endif //HASHCODE18_UTILITY_H
