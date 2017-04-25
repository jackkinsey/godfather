/*
 * main.cpp
 * Entry point for execution.
 */
#include <iostream>
#include "input.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: godfather input.csv" << '\n';
    }
    AirportInputProcessor* processor = new AirportInputProcessor(argv[1]);
    processor->process();
    processor->print();
    delete processor;
    return 0;
}
