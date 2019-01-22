//
// Created by anonymous on 13/12/18.
//


#include "Map.h"
#include "ParserOut.h"
#include "Residence.h"
#include "Utility.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <cmath>
#include <map>
using namespace std;

vector<string> ParserOut::split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

bool ParserOut::Validation(Map *map) {
    for (int i = 0; i < map->listeBatiments.size(); i++) {
      //  cout << "Batiment n~ " << i <<endl;
        for (int j = 0; j < map->listeBatiments[i]->sizeX; j++) {
            for (int k = 0; k < map->listeBatiments[i]->sizeY; k++) {

                if (map->listeBatiments[i]->plan[j][k] == 1) {
                    for(int l=0;l<map->listeBatiments[i]->posX.size();l++)
                    {
                      //  cout << j << " ; " << k << " du batiment n " << i << " sous element : " << l << endl;

                        if(map->tabCell[map->listeBatiments[i]->posX[l] + j][map->listeBatiments[i]->posY[l] + k]==-1){
                            map->tabCell[map->listeBatiments[i]->posX[l] + j][map->listeBatiments[i]->posY[l] + k] =i;

                        }
                        else{
                            cout << "INVALID OUTPUT FILE" <<endl;
                            return false;
                        }
                    }
                }

            }
        }

    }

    return true;
}



void ParserOut::Print(Map *map)
{

    for(int i=0;i<map->sizeX;i++)
    {
        for(int j=0;j<map->sizeY;j++)
        {
            cout << map->tabCell[i][j]<<"-";
        }
        cout<<endl;
    }
}

int Distance(int rx, int ry,int ux,int uy) {
	
	
	return abs(ux-rx)+abs(uy-ry);

}
int ParserOut::ScorePoint(Batiment* r, Batiment* u, Map *m)
{
	//initialisation du score
	int score = 0;
	//distMin initialisation
	int distMin = 1000000000;

	//on parcours toutes les instances de ce type de résidence
	for (int i = 0; i < r->posX.size();i++)
	{
		//on parcours tous les batiments de ce type
		for (int j = 0; j < u->posX.size(); j++)
		{
			//la dist min doit être réinitialisée à chaque changement de couple UTLITAIRE  - RESIDENCE
			distMin = 1000000000;
			//on itère sur le plan de la résidence
			//pour chaque ligne du plan
			for (int q = 0; q < r->sizeX; q++)
			{
				//pour chaque colonne du plan
				for (int s = 0; s < r->sizeY; s++)
				{
					if (r->plan[q][s] == 1)
					{
						int rx = r->posX[i];
						int ry = r->posY[i];
						rx = rx + q;
						ry = ry + s;
						//on itère sur le plan de l'utilitaire et on cherche la distance la plus proche entre chaque cellule des 2 batiments
						for (int l = 0; l < u->sizeX; l++)
						{	
							for (int m = 0; m < u->sizeY; m++)
							{
								int ux = u->posX[j];
								int uy = u->posY[j];
								if (u->plan[l][m] == 1)
								{
									ux = ux + l;
									uy = uy + m;

									int dist = Distance(rx, ry, ux, uy);
									//cout << dist << endl;
									if (dist < distMin)
									{
										distMin = dist;

									}
								}
							}

						}
					}
				}
			}
			//cout << "La distance minimale entre la res"<< r->posX[i]<<r->posY[i]<<  "et lut  "<<u->posX[j]<<u->posY[j]<<" vaut" << distMin << " et la dist max est " << m->distMax << endl;
			if (m->distMax >= distMin)
			{
				score += r->capacity;
			}
		}
	}
	return score;
}

int ParserOut::Score(Map *m) {

	std::vector<Batiment*> listeUtility;
	std::vector<Batiment*> listeResidence;
	int interm = 0;
	int j = 0;
	int k = 0;
	int score = 0;
	//on itère sur tous les batiments
	for (int i = 0; i < m->listeBatiments.size(); i++) {
		//si ce batiment est une résidence
		if (m->listeBatiments[i]->returnType() == -4) {
			//pour chaque batiment de ce type
				//on insère les résidences dans un tableau de résidences
				listeResidence.push_back(m->listeBatiments[i]);
				k++;
			
		}
		else
		{
				listeUtility.push_back(m->listeBatiments[i]);
				j++;
			
		}
	}
	//pour chaque résidence
	for (int s = 0; s < k; s++)
	{
		//pour chaque utilitaire
		for (int t = 0; t < j; t++)
		{
			//cout << "Résidence n et Utility n " << s << " : " << t << endl;
			score+=this->ScorePoint(listeResidence[s], listeUtility[t], m);
			//cout << " Score final" << score << endl;
		}
	}
	return score;
}


ParserOut::ParserOut(string name,Map *map) {
    time_t deb =time(NULL);
    string line;
    ifstream myfile(name);
    string::size_type sz;
    vector<string> sep;

    //Si le fichier est ouvert
    if (myfile.is_open())
    {
        getline(myfile,line);
        this->nbBatiment = stoi(line,&sz);

        while(getline(myfile,line)){
            sep = split(line,' ');
            map->listeBatiments.at(stoi(sep[0],&sz))->posX.push_back(stoi(sep[1],&sz));
            map->listeBatiments.at(stoi(sep[0],&sz))->posY.push_back(stoi(sep[2],&sz));
        }
    }
	//validation , calcul et affichage du score
	if (this->Validation(map))
	{
		int s = this->Score(map);
		cout <<" Score de : "<< s << endl;

	}
	//affiche map
	//this->Print(map);

}