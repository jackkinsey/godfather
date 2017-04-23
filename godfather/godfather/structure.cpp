/*
 * structure.cpp
 * Implements the timeline data structure.
 */
#include "array.h"
#include "structure.h"
#include "airport.h"

struct IndexNode {
    int index;
    DynamicArray<struct Plane>* data;
};

struct IndexNode* Timeline::createIndex(int index) {

}

Timeline::Timeline() {

}

Timeline::~Timeline() {

}

struct IndexNode* Timeline::fetch(int index) {

}

bool Timeline::push(int index, struct Plane el) {

}
