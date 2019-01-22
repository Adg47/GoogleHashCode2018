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




// La fonction de validation marchent ! La fonction pour calculer le temps d'éxécution
// des executables est ok pour windows seulement pour le moment.
int main(int argc, char *argv[]){


	if (argc < 3)
	{
		cout << "Pas assez de paramètres - utilisez de la façon suivante : nomProg mapEntree mapSortie" << endl;
		system("PAUSE");
		return 0;
	}

	string in;
	string out;
	in = argv[1];
	out = argv[2];

	cout << in << endl;
	cout << out << endl;

   Parser *p=new Parser(in);

   ParserOut *po = new ParserOut(out,p->map);
   string nomdedossier;
   system("PAUSE");


}