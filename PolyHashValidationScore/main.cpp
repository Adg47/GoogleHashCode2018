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

// POUR WINDOWS
#include <windows.h>
#include <filesystem>

using namespace std;
namespace fs = std:: experimental::filesystem;


/*
void TempsdeExecution(string path)
{
    vector<float> g1;
    try {
        for (auto & p : fs::directory_iterator(path))
        {   string var_locale = p.path().string();
            char* c = new char[var_locale.length() + 1];
            strcpy(c, var_locale.c_str());
            int varlocale=0;
            for (int i = 0; i < 10; i++)
            {
                DWORD temps_debut = GetTickCount();
                system(c);
                DWORD temps_execution = GetTickCount() - temps_debut;
                varlocale += temps_execution;
                //cout << temps_execution << endl;
            }
            //le temps est calculé en millisecondes
            g1.push_back((float)varlocale/10);
        }
    }
    catch (...)
    {
        throw;
    }
    for (auto it = g1.begin(); it != g1.end(); it++)
        cout << *it << " ";
}

*/

int ScorePoint(Batiment *r, Batiment *u, int rx, int ry, int ux, int uy,Map *m) {

	//Fonction à revoir
    int distanceru = 1000000;// c'est la distance minimale
							 /*

    for (int i = rx; i < rx + r->sizeX; i++) {
        for (int j = ry; j < ry + r->sizeY; j++) {
			//si la cellule est occupée dans le plan de la résidence r
            if (r->plan[rx+i][ry+j] == 1) {
				//cellules de l'utilitaire
                for (int z = ux; z < ux + u->sizeX; z++) {
                    for (int e = uy; e < uy + u->sizeY; e++) {

						cout << "z vaut " << z << " e vaut " << e << " ux et uy : " <<  ux << " " << uy << endl;
						cout << "la taille de la map est Y = " << m->sizeY << " et X = " << m->sizeX << endl;
						cout << " le plan a pour dimension Y = " << u->sizeY << " et X = " << u->sizeX << endl;
						cout << " z vaut = " << z << " et e vaut = " << e << endl;

						if (uy + z < m->sizeY && ux + e << m->sizeX && uy+z<u->sizeY && ux+e<<u->sizeX)
						{		
							if (u->plan[ux + z][uy + e] == 1)
							{
								if (abs(z - i) + abs(e - j)<distanceru)
								{
									distanceru = ((abs(z - i) + abs(e - j)));

								}
							}
						}
						
                    }
                }
            }
        }
    }
	*/
    return distanceru;
}

int ScoreFinal(Batiment **r, Batiment **u, map<int, int >rm, map<int, int>um, int disMax,Map *m) {
    int myscore = 0;// calcule le final score
    map<int, int>::iterator iter;
    map<int, int>::iterator it;
    int e = 0;
    for (iter = rm.begin(); iter != rm.end(); iter++) {// faire l'itération sur les residences
        int k = 0;
        for (it = um.begin(); it != um.end(); it++) {// faire l'iteration sur  utilitaires

			cout << "on envoi la residence " << e << " avec l'utilitaire " << k<< " rx vaut "<< iter->first << "ry vaut " <<iter->second <<" ux vaut " << it->first<< "uy vaut " <<it->second << endl;
			myscore = (ScorePoint(r[e], u[k], iter->first, iter->second, it->first, it->second,m) <= disMax) ? myscore + 1 : myscore;
			k++;
            myscore += r[e]->capacity;        
		}
        e++;
    }
    return myscore;

}
int ParserOut::Score(Map *m) {
    map<int, int> m1;
    map<int, int> m2;
    Batiment **u = new Batiment *[m->nbrBuild];
    int j = 0;
    int k = 0;
    Batiment **r = new Batiment *[m->nbrBuild];

	//on itère sur tous les batiments
    for (int i = 0; i < m->listeBatiments.size(); i++) {
		//si ce batiment est une résidence
        if (m->listeBatiments[i]->returnType() == -4) {
			//pour chaque batiment de ce type
            for (int a = 0; a < m->listeBatiments[i]->posX.size(); a++) {
				//on insère les résidences dans un tableau de résidences
                m1.insert(pair<int, int>(m->listeBatiments[i]->posX[a], m->listeBatiments[i]->posY[a]));
                r[k] = m->listeBatiments[i];
                k++;
            }
        }
		else 
		{
			//pour chaque batiment non résidence, on itère sur ce type
            for (int b = 0; b < m->listeBatiments[i]->posX.size(); b++) {
                m2.insert(pair<int, int>(m->listeBatiments[i]->posX[b], m->listeBatiments[i]->posY[b]));
                u[j] = m->listeBatiments[i];
                j++;
            }
        }
    }
	cout << "ola" << endl;
    return ScoreFinal(r, u, m1, m2, m->distMax,m);
}





// La fonction de validation marche ! La fonction pour calculer le temps d'éxécution
// des executables est ok pour windows seulement pour le moment.
int main() {

   Parser *p=new Parser("a_example.in");

   ParserOut *po = new ParserOut("PolyPlayer_a_example.txt",p->map);



   cout << p->map->tabCell[0][1]<<endl;
 //  cout << "test" <<endl;
   system("PAUSE");
   //D:/visualc++/Executables
   string nomdedossier;
   //cout << "taper le chemin des exécutables" << endl;
   //cin >> nomdedossier;
   //TempsdeExecution(nomdedossier);

}