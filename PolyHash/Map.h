
#ifndef HASHCODE18_MAP_H
#define HASHCODE18_MAP_H

#include "Residence.h"
#include "Utility.h"
#include "Cell.h"
#include <vector>
//Une map est représentée par des dimensions : X et Y , une distance de marche maximale pour les habitants ainsi qu'un nombre de batiments la peuplant
class Map {

public:
    Map(int x,int y,int dist,int nbrBuild);

//    Residence *myResidences[1000];
 //   Utility *myUtility[1000];
    int sizeX;
    int sizeY;
    int distMax;
    int nbrBuild;
	int nbResidence;
    /*std::vector<Residence> listeResidences;
    std::vector<Utility> listeUtility;*/
    std::vector<Batiment*> listeBatiments;
    std::vector<std::vector<int> > tabCell;
    int** tab;
    //std::vector <std::vector<Cell> > listeCell;
    // vector <vector<int> > mymap(stoi(sep[1],&sz),vector<int>(stoi(sep[2],&sz),0));
 //  void addResidence(const Residence r);
   // void addUtility(const Utility u);
};


#endif //HASHCODE18_MAP_H
