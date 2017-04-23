/*
 * structure.h
 * Defines the interface of the timeline data structure in structure.cpp.
 */
#ifndef _structure
#define _structure
#include "array.h"
#include "airport.h"

struct IndexNode;

class Timeline {
    private:
        DynamicArray<struct IndexNode>*  _center; //The central timeline.

        struct IndexNode* createIndex(int index);
    public:
        Timeline();
        ~Timeline();

        struct IndexNode* fetch(int depth); //Returns the IndexNode that is int depth deep in the Timeline.
        bool push(int index, struct Plane& el); //Appends a Plane to the end of the IndexNode's list with index int index.
};

#endif
