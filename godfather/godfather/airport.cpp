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
    this->grandchildrenDeparted = 0;
    this->planesArrived = 0;
    this->grandchildrenArrived = 0;
    this->planesCrashed = 0;

    this->peopleArrived = 0;
    this->peopleKilled = 0;
    this->grandchildrenKilled = 0;

    this->cargoArrived = 0;
    this->cargoDestroyed = 0;

    this->processed = false;
    this->runwaysUsed = 0;
}

Airport::~Airport() {
    delete this->_timeline;
    this->_timeline = nullptr;
}

int Airport::getValue(struct Plane* plane) {
        //Set the weights.
	int value;
	int weightPeople = 10;
	int weightCargo = 5;
	int fuelFactor = 3;
	float multiplierGrandchildren = 1.25;

        //Weight the planes.
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

void Airport::processPlane(struct Plane* plane, int timeIndex) {
    //Process the plane.
    if(this->runwaysUsed >= Airport::RUNWAY_COUNT) { //If there aren't any runways left...
        if(plane->action == Airport::ARRIVAL) { //And the plane is arriving...
            if(plane->fuel == 1) { //But it's out of fuel...
                this->crash(plane); //...it crashes.
            } else { //Otherwise...
                this->delay(plane, timeIndex, true); //...it's delayed.
            }
        } else if(plane->action == Airport::DEPARTURE) { //And the plane is departing...
            this->delay(plane, timeIndex, false); //...it's delayed.
        } else {
            //I don't know what you did, but something bad is going to happen because of it.
            return;
        }
    } else { //If there are free runways...
        if(plane->action == Airport::ARRIVAL) { //And the plane is arriving...
            this->land(plane, timeIndex); //...land it, and use a runway.
            this->runwaysUsed++;
        } else if(plane->action == Airport::DEPARTURE) { //And the plane is departing...
            if(plane->fuel < Airport::FUEL_REQUIREMENT) { //If it doesn't meet the fuel requirement...
                this->refuel(plane, timeIndex); //Send it to refuel.
            } else { //Otherwise...
                this->depart(plane, timeIndex); //Depart it, and use a runway.
                this->runwaysUsed++;
            }
        } else {
            //I don't know what you did, but something bad is going to happen because of it.
            return;
        }
    }
}

struct Plane* planeCopy(struct Plane* plane) {
    //Make a physical copy of a Plane struct.
    struct Plane* newPlane = new struct Plane;
    newPlane->dataType = plane->dataType;
    newPlane->action = plane->action;
    newPlane->grandchildren = plane->grandchildren;
    newPlane->time = plane->time;
    newPlane->fuel = plane->fuel;
    newPlane->numPeople = plane->numPeople;
    newPlane->numCargo = plane->numCargo;
    newPlane->value = plane->value;
    return newPlane;
}

bool Airport::refuel(struct Plane* plane, int timeIndex) {
    //Copies the plane so it doesn't get deleted twice further down the road.
    //(That would be an error.)
    struct Plane* newPlane = planeCopy(plane);
    newPlane->fuel = Airport::FUEL_REQUIREMENT;
    this->_timeline->push(timeIndex + Airport::REFUELING_DELAY, newPlane);
    return true;
}

bool Airport::depart(struct Plane* plane, int timeIndex) {
    //Send the plane off, and update statistics.
    int timeWaited = timeIndex - plane->time;
    if(plane->grandchildren) {
        this->grandchildrenDepartureWaitTime += timeWaited;
        this->grandchildrenDeparted += 1;
    }
    this->planesDeparted += 1;
    this->departureWaitTime += timeWaited;
    return true;
}

bool Airport::land(struct Plane* plane, int timeIndex) {
    //Land the plane, and update statistics.
    int timeWaited = timeIndex - plane->time;
    if(plane->grandchildren) {
        this->grandchildrenArrivalWaitTime += timeWaited;
        this->grandchildrenArrived += 1;
    }
    this->planesArrived += 1;
    this->arrivalWaitTime += timeWaited;
    this->peopleArrived += plane->numPeople;
    this->cargoArrived += plane->numCargo;
    return true;
}

bool Airport::crash(struct Plane* plane) {
    //Crash the plane, and update statistics.
    if(plane->grandchildren) {
        this->grandchildrenKilled += 1;
    }
    this->planesCrashed += 1;
    this->peopleKilled += plane->numPeople;
    this->cargoDestroyed += plane->numCargo;
    return true;
}

bool Airport::delay(struct Plane* plane, int timeIndex, bool arriving) {
    //bool arriving is true if the plane is arriving, false if it's departing.
    //Copies the plane so it doesn't get deleted twice further down the road.
    //(That would be an error.)
    //Delay the plane to the next time index.
    struct Plane* newPlane = planeCopy(plane);
    if(arriving) {
        newPlane->fuel -= 1;
    }
    this->_timeline->push(timeIndex + 1, newPlane);
    return true;
}

void Airport::process() {
    //Main processing algorithm.
    if(this->processed) return; //Don't process if it's already been done.
    TimelineIterator* iter = this->_timeline->iterate();   
    struct IndexNode* node = iter->step();
    while(node) { //Iterate through all the time indexs.
        int timeIndex = node->index;
        DynamicArray<struct Plane>* time = node->data;

        DynamicArrayIterator<struct Plane>* timeIter = time->iterate();
        struct Plane* plane = timeIter->step();
        while(plane) { //Weight all the planes.
            plane->value = this->getValue(plane);
            plane = timeIter->step();
        }
        delete timeIter;
        timeIter = nullptr;

        time->sort(); //Sort them by weight, greatest to least.

        timeIter = time->iterate();
        plane = timeIter->step();
        while(plane) { //Process all the planes.
            this->processPlane(plane, timeIndex);
            plane = timeIter->step();
        }
        delete timeIter;

        this->runwaysUsed = 0;
        this->_timeline->deleteIndex(node); //Delete the current index (it'll never be used again).
        node = iter->step();
    }
    this->processed = true;
    delete iter;
}

void Airport::print() {
    if(this->processed) {
        printf("####################################################\n");
        printf("######### Arrival and Departure Statistics #########\n");
        printf("Number of planes departed: %d\n", this->planesDeparted);
        printf("Number of planes arrived: %d\n", this->planesArrived);
        printf("Number of people arrived: %d\n", this->peopleArrived);
        printf("########### Fatality and Crash Stastics ############\n");
        printf("Number of planes crashed: %d\n", this->planesCrashed);
        printf("Number of people killed: %d\n", this->peopleKilled);
        printf("Number of grandchildren killed: %d\n", this->grandchildrenKilled);
        printf("################# Cargo Statistics #################\n");
        printf("Amount of cargo arrived: %d\n", this->cargoArrived);
        printf("Amount of cargo destroyed: %d\n", this->cargoDestroyed);
        printf("############### Wait Time Statistics ###############\n");
        printf("Average departure wait time: %.2ft\n", (float)this->departureWaitTime/(float)this->planesDeparted);
        printf("Average arrival wait time: %.2ft\n", (float)this->arrivalWaitTime/(float)this->planesArrived);
        printf("Average departure wait time for grandchildren: %.2ft\n", (float)this->grandchildrenDepartureWaitTime/(float)this->grandchildrenDeparted);
        printf("Average arrival wait time for grandchildren: %.2ft\n", (float)this->grandchildrenArrivalWaitTime/(float)this->grandchildrenArrived);
    } else {
        printf("The data needs to be processed first.\n");
    }
}
