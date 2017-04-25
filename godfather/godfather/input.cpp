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
#include "airport.h"

using namespace std;

AirportInputProcessor::AirportInputProcessor(char* input){
	Plane* plane = new Plane; //Initialize first instance of the Plane structure
	string line;				//this is the variable line that is obtained from each line of the CSV
        Timeline* timeline = new Timeline;
    ifstream myfile (input);	//opens the "data.csv" file to be read
    if (myfile.is_open())			//if the file is successfully opened...
    {
        cout <<"File is Open"<<"\n";	//let me know that the file is opened
        while ( getline (myfile,line) )	//while we can get line from the file
        {
        	cout<<line<<"\n";
            parseData(line, plane);		//initialize the constructors properties with the elements of each line
            timeline->push(plane->time, plane);
            plane = new Plane;	//initialize a new instance of the plane
        }
        myfile.close();					//close the file
        this->_airport = new Airport(timeline);
        this->_airport->process();
        this->_airport->print();
    }
    
    else cout << "Unable to open file";	//the exception statement

}

AirportInputProcessor::~AirportInputProcessor(){

}

void AirportInputProcessor::parseData(string CSV, Plane *plane) {		
	istringstream ss(CSV); 		//CSV is the comma seperateed line of the excel file
	string token;				//token is the mini parts of the CSV that we are trying to obtain

	string inputData[7];		//initialize InputData[7]

	plane = new Plane;	//the plane is initialized to a new instance of the Plane struct

	int i = 0;					//initialize a counter i
	while(std::getline(ss, token, ',')) {		//get the tokens of the CSV file
    	inputData[i] = token;					//the ith element of the inputData file is going to be this token
    	cout<<"TOKEN ["<<i<<"]: "<<token<<"\n";
    	i++;
	}

	char dataType = inputData[0][0];			//converting the dataType to a char
	int time = std::stoi(inputData[1]);				//convert to INT
	char action = inputData[2][0];				//convert to char
	int fuel = std::stoi(inputData[3]);				//convert to INT
	int numPeople = std::stoi(inputData[4]);			//convert to INT
	int numCargo = std::stoi(inputData[5]);			//convert to INT
	bool grandchildren;
	if (inputData[6][0] == 'Y') {
		grandchildren = true;
	} else { grandchildren = false;}

	plane->numCargo = numCargo;	//initialize the Plane struct's properties
	plane->numPeople = numPeople;
	plane->fuel = fuel;
	plane->grandchildren = grandchildren;
	plane->time = time;
	plane->dataType = dataType;
	plane->action = action;
}

