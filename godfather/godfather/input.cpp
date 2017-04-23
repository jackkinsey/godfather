/*
 * input.cpp
 * Processess CSV files into command structs.
 */

#include <stdlib.h> //For malloc, etc.
#include <string.h> //For memcpy.
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "input.h"
using namespace std;

<<<<<<< HEAD
=======
struct Plane {
	int numCargo;
	int numPeople;
	int fuel;
	bool grandchildren;
	double value;
	int time;
};

>>>>>>> 13e062da3a50d55d3b7996bdf7d3badd0a3132c4
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

void AirportInputProcessor::init(int numCargo, int numPeople, int fuel, bool grandchildren, int time, Plane plane) {
	plane.numCargo = numCargo;
	plane.numPeople = numPeople;
	plane.fuel = fuel;
	plane.grandchildren = grandchildren;
	plane.time = time;
}

void AirportInputProcessor::parseData(string CSV) {
	string input = CSV;
	istringstream ss(input);
	string token;

	i = 0;
	while(std::getline(ss, token, ',')) {
    	inputData[i] = token;
    	i++;
	}
	
}
