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

        bool processed;
        int runwaysUsed;

        int departureWaitTime;
        int arrivalWaitTime;
        int grandchildrenDepartureWaitTime;
        int grandchildrenArrivalWaitTime;

        int planesDeparted;
        int grandchildrenDeparted;
        int planesArrived;
        int grandchildrenArrived;
        int planesCrashed;

        int peopleArrived;
        int peopleKilled;
        int grandchildrenKilled;

        int cargoArrived;
        int cargoDestroyed;

	bool refuel(struct Plane* plane, int timeIndex);
	bool depart(struct Plane* plane, int timeIndex);
	bool land(struct Plane* plane, int timeIndex);
	bool crash(struct Plane* plane);
	bool delay(struct Plane* plane, int timeIndex, bool arriving);

        void processPlane(struct Plane* plane, int timeIndex);

	int getValue(struct Plane* plane);

        static const char ARRIVAL = 'A';
        static const char DEPARTURE = 'D';
        static const int RUNWAY_COUNT = 2;
        static const int FUEL_REQUIREMENT = 20;
        static const int REFUELING_DELAY = 10;
	
    public:
        Airport(Timeline* timeline);
        ~Airport();

	void process();
        void print();
};

#endif
