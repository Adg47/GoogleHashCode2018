#include "Utility.h"
#include "Residence.h"
#include "Map.h"
//Une map est représentée par des dimensions : X et Y , une distance de marche maximale pour les habitants ainsi qu'un nombre de batiments la peuplant
Map::Map(int x,int y,int dist,int nbrBat)
{

    this->sizeX=x;
    this->sizeY=y;
    this->distMax=dist;
    this->nbrBuild=nbrBat;

    this->tabCell.assign(x,std::vector<int>(y,-1));

}