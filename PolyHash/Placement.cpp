/*#include "Placement.h"
#include "Batiment.h"
#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include <fstream>

ofstream OutFile("test.out");
int nbBatimentPose = 0;

Placement::Placement(Map *map, int nbResidence)
{
	this->map = map;
	this->tmpPosUtilitaire = 0;
	for (int i = 0; i < nbResidence; i++) {
		this->residences.push_back(map->listeBatiments.at(i));
	}
	for (int i = nbResidence; i < map->listeBatiments.size(); i++) {
		this->utilitaires.push_back(map->listeBatiments.at(i));
	}
}

// Ajouter retourner une liste si on veut tester plusieurs points de départ
Batiment * Placement::getMaxCapacite()
{
	int maxCapacite = 0;
	Batiment *residence = nullptr;
	for (int i = 0; i < this->residences.size(); i++) {
		if (this->residences.at(i) != nullptr) {
			if (maxCapacite < this->residences.at(i)->capacity) {
				maxCapacite = this->residences.at(i)->capacity;
				residence = this->residences.at(i);
				//this->residences.at(i) = nullptr;
			}
		}
	}
	return residence;
}


Batiment* Placement::getMinPerimetre()
{

	int minPerimetre = 999999;
	Batiment *utilitaire = nullptr;
	cout << endl;
	for (int i = this->tmpPosUtilitaire; i < utilitaires.size(); i++) {

		if (minPerimetre > (this->utilitaires.at(i)->sizeX*this->utilitaires.at(i)->sizeY))
		{
			minPerimetre = this->utilitaires.at(i)->sizeX*this->utilitaires.at(i)->sizeY;
			utilitaire = this->utilitaires.at(i);
			this->tmpPosUtilitaire = i + 1;
		}
	}
	if (this->tmpPosUtilitaire == utilitaires.size()) this->tmpPosUtilitaire = 0;
	return utilitaire;
}


void Placement::Place_batiment(Batiment * batiment, int posX, int posY)
{
	for (int i = 0; i <batiment->sizeX; i++)
	{
		for (int j = 0; j < batiment->sizeY; j++)
		{
			if (map->tabCell[posX + i][posY + j] == -1 && batiment->plan[i][j] != -1) {
				map->tabCell[posX + i][posY + j] = batiment->plan[i][j];
			}
		}
	}
}

void Placement::placeUtilitairesSurContour(int posFirstX, int posFirstY,int distanceMax) {
	//on place sur (i,j) avec j fixe
	int j = posFirstY - distanceMax;
	//Pour Y gauche bas en haut
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, false, distanceMax);
	//Pour X haut gauche à droite
	j = posFirstX + distanceMax;
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, true, distanceMax);
	// Pour Y droite haut en bas
	j = posFirstY + distanceMax;
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, true, distanceMax);
	//Pour X haut gauche à droite
	j = posFirstX - distanceMax;
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, false, distanceMax);
}

void Placement::placeUtilitaire(int posFirstX, int posFirstY,int j, bool isPlusFirst, int distMax){
	if (isPlusFirst) {
		for (int i = posFirstX + distMax; i >= posFirstX - distMax; i--)
		{

			if (i > 0 && j > 0) {
				bool cond = false;
				for (int k = this->tmpPosUtilitaire; k < utilitaires.size(); k++) {
					Batiment *utiliy = this->utilitaires.at(k);
					if (isOkForPlacement(utiliy, i, j)) {
						Place_batiment(utiliy, i, j);
						OutFile << utiliy->returnIdOrder() << " " << i << " " << j << endl;
						k = utilitaires.size();
						this->tmpPosUtilitaire = k + 1;
						nbBatimentPose++;
					}
				}
			}
		}
	}
	else {
		for (int i = posFirstX - distMax; i <= posFirstX + distMax; i++)
		{
			//on place sur (i,j) avec j fixe
			if (i > 0 && j > 0) {
				bool cond = false;
				for (int k = this->tmpPosUtilitaire; k < utilitaires.size(); k++) {
					Batiment *utiliy = this->utilitaires.at(k);
					if (isOkForPlacement(utiliy, i, j)) {
						Place_batiment(utiliy, i, j);
						OutFile << utiliy->returnIdOrder() << " " << i << " " << j << endl;
						k = utilitaires.size();
						nbBatimentPose++;
						this->tmpPosUtilitaire = k + 1;
					}
				}
			}
		}
	}
}

vector<Batiment*> Placement::placerBatiment()
{
	int posFirstX = (0);
	int posFirstY = (0);
	int distanceMax = this->map->distMax;
	Batiment* utilitaire = this->getMinPerimetre();
	Batiment* residence = this->getMaxCapacite();
	//Avec la ligne suivante, on place l'utilitaire de plus petit périmetre au milieu
	OutFile << utilitaire->returnIdOrder() << " " << posFirstX << " " << posFirstY << endl;
	Place_batiment(utilitaire, posFirstX, posFirstY);
	nbBatimentPose++;
	bool condition = true;
	for (int x = posFirstX - (distanceMax); x < posFirstX + (distanceMax); x++) {
		for (int y = posFirstY - (distanceMax); y < posFirstY + (distanceMax); y++) {
			if (isOkForPlacement(residence, x, y)) {
				Place_batiment(residence, x, y);
				OutFile << residence->returnIdOrder() << " " << x << " " << y << endl;
				residence = this->getMaxCapacite();
				nbBatimentPose++;
			}
		}
	}
	int cpt = 0;
	int dmaxCondition = sqrt(2) * (this->map->sizeX*this->map->sizeY);
	while (distanceMax <= dmaxCondition)
	{
		//comment je devrais mettre les residences et ce qui reste des utilitaires ==>
		//normalement je devrais mettre les batiments de autour de cette utility de maniere à ne pas dépasser le rayon D
		//puis faire l'itération 
		//on retourne le map actuelle
		if (distanceMax == 1) {
			if (cpt == 0) distanceMax *= 2;
		}
		else distanceMax *= 1.5;
		cpt++;
		placeUtilitairesSurContour(posFirstX, posFirstY, distanceMax);

		distanceMax *= 1.5;
		for (int x = posFirstX - (distanceMax); x <= posFirstX + (distanceMax); x++) {
			if (x < 0) x = 0;
			for (int y = posFirstY - (distanceMax); y <= posFirstY + (distanceMax); y++) {
				if (y < 0) y = 0;
				if (isOkForPlacement(residence, x, y)) {
					Place_batiment(residence, x, y);
					OutFile << residence->returnIdOrder() << " " << x << " " << y << endl;
					residence = this->getMaxCapacite();
					nbBatimentPose++;
				}
			}
		}
		cout << distanceMax << endl;
	}


	//Tout en haut du fichier tu changes le test.out avec le nom de la map .out
	//Puis juste en dessous de cette ligne, tu changes le test.out en le nomdelamap.out
	ifstream fichier("test.out");
	//et ici tu changes en nom de la mapV2.out !
	ofstream flux("realTest.out");

	string ligne;
	flux << nbBatimentPose << endl;
	while (getline(fichier, ligne)) // On le lis ligne par ligne
	{
		if (flux) // Si le lieu de destination existe ( j'entend par la le dossier )
		{
			flux << ligne << endl; // On ecrit dans le fichier de destination
		}                          // Et au passage on le créer si il n'existe pas
		else
		{
			cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
		}
	}
	return vector<Batiment*>();
}

bool Placement::isOkForPlacement(Batiment * batiment, int posX, int posY)
{
	if (posX + batiment->sizeX > map->sizeX || posY + batiment->sizeY > map->sizeY) return false;

	if (posX < 0 || posY < 0) return false;

	for (int i = 0; i < batiment->sizeX; i++)
	{
		for (int j = 0; j < batiment->sizeY; j++)
		{
			// != -1 ==> occupée ==>  à vérifier 
			if (map->tabCell[posX + i][posY + j] != -1  && batiment->plan[i][j] != -1)
			{
				return false;
			}
			
		}
	}
	return true;
}
*/

