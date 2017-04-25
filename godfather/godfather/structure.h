/*
 * structure.h
 * Defines the interface of the timeline data structure in structure.cpp.
 */
#ifndef _structure
#define _structure
#include "array.h"
#include "airport.h"

struct IndexNode;

class TimelineIterator {
    private:
        DynamicArrayIterator<struct IndexNode>* _iter;

    public:
        TimelineIterator(DynamicArray<struct IndexNode>* iter);
        ~TimelineIterator();

        struct IndexNode* step();
}

class Timeline {
    private:
        DynamicArray<struct IndexNode>*  _center; //The central timeline.

        struct IndexNode* createIndex(int depth, int index);
    public:
        Timeline();
        ~Timeline();

        TimelineIterator* iterate();
        bool push(int index, struct Plane* el);
};

#endif
