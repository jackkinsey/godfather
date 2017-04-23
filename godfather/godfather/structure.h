/*
 * structure.h
 * Defines the structure of the classes in structure.cpp.
 */
#ifndef _structure
#define _structure

struct Node;

class DynamicArray {
    private:
        struct Node* _first; //Pointer to the eventual physical array space.
        struct Node* _last; //Pointer to the eventual physical array space.

        int _size = 0; //How many nodes does the array contain?

        //Helper methods.
        struct Node* addNode(int datum, struct Node* next, struct Node* prev);
        struct Node* scan(int loc);

    public:
        //Public interface.
        DynamicArray(int size = 0); //Default size of a DynamicArray is 0.
        ~DynamicArray();

        struct Node* addElementFront(int el);
        struct Node* addElementBack(int el);
        bool insertElement(int el, int loc);
        bool deleteElement(int loc);
        bool removeFront();
        bool removeBack();
        
        //Get size, count, and utilization (as a float).
        int size(){ return this->_size; };
        
        void print();
};

#endif
