/*
 * structure.cpp
 * Implements the timeline data structure.
 */
#include "array.h"
#include "airport.h"

struct IndexNode {
    int index;
    DynamicArray<struct Plane>* data;
};
