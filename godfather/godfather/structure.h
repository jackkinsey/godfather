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

        struct IndexNode* fetch(int index);
        bool push(int index, Plane el);
};

#endif
