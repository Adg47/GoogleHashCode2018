#include "Placement.h"
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

// Ajouter retourner une liste si on veut tester plusieurs points de d�part
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
	//Pour X haut gauche � droite
	j = posFirstX + distanceMax;
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, true, distanceMax);
	// Pour Y droite haut en bas
	j = posFirstY + distanceMax;
	if (j >= 0) placeUtilitaire(posFirstX, posFirstY, j, true, distanceMax);
	//Pour X haut gauche � droite
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
	//Avec la ligne suivante, on place l'utilitaire de plus petit p�rimetre au milieu
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
		//normalement je devrais mettre les batiments de autour de cette utility de maniere � ne pas d�passer le rayon D
		//puis faire l'it�ration 
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
		}                          // Et au passage on le cr�er si il n'existe pas
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
			// != -1 ==> occup�e ==>  � v�rifier 
			if (map->tabCell[posX + i][posY + j] != -1  && batiment->plan[i][j] != -1)
			{
				return false;
			}
			
		}
	}
	return true;
}
