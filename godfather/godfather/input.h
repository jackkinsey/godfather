/*
 * input.h
 * Defines the input of the classes in structure.cpp.
 */
#ifndef _input
#define _input
#include "airport.h"

using namespace std;

struct Plane;

class AirportInputProcessor {
    private:
        Airport* _airport;

    public:
        AirportInputProcessor(char[] file);
        ~AirportInputProcessor();
        void parseData(string CSV, Plane *plane);

};

#endif
