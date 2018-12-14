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



int ScorePoint(Batiment *r, Batiment *u, int rx, int ry, int ux, int uy) {
    int distanceru = 1000000;// c'est la distance minimale
    for (int i = rx; i < rx + r->sizeX; i++) {
        for (int j = ry; j < ry + r->sizeY; j++) {
            if (r->plan[i - rx][j - ry] == 1) {
                for (int z = ux; i < ux + u->sizeX; z++) {
                    for (int e = uy; j < uy + u->sizeY; e++) {
                        distanceru = ((abs(z - i) + abs(e - j) < distanceru) && (u->plan[z - ux][e - uy] == 1)) ? abs(z - i) + abs(e - j) : distanceru;
                    }
                }
            }
        }
    }
    return distanceru;
}

int ScoreFinal(Batiment **r, Batiment **u, map<int, int >rm, map<int, int>um, int disMax) {
    int myscore = 0;// calcule le final score
    map<int, int>::iterator iter;
    map<int, int>::iterator it;
    int e = 0;
    for (iter = rm.begin(); iter != rm.end(); iter++) {// faire l'itération sur les residences
        int k = 0;
        for (it = um.begin(); it != um.end(); it++) {// faire l'iteration sur  utilitaires
            myscore = (ScorePoint(r[e], u[k], iter->first, iter->second, it->first, it->second) <= disMax) ? myscore + 1 : myscore; // si la distance est inférieur à la distance maximale, on le compte, s'ils ne sont pas inférieurs, on ne le compte pas
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

    for (int i = 0; i < m->listeBatiments.size(); i++) {
        if (m->listeBatiments[i]->returnType() == -4) {
            for (int a = 0; a < m->listeBatiments[i]->posX.size(); a++) {
                m1.insert(pair<int, int>(m->listeBatiments[i]->posX[a], m->listeBatiments[i]->posY[a]));
                r[k] = m->listeBatiments[i];
                k++;
            }
        } else {
            for (int b = 0; b < m->listeBatiments.size(); b++) {
                m1.insert(pair<int, int>(m->listeBatiments[i]->posX[b], m->listeBatiments[i]->posY[b]));
                u[j] = m->listeBatiments[i];
                j++;
            }
        }
    }
    return ScoreFinal(r, u, m1, m2, m->distMax);
}

    /* int score=0;
     for(int i=0;i<map->listeBatiments.size();i++)
     {
         for(int j=0;j<map->listeBatiments[i]->posX[j];j++)
         {
             for(int k=0<map->listeBatiments[i]->posY[k];k++)
             {
                 cout << " le type du batiment  "<< i <<" est : "<< map->listeBatiments[i]->returnType() <<endl;
                 map->listeBatiments[i]->plan
                 //récupérer le nombre de batiments qu'il existe avec le plan du batiment à l'indice [i]
                 map->listeBatiments[i]->posX.size();
                 //récupérer les coordonnées du premier batiment construit avec le plan du batiment[i]               map->listeBatiments[i]->posX[0]
                 map->listeBatiments[i]->posY[0]

             }
         }
     }


    return score;*/
}


// La fonction de validation marche ! La fonction pour calculer le temps d'éxécution
// des executables est ok pour windows seulement pour le moment.
int main() {

   Parser *p=new Parser("a_example.in");

   ParserOut *po = new ParserOut("PolyPlayer_a_example.txt",p->map);
   cout << p->map->tabCell[0][200]<<endl;
   cout << "test" <<endl;

   //D:/visualc++/Executables
   string nomdedossier;
   cout << "taper le chemin des exécutables" << endl;
   cin >> nomdedossier;
   TempsdeExecution(nomdedossier);

}