/*
 * airport.h
 * Defines the structure of the classes in airport.cpp.
 */
#ifndef _airport
#define _airport

struct Plane;

class Airport {

	int numberOfDepartingPlanes;
	int numberOfArrivingPlanes; 

	bool refuel(Plane);
	bool depart(Plane);
	bool land(Plane);
	bool crash(Plane);
	int getValue(Plane);
	
public:
	void process();

};

#endif
