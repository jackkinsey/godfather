/*
 * structure.cpp
 * Implements the timeline data structure.
 */
#include "array.h"
#include "structure.h"

bool Plane::operator>(const Plane& plane) const { return value > plane.value; }

TimelineIterator::TimelineIterator(DynamicArray<struct IndexNode>* iter) {
    this->_iter = iter->iterate();
}

TimelineIterator::~TimelineIterator() {
    delete this->_iter;
    this->_iter = nullptr;
}

struct IndexNode* TimelineIterator::step() {
    //Return the current IndexNode and step forward.
    return this->_iter->step();
}

struct IndexNode* Timeline::createIndex(int depth, int index) {
    //Add a new node to the central timeline.
    //The new node is depth deep in the timeline, and is
    // initialized to have time index of index.
    //(Returns nullptr if depth is larger than the array size + 1.)
    if(depth == this->_center->size()) {
        IndexNode* newTime = new IndexNode;
        newTime->index = index;
        newTime->data = new DynamicArray<struct Plane>;
        this->_center->append(newTime);
        //printf("depth at %d %d\n", depth, index);
        return newTime;
    } else if(depth > this->_center->size()) {
        //printf("bigdepth at %d %d\n", depth, index);
        return nullptr;   
    } else {
        IndexNode* newTime = new IndexNode;
        newTime->index = index;
        newTime->data = new DynamicArray<struct Plane>;
        if(this->_center->insert(newTime, depth)) { 
            //printf("inserted at %d %d\n", depth, index);
            return newTime; 
        } else { 
            delete newTime->data;
            delete newTime; 
            //printf("failed at %d %d\n", depth, index);
            return nullptr; 
        }
    }
}

void Timeline::deleteIndex(struct IndexNode* index) {
    delete index->data;
    index->data = nullptr;
}

Timeline::Timeline() {
    //Initialize the timeline's central array.
    this->_center = new DynamicArray<struct IndexNode>;
}

Timeline::~Timeline() {
    //Delete all the subarrays in the timeline,
    // then delete the timeline's central array.
    DynamicArrayIterator<struct IndexNode>* iter = this->_center->iterate();
    struct IndexNode* loc = iter->step();
    while(loc) {
        this->deleteIndex(loc);
        loc = iter->step();
    }
    delete iter;
    delete this->_center;
}

TimelineIterator* Timeline::iterate() {
    //Returns an iterator that allows the user to step through the timeline.
    TimelineIterator* out = new TimelineIterator(this->_center);
    return out;
}

bool Timeline::push(int index, struct Plane* el) {
    //Appends a Plane to the end of the IndexNode's list with index int index.
    TimelineIterator* iter = this->iterate();
    struct IndexNode* node = iter->step();
    int count = 0;
    while(node) { //Walk the list until we find an IndexNode with
                  // the index we're looking for, or greater.
        if(node->index >= index) { break; }
        node = iter->step();
        count++;
    }
    delete iter;
    if(node) { //If the node isn't null...
        if(node->index == index) { //Either append the element (the node already exists)...
            node->data->append(el);
            //printf("appending to %d\n", index);
        } else if(node->index > index) { //...or make the node and append the element.
            this->createIndex(count, index)->data->append(el);
            //printf("c:appending to %d\n", index);
        }
        return true;
    } else { //If the node is null, make the node and append the element.
        this->createIndex(count, index)->data->append(el);
        //printf("cn:appending to %d\n", index);
        return true;
    }
}
