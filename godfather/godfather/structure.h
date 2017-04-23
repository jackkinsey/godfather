/*
 * structure.h
 * Defines the interface of the timeline data structure in structure.cpp.
 */
#ifndef _structure
#define _structure
#include "array.h"

struct TimeNode;

class Timeline {
    private:
        DynamicArray*<TimeNode>  _center; //The central timeline.
    public:

}

#endif
