/*
 * airport.h
 * Defines the structure of the classes in airport.cpp.
 */
#ifndef _airport_h
#define _airport_h
#include "structure.h"

class Airport {
    private:
        Timeline* _timeline;

        float departureWaitTime;
        float arrivalWaitTime;
        float grandchildrenDepartureWaitTime;
        float grandchildrenArrivalWaitTime;

        int planesDeparted;
        int planesArrived;
        int planesCrashed;

        int peopleArrived;
        int peopleKilled;
        int grandchildrenKilled;

        int cargoArrived;
        int cargoDestroyed;

	bool refuel(Plane* plane);
	bool depart(Plane* plane);
	bool land(Plane* plane);
	bool crash(Plane* plane);
	int getValue(Plane* plane);
	
    public:
        Airport(Timeline* timeline);
        ~Airport();

	void process();
        void print();
};

#endif
