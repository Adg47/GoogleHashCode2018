

#include "Cell.h"

//Une cellule est définie par ses coordonnées et un booléen indiquant si elle fait part d'un batiment ou non
Cell::Cell(int x,int y,int value)
{
    this->x=x;
    this->y=y;
    this->value = value;
    this->isOccupied=false;
}