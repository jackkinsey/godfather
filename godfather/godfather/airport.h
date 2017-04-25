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

	bool refuel(Plane& plane);
	bool depart(Plane& plane);
	bool land(Plane& plane);
	bool crash(Plane& plane);
	void getValue(Plane& plane);
	
    public:
        Airport(Timeline* timeline);
        ~Airport();
	void process();
        void print();
};

#endif