#include "Placement.h"
#include "Batiment.h"
#include <iostream>
#include <string>
#include <vector>
#include "Map.h"
#include <fstream>

ofstream OutFile("f_different_footprints.out");
int nbBatimentPose = 0;

Placement::Placement(Map *map, int nbResidence, int nbDivision)
{
	this->map = map;
	this->tmpPosUtilitaire = 0;
	this->tmpPosResidence = 0;
	this->nbDivision = nbDivision;
	for (int i = 0; i < nbResidence; i++) {
		this->residences.push_back(map->listeBatiments.at(i));
	}
	for (int i = nbResidence; i < map->listeBatiments.size(); i++) {
		this->utilitaires.push_back(map->listeBatiments.at(i));
	}
}

// Ajouter retourner une liste si on veut tester plusieurs points de dpart
Batiment * Placement::getMaxCapacite()
{
	int maxCapacite = 0;
	Batiment *residence = nullptr;
	for (int i = this->tmpPosResidence; i < this->residences.size(); i++) {
		if (this->residences.at(i) != nullptr) {
			if (maxCapacite < this->residences.at(i)->capacity) {
				maxCapacite = this->residences.at(i)->capacity;
				residence = this->residences.at(i);
				this->tmpPosResidence = i + 1;
				//this->residences.at(i) = nullptr;
			}
		}
	}
	if (this->tmpPosResidence == residences.size()) this->tmpPosResidence = 0;
	return residence;
}


