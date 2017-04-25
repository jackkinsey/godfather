/*
 * airport.cpp
 * Implements behavior of the airport.
 */
#include <iostream>
#include "structure.h"
#include "airport.h"

Airport::Airport(Timeline* timeline) {
    this->_timeline = timeline;
    this->departureWaitTime = 0;
    this->arrivalWaitTime = 0;
    this->grandchildrenDepartureWaitTime = 0;
    this->grandchildrenArrivalWaitTime = 0;

    this->planesDeparted = 0;
    this->planesArrived = 0;
    this->planesCrashed = 0;

    this->peopleArrived = 0;
    this->peopleKilled = 0;
    this->grandchildrenKilled = 0;

    this->cargoArrived = 0;
    this->cargoDestroyed = 0;
}

Airport::~Airport() {
    delete this->_timeline;
    this->_timeline = nullptr;
}

int Airport::getValue(Plane* plane) {
	int value;
	int weightPeople = 10;
	int weightCargo = 5;
	int fuelFactor = 3;
	float multiplierGrandchildren = 1.25;

	if (plane->grandchildren) {
            value = (multiplierGrandchildren * weightPeople * plane->numPeople) + 
                     (weightCargo * plane->numCargo) + 
                     -((1-multiplierGrandchildren) * fuelFactor * plane->fuel);
        } else {
            value = (weightPeople * plane->numPeople) + 
                     (weightCargo * plane->numCargo) +
                     -(fuelFactor * plane->fuel);
        }

	return value;
}

bool Airport::refuel(Plane* plane) {
    if(plane->fuel < 20) {
        return true;
    } else {
        return false;
    }
}

bool Airport::depart(Plane* plane) {
    return true;
}

bool Airport::land(Plane* plane) {
    //if(plane == maxPlaneToLand1 || plane == maxPlaneToLand2) { return true; } else { return false; }
    return true;
}

bool Airport::crash(Plane* plane) {
	if (!land(plane) && plane->time == 1) {return true;} else {return false;}
}

void Airport::process() {
    TimelineIterator* iter = this->_timeline->iterate();   
    delete iter;
}

void Airport::print() {
    printf("Number of planes departed: %d\n", this->planesDeparted);
    printf("Number of planes arrived: %d\n", this->planesArrived);
    printf("Number of planes crashed: %d\n", this->planesCrashed);

    printf("Number of people arrived: %d\n", this->peopleArrived);
    printf("Number of people killed: %d\n", this->peopleKilled);
    printf("Number of grandchildren killed: %d\n", this->grandchildrenKilled);

    printf("Amount of cargo arrived: %d\n", this->cargoArrived);
    printf("Amount of cargo destroyed: %d\n", this->cargoDestroyed);

    printf("Average departure wait time: %.2fs\n", this->departureWaitTime);
    printf("Average arrival wait time: %.2fs\n", this->arrivalWaitTime);
    printf("Average departure wait time for grandchildren: %.2fs\n", this->grandchildrenDepartureWaitTime);
    printf("Average arrival wait time for grandchildren: %.2fs\n", this->grandchildrenArrivalWaitTime);
}
