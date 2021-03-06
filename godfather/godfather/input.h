/*
 * input.h
 * Defines the input of the classes in structure.cpp.
 */
#ifndef _input_h
#define _input_h
#include "airport.h"

using namespace std;

class AirportInputProcessor {
    private:
        Airport* _airport;

    public:
        AirportInputProcessor(char* input);
        ~AirportInputProcessor();

        void process();
        void print();
        void parseData(string CSV, struct Plane* plane);
};

#endif
