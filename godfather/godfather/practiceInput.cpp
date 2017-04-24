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
//#include "structure.h"

using namespace std;


struct Plane {
	char dataType;
	int time;
	char action;
	int fuel;
	int numPeople;
	int numCargo;
	bool grandchildren;
	double value;

	Plane *next;
	
};

class AirportInputProcessor {
    public:
    	Plane *plane;
        void readCSV();
        void init(char dataType, int time, char Acion, int fuel, int numPeople, int numCargo, bool grandchildren,  Plane *plane);
        void parseData(string CSV, Plane *plane);

};

void AirportInputProcessor::readCSV() {
	plane = new Plane; //Initialize first instance of the Plane structure
	Plane *constr = plane;		//Initialize a navigator to walk from struct to struct
	string line;				//this is the variable line that is obtained from each line of the CSV
    ifstream myfile ("AllTimeZero.csv");	//opens the "data.csv" file to be read
    if (myfile.is_open())			//if the file is successfully opened...
    {
        cout <<"File is Open"<<"\n";	//let me know that the file is opened
        while ( getline (myfile,line) )	//while we can get line from the file
        {
        	cout<<line<<"\n";
            parseData(line, constr);		//initialize the constructors properties with the elements of each line
            constr->next = new Plane;	//initialize a new instance of the plane
            constr = constr->next;		//the constr is now the new plane
        }
        constr = nullptr;				//once we cannot read the file anymore, the last constructor should be null
        myfile.close();					//close the file
    }
    
    else cout << "Unable to open file";	//the exception statement

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


	cout<<"DataType: "<<dataType<<" Time: "<<time<<" Action: "<<action<<" Fuel: "<<fuel<<"\n";

	plane->numCargo = numCargo;	//initialize the Plane struct's properties
	plane->numPeople = numPeople;
	plane->fuel = fuel;
	plane->grandchildren = grandchildren;
	plane->time = time;

	cout<<"Plane Time: "<<plane->time<<"\n";
	
}

int main() {

	AirportInputProcessor Input;
    Input.readCSV();
    cout<<Input.plane;
    return 0;
        }


	


