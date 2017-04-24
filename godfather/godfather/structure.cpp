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
    /*
     * for all nodes in center:
     *  delete node->datum->data
     */
    for
    delete this->_center;
}

struct IndexNode* Timeline::fetch(int depth) {
    /*
     * return center[depth]
     */
    return NULL;
}

bool Timeline::push(int index, struct Plane& el) {
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
