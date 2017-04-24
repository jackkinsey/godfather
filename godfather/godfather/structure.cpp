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

struct IndexNode* Timeline::createIndex(int depth, int index) {
    IndexNode newTime = new IndexNode;
    newTime->index = index;
    newTime->data = new DynamicArray<struct Plane>;
    this->_center.insert(newTime, depth)
}

Timeline::Timeline() {
    this->_center = new DynamicArray<struct IndexNode>;
}

Timeline::~Timeline() {
    DynamicArrayIterator<struct IndexNode> iter = this->_center.iterate();
    struct IndexNode* loc = iter.step();
    while(loc) {
        delete loc->data;
        loc = iter.step();
    }
    delete iter;
    delete this->_center;
}

struct IndexNode* Timeline::fetch(int depth) {
    //Returns the IndexNode that is int depth deep
    // in the Timeline. int depth must be within bounds.
    if(depth >= this->_center.size()) { return NULL; }
    DynamicArrayIterator<struct IndexNode> iter = this->_center.iterate();
    struct IndexNode* loc = iter.step();

    return NULL;
}

bool Timeline::push(int index, struct Plane* el) {
    //Appends a Plane to the end of the IndexNode's list with index int index.
    /*
     * while center[i].index < index:
     *  i++
     * if center[i].index==index:
     *  center[i].data.append(el);
     * else:
     *  createIndex(i, index).data.append(el);
     */
    return NULL;
}
