/*
 * input.cpp
 * Processess CSV files into command structs.
 */

#include <stdlib.h> //For malloc, etc.
#include <string.h> //For memcpy.
#include <iostream>
#include <fstream>
#include <string>
#include "input.h"
using namespace std;

void AirportInputProcessor::readCSV() {

	string line;
    ifstream myfile ("data.csv");
    if (myfile.is_open())
    {
        cout <<"File is Open"<<"\n";
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    
    else cout << "Unable to open file";

}
