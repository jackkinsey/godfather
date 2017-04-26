/*
 * structure.h
 * Defines the interface of the timeline data structure in structure.cpp.
 */
#ifndef _structure_h
#define _structure_h
#include "array.h"

struct IndexNode {
    int index;
    DynamicArray<struct Plane>* data;
};

struct Plane {
	char dataType;
	char action;
	bool grandchildren;
	int time;
	int fuel;
	int numPeople;
	int numCargo;
	double value;
        bool operator>(const Plane&) const;
};


class TimelineIterator {
    private:
        DynamicArrayIterator<struct IndexNode>* _iter;

    public:
        TimelineIterator(DynamicArray<struct IndexNode>* iter);
        ~TimelineIterator();

        struct IndexNode* step();
};

class Timeline {
    private:
        DynamicArray<struct IndexNode>*  _center; //The central timeline.

        struct IndexNode* createIndex(int depth, int index);

    public:
        Timeline();
        ~Timeline();

        TimelineIterator* iterate();
        void deleteIndex(struct IndexNode* index);
        bool push(int index, struct Plane* el);
};

#endif
