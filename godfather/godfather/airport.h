/*
 * airport.h
 * Defines the structure of the classes in airport.cpp.
 */
#ifndef _airport
#define _airport
#include "structure.h"

struct Plane;

class Airport {
    private:
        Timeline* _timeline;

	int numberOfDepartingPlanes;
	int numberOfArrivingPlanes; 

	bool refuel(Plane);
	bool depart(Plane);
	bool land(Plane);
	bool crash(Plane);
	int getValue(Plane);
	
    public:
        Airport(Timeline* timeline);
        ~Airport();
	void process();
        void print();

};

#endif
