//
// Created by anonymous on 13/12/18.
//

// Premier = nb batiment placé
// c1 = id batiment c2 =ligne c3 = colonne

// si c1 = 0 alors résidence sinon utility

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

/*int ParserOut::Score(Map *map){

    int score=0;
    for(int i=0;i<map->listeBatiments.size();i++)
    {
        for(int j=0;j<map->listeBatiments[i]->posX[j];j++)
        {
            for(int k=0;k<map->listeBatiments[i]->posY[k];k++)
            {
                cout << " le type du batiment  "<< i <<" est : "<< map->listeBatiments[i]->returnType() <<endl;
				//map->listeBatiments[i]->plan;;
                //récupérer le nombre de batiments qu'il existe avec le plan du batiment à l'indice [i]
                //map->listeBatiments[i]->posX.size();
                //récupérer les coordonnées du premier batiment construit avec le plan du batiment[i]               map->listeBatiments[i]->posX[0]
				//map->listeBatiments[i]->posY[0];

            }
        }
    }
	return 0;
}*/

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
	cout << this->Validation(map) << endl;
    //this->Score(map);
}