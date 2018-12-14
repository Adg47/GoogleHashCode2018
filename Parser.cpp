#include "Map.h"
#include "Parser.h"
#include "Residence.h"
#include "Utility.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <cmath>

using namespace std;


vector<string> Parser::split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str); // Turn the string into a stream.
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}

void duree(time_t _begin, time_t _end)
{
    double temp;
    double hours=0, min=0, sec=0;
    double dureeCalc = difftime(_end, _begin);
    temp = modf(dureeCalc/3600., &hours);
    temp = modf(temp*60., &min);
    temp = modf(temp*60., &sec);
    cout<<"Duree du calcul : "<<hours<<" h "<<min<<" min "<<sec<<" sec"<<endl;
}

Parser::Parser(string namefile)
{
    time_t deb =time(NULL);
    string line;
    ifstream myfile(namefile);
    string::size_type sz;
    vector<string> sep,sepTamp;

    //Si le fichier est ouvert
    if (myfile.is_open())
    {
        //On recupère la première ligne et on la traite
        getline(myfile,line);
        int  CPT = 0;
        bool isResidence = false;
        //On split les caractères avec comme delimiteur " "
        sep = split(line, ' ');
        this->map = new Map(stoi(sep[0],&sz),stoi(sep[1],&sz),stoi(sep[2],&sz),stoi(sep[3],&sz));
        while(getline(myfile,line)){
            sep = split(line, ' ');
            sepTamp = split(line,' ');
            int nbLine = stoi(sep[1]);
            vector <vector<int> > mymap(stoi(sep[1],&sz),vector<int>(stoi(sep[2],&sz),0));

            const char* charLine;
            for(int i =0; i < stoi(sep[1],&sz);i++){
                int cpt=0;
                getline(myfile,line);
                //charLine = line.c_str();
                for(char& c : line){
                    if (c == '#'){
                        mymap[i][cpt] = 1;
                    }
                    cpt++;
                }
            }

            switch(*sep[0].c_str()){
                case 'R':
                    Batiment *residence;
                    residence = new Residence(stoi(sep[3], &sz), stoi(sep[1], &sz), stoi(sep[2], &sz),mymap);
                    //map->listeResidences.push_back(*residence);
                    map->listeBatiments.push_back(residence);
                    break;
                case 'U':
                    Batiment *utility = new Utility(stoi(sep[3],&sz),stoi(sep[1],&sz),stoi(sep[2],&sz),mymap);
                    map->listeBatiments.push_back(utility);
                    //map->listeUtility.push_back(*utility);
                    break;
            }


            mymap.clear();
        }

        myfile.close();

        time_t end = time(NULL);
        duree(deb,end);
    }
    else cout << "Unable to open file";

}