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
	double value;
	int time;
};

void Airport::getValue(Plane& plane) {
	int Value;
	int weightPeople = 10;
	int weightCargo = 5;
	int fuelFactor = 3;
	double multiplierGrandchildren = 0.25;

	if (plane.grandchildren) {Value = multiplierGrandchildren*weightPeople*plane.numPeople + weightCargo*plane.numCargo - (1-multiplierGrandchildren)*fuelFactor*plane.fuel;}
	else {Value = weightPeople*plane.numPeople + weightCargo*plane.numCargo - fuelFactor*plane.fuel;}

	plane.value = Value;

}

bool Airport::refuel(Plane& plane) {
    if(plane.fuel < 20) {
        return true;
    } else {
        return false;
    }
}

bool Airport::depart(Plane& plane) {
    return true;
}

bool Airport::land(Plane& plane) {
    //if(plane == maxPlaneToLand1 || plane == maxPlaneToLand2) { return true; } else { return false; }
    return true;
}

bool Airport::crash(Plane& plane) {
	if (!land(plane) && plane.time == 1) {return true;} else {return false;}
}

void Airport::process() {

}