Batiment* Placement::getMinPerimetre()
{

	int minPerimetre = 999999;
	Batiment *utilitaire = nullptr;
	cout << endl;
	for (int i = this->tmpPosUtilitaire; i < utilitaires.size(); i++) {

		if (minPerimetre >(this->utilitaires.at(i)->sizeX*this->utilitaires.at(i)->sizeY))
		{
			minPerimetre = this->utilitaires.at(i)->sizeX*this->utilitaires.at(i)->sizeY;
			utilitaire = this->utilitaires.at(i);
			this->tmpPosUtilitaire = i + 1;
		}
	}
	if (this->tmpPosUtilitaire == utilitaires.size()) this->tmpPosUtilitaire = 0;
	return utilitaire;
}


void Placement::Place_batiment(Batiment * batiment, int posX, int posY, const int nbDivision, int sizeMap)
{
	bool debug = false;
	for (int i = 0; i < batiment->sizeX; i++)
	{
		for (int j = 0; j < batiment->sizeY; j++)
		{
			if (map->tabCell[posX + i][posY + j] == -1 && batiment->plan[i][j] != -1) {
				map->tabCell[posX + i][posY + j] = batiment->plan[i][j];
				switch (nbDivision)
				{
				case 4:
					if (isOkForPlacement(batiment, posX + i + ((sizeMap / 2) - 1), posY + j)) {
						map->tabCell[posX + i + ((sizeMap / 2) - 1)][posY + j] = batiment->plan[i][j];
					}
					if (isOkForPlacement(batiment, posX + i, posY + j + ((sizeMap / 2) - 1))) {
						map->tabCell[posX + i][posY + j + ((sizeMap / 2) - 1)] = batiment->plan[i][j];
					}
					if (isOkForPlacement(batiment, posX + i + ((sizeMap / 2) - 1), posY + j + ((sizeMap / 2) - 1))) {
						map->tabCell[posX + i + ((sizeMap / 2) - 1)][posY + j + ((sizeMap / 2) - 2)] = batiment->plan[i][j];
					}
					break;
				case 16:
					break;
				case 32:
					break;
				default:
					break;
				}
			}
		}
	}
}

