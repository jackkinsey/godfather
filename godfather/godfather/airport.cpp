/*
 * airport.cpp
 * Implements behavior of the airport.
 */

#include <stdlib.h> //For malloc, etc.
#include <string.h> //For memcpy.
#include <iostream>
#include "airport.h"

struct Plane {
	int numCargo;
	int numPeople;
	int fuel;
	bool grandchildren;
};

int Airport::getValue(Plane plane) {
	int Value;
	int weightPeople = 10;
	int weightCargo = 5;
	double multiplierGrandchildren = 0.25;

	if (plane.grandchildren) {Value = multiplierGrandchildren*weightPeople*plane.numPeople + weightCargo*plane.numCargo;}
	else {Value = weightPeople*plane.numPeople + weightCargo*plane.numCargo;}  

	return Value;

}

bool Airport::refuel(Plane plane) {
	if (plane.fuel < 20) {return true;} else { return false; }
}

bool Airport::depart(Plane plane) {
	return true;
}

bool Airport::land(Plane plane) {
	return true;
}

bool Airport::crash(Plane plane) {
	return true;
}


void Airport::process() {

}