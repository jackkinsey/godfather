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
    return NULL;
}

Timeline::Timeline() {
    this->_center = new DynamicArray<struct IndexNode>;
}

Timeline::~Timeline() {
    delete this->_center;
}

struct IndexNode* Timeline::fetch(int depth) {
    return NULL;
}

bool Timeline::push(int index, struct Plane& el) {
    return NULL;
}
