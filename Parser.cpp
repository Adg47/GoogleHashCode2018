#include "Map.h"
#include "Parser.h"
#include "Residence.h"
#include "Utility.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
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

Parser::Parser(string namefile)
{

    this->namefile=namefile;
    string line;
    ifstream myfile(namefile);
    std::string::size_type sz;
    if (myfile.is_open())
    {
        getline(myfile,line);
        vector<string> sep = split(line, ' ');
        Map *map = new Map(std::stoi (sep[0],&sz),std::stoi (sep[1],&sz),std::stoi (sep[2],&sz),std::stoi (sep[3],&sz));
        for(int i = 0; i < sep.size(); ++i)

            while ( getline (myfile,line) )
            {
                vector<string> sep = split(line, ' ');
                if(sep[0] == "R"){
                    Residence *res = new Residence(std::stoi (sep[3],&sz),std::stoi (sep[1],&sz),std::stoi (sep[2],&sz));
                    int **tab;
                    tab = new int*[std::stoi (sep[1],&sz)];
                    for(int i = 0; i < std::stoi (sep[1],&sz); i++){
                        getline (myfile,line);
                        tab[i] = new int(std::stoi (sep[2],&sz));
                        int cpt = 0;
                        for(char& c : line) {
                            if(c == '#'){
                                tab[i][cpt] = 1;
                            } else {
                                tab[i][cpt] = 0;
                            }
                            cpt++;
                        }
                    }
                    res->plan = tab;
                } else {
                    Utility *uti = new Utility(std::stoi (sep[3],&sz),std::stoi (sep[1],&sz),std::stoi (sep[2],&sz));
                    int **tab;
                    tab = new int*[std::stoi (sep[1],&sz)];
                    for(int i = 0; i < std::stoi (sep[1],&sz); i++){
                        getline (myfile,line);
                        tab[i] = new int(std::stoi (sep[2],&sz));
                        int cpt = 0;
                        for(char& c : line) {
                            if(c == '#'){
                                tab[i][cpt] = 1;
                            } else {
                                tab[i][cpt] = 0;
                            }
                            cpt++;
                        }
                    }
                    uti->plan = tab;

                }
            }
        myfile.close();
    }
    else cout << "Unable to open file";

}