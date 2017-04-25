/*
 * main.cpp
 * Entry point for execution.
 */
#include <iostream>
#include <time.h>
#include "input.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Usage: godfather input.csv" << '\n';
    }
    clock_t tStart = clock();
    AirportInputProcessor* processor = new AirportInputProcessor(argv[1]);
    processor->process();
    processor->print();
    delete processor;
    printf("Process time: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
