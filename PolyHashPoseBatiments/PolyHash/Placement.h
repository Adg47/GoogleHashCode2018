#ifndef HASHCODE18_PLACEMENT_H
#define HASHCODE18_PLACEMENT_H

#include <string>
#include <vector>
#include "Map.h"
#include <fstream>
using namespace std;
class Placement {

public:
	Placement(Map *map, int nbResidence, int nbDivision);

	Map *map;
	vector<Batiment*> residences;
	vector<Batiment*> utilitaires;
    Batiment* getMaxCapacite();
	Batiment* getMinPerimetre();
	int nbPBatimentPlace;
	int tmpPosUtilitaire;
	int tmpPosResidence;
	int nbDivision;
	//vector<Batiment*> batimentPlace;
	//cette méthode place le bâtiment, on suppose qu'on sait où est-ce on devrait la mettre (posX,posY)
	void Place_batiment(Batiment *batiment, int posX, int posY,const int nbDivision,int sizeMap);
	vector<Batiment*> placerBatiment();
	bool isOkForPlacement(Batiment *batiment, int posX, int posY);
	void placeUtilitaire(int posFirstX, int posFirstY, int fixe, bool isPlusFirst, int distMax);
	void placeUtilitairesSurContour(int posFirstX, int posFirstY,int distMax);

private:


};

#endif //HASHCODE18_PLACEMENT_H