void Placement::placeUtilitairesSurContour(int posFirstX, int posFirstY, int distanceMax) {
	//on place sur (i,j) avec j fixe
	int j = posFirstY - distanceMax;
	//Pour Y gauche bas en haut
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, false, distanceMax);
	//Pour X haut gauche  droite
	j = posFirstX + distanceMax;
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, true, distanceMax);
	// Pour Y droite haut en bas
	j = posFirstY + distanceMax;
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, true, distanceMax);
	//Pour X haut gauche  droite
	j = posFirstX - distanceMax;
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, false, distanceMax);
}

void Placement::placeUtilitaire(int posFirstX, int posFirstY, int j, bool isPlusFirst, int distMax) {
	if (isPlusFirst) {
		for (int i = posFirstX + distMax; i >= posFirstX - distMax; i--)
		{

			if (i > 0 && j > 0) {
				bool cond = false;
				for (int k = this->tmpPosUtilitaire; k < utilitaires.size(); k++) {
					Batiment *utiliy = this->utilitaires.at(k);
					if (isOkForPlacement(utiliy, i, j)) {
						Place_batiment(utiliy, i, j,this->nbDivision,this->map->sizeX);
						OutFile << utiliy->returnIdOrder() << " " << i << " " << j << endl;
						k = utilitaires.size();
						this->tmpPosUtilitaire = k + 1;
						nbBatimentPose+=4;
					}
				}
			}
		}
	}
	else {
		for (int i = posFirstX - distMax; i <= posFirstX + distMax; i++)
		{
			//on place sur (i,j) avec j fixe
			if (i > 0 && j > 0) {
				bool cond = false;
				for (int k = this->tmpPosUtilitaire; k < utilitaires.size(); k++) {
					Batiment *utiliy = this->utilitaires.at(k);
					if (isOkForPlacement(utiliy, i, j)) {
						Place_batiment(utiliy, i, j, this->nbDivision, this->map->sizeX);
						OutFile << utiliy->returnIdOrder() << " " << i << " " << j << endl;
						k = utilitaires.size();
						nbBatimentPose+=4;
						this->tmpPosUtilitaire = k + 1;
					}
				}
			}
		}
	}
}

