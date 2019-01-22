

#ifndef HASHCODE18_CELL_H
#define HASHCODE18_CELL_H

//Une cellule est définie par ses coordonnées et un booléen indiquant si elle fait part d'un batiment ou non

class Cell {
public:
    Cell(const int x,const int y);
    int x;
    int y;
    bool isOccupied;
};


#endif //HASHCODE18_CELL_H
