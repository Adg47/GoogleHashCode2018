#include "Map.h"
#include "ParserOut.h"
#include "Residence.h"
#include "Utility.h"
#include "Parser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <map>
#include <cmath>
#include <time.h>
#include <cmath>
#include <cstring>
#include "Placement.h"
#include <cstdio>


// POUR WINDOWS
#include <windows.h>
#include <filesystem>

using namespace std;
namespace fs = std:: experimental::filesystem;


// La fonction de validation marche ! La fonction pour calculer le temps d'éxécution
// des executables est ok pour windows seulement pour le moment.
int main() {

	//Ici tu change le nom de la map contenu dans le "Fichier de Ressources"
	// ensuite tu vas dans Placement.cpp à la fonction placerBatiment
   Parser *p=new Parser("a_example.in");

   //ParserOut *po = new ParserOut("PolyPlayer_a_example.txt",p->map);
 //  cout << "test" <<endl;
   Placement *pl = new Placement(p->map, p->map->nbResidence);
   cout << pl->getMaxCapacite()->capacity << endl;
   int i = 1.5;
   cout << i;
   //vector<Batiment*> res = pl->getMinPerimetre();
   pl->placerBatiment();

   for (int i = 0; i<pl->map->sizeX; i++)
   {
	   for (int j = 0; j<pl->map->sizeY; j++)
	   {
		   if (pl->map->tabCell[i][j] == -1) {
			   cout << ".";
		   }
		   else {
			   cout << "#";
		   }
		   //cout << pl->map->tabCell[i][j];
	   }
	   cout << endl;
   }
   system("PAUSE");
   //D:/visualc++/Executables
   //string nomdedossier;
   //cout << "taper le chemin des exécutables" << endl;
   //cin >> nomdedossier;
   //TempsdeExecution(nomdedossier);

}