vector<Batiment*> Placement::placerBatiment()
{
	int dmaxCondition = sqrt(2) * ((this->map->sizeX/(this->nbDivision/2))*(this->map->sizeY/(this->nbDivision /2)));
	int sizeXSubMap = this->map->sizeX / this->nbDivision;
	int sizeYSubMap = this->map->sizeY / this->nbDivision;
	int posFirstX = (0);
	int posFirstY = (0);
	int distanceMax = this->map->distMax;
	
	Batiment* utilitaire = this->getMinPerimetre();
	Batiment* residence = this->getMaxCapacite();
	OutFile << utilitaire->returnIdOrder() << " " << posFirstX << " " << posFirstY << endl;
	Place_batiment(utilitaire, posFirstX, posFirstY, this->nbDivision, this->map->sizeX);
	nbBatimentPose+=4;
	bool condition = true;
	//on essaye de recupérer la  derniere position x, là où on s'est arreté
	int dernierxrempli = 0;
	//on essaye de recupérer la  derniere position x, là où on s'est arreté
	int dernieryrempli = 0;
	for (int x = posFirstX - (distanceMax); x < posFirstX + (distanceMax); x++) {
		for (int y = posFirstY - (distanceMax); y < posFirstY + (distanceMax); y++) {
			if (isOkForPlacement(residence, x, y)) {
				Place_batiment(residence, x, y, this->nbDivision, this->map->sizeX);
				dernierxrempli = x + residence->sizeX - 1;
				dernieryrempli = y + residence->sizeY - 1;
				//cout << "dernier  x rempli " << dernierxrempli << endl;
				//cout << "dernier  y rempli " << dernieryrempli << endl;
				OutFile << residence->returnIdOrder() << " " << x << " " << y << endl;
				residence = this->getMaxCapacite();
				nbBatimentPose+=4;
			}
		}
	}
	int cpt = 0;
	while (distanceMax <= dmaxCondition)
	{

		if (distanceMax == 1) {
			if (cpt == 0) distanceMax *= 2;
		}
		else distanceMax *= 1.5;
		cpt++;
		placeUtilitairesSurContour(posFirstX, posFirstY, distanceMax);

		distanceMax *= 1.5;
		cout << distanceMax << " " << dmaxCondition << endl;
		// on fait une copie de dernierxrempli et de dernieryrempli parce que on va les utiliser pour définir  les bornes des boucles for et on va les modifier à l'interieur de la boucle
		int borneX = dernierxrempli;
		int borneY = dernieryrempli;
		for (int x = borneX; x <= posFirstX + (distanceMax); x++) {
			if (x < 0) x = 0;
			for (int y = 0; y <= borneY; y++) {
				if (y < 0) y = 0;
				if (isOkForPlacement(residence, x, y)) {
					Place_batiment(residence, x, y, this->nbDivision, this->map->sizeX);
					OutFile << residence->returnIdOrder() << " " << x << " " << y << endl;
					residence = this->getMaxCapacite();
					nbBatimentPose+=4;
				}
			}
		}
		for (int x = 0; x <= posFirstX + (distanceMax); x++) {
			if (x < 0) x = 0;
			for (int y = borneY; y <= posFirstY + (distanceMax); y++) {
				if (y < 0) y = 0;
				if (isOkForPlacement(residence, x, y)) {
					//cout << x << " " << y << endl;
					Place_batiment(residence, x, y, this->nbDivision, this->map->sizeX);
					dernierxrempli = x + residence->sizeX - 1;
					dernieryrempli = y + residence->sizeY - 1;
					//cout << "dernier  x rempli " << dernierxrempli << endl;
					//cout << "dernier  y rempli " << dernieryrempli << endl;
					OutFile << residence->returnIdOrder() << " " << x << " " << y << endl;
					residence = this->getMaxCapacite();
					nbBatimentPose+=4;
				}
			}
			//on sortie le dernierxrempli et le dernieryrempli seront la derniere cellule de derniere résidence rempli, que je le récupere de la deuxieme boucle, parce que l'espace à remplir par la deuxieme boucle plus grande que celui de la premiere  
			
		}
		cout << distanceMax << endl;
	}


		//Tout en haut du fichier tu changes le test.out avec le nom de la map .out
		//Puis juste en dessous de cette ligne, tu changes le test.out en le nomdelamap.out
		ifstream fichier("f_different_footprints.out");
		//et ici tu changes en nom de la mapV2.out !
		ofstream flux("f_different_footprintsV2.out");

		string ligne;
		flux << nbBatimentPose << endl;
		while (getline(fichier, ligne)) // On le lis ligne par ligne
		{
			if (flux) // Si le lieu de destination existe ( j'entend par la le dossier )
			{
				flux << ligne << endl; // On ecrit dans le fichier de destination
			}                          // Et au passage on le crer si il n'existe pas
			else
			{
				cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
			}
		}
		return vector<Batiment*>();
	}
	

bool Placement::isOkForPlacement(Batiment * batiment, int posX, int posY)
{
	if (posX + batiment->sizeX > map->sizeX || posY + batiment->sizeY > map->sizeY) return false;

	if (posX < 0 || posY < 0) return false;

	for (int i = 0; i < batiment->sizeX; i++)
	{
		for (int j = 0; j < batiment->sizeY; j++)
		{
			// != -1 ==> occupe ==>   vrifier 
			if (map->tabCell[posX + i][posY + j] != -1 && batiment->plan[i][j] != -1)
			{
				return false;
			}

		}
	}
	return true;
}
