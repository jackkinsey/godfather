/*
 * array.h
 * Implements the (templated) dynamic array data structure.
 */
#ifndef _structure
#define _structure
#include <stdlib.h> //For malloc, etc.
#include <string.h> //For memcpy.
#include <iostream>

template <class T> struct Node{
    T datum;
    struct Node* next;
    struct Node* prev;
};

template <class T> class DynamicArray {
    private:
        struct Node* _first; //Pointer to the eventual physical array space.
        struct Node* _last; //Pointer to the eventual physical array space.

        int _size = 0; //How many nodes does the array contain?

        //Helper methods.
        struct Node* addNode(T datum, struct Node* next, struct Node* prev);
        struct Node* scan(int loc);

    public:
        //Public interface.
        DynamicArray(int size = 0); //Default size of a DynamicArray is 0.
        ~DynamicArray();

        struct Node* append(T el);
        bool insert(T el, int loc);
        bool delete(int loc);
};

DynamicArray::DynamicArray(int size) {
    //Allocate the memory for the array, initialize it, and set the size counter.
    //Negative sizes are treated as 0.
    if(size < 0) { size = 0; }
    if(size > 0) {
        this->_first = this->addNode(NULL, NULL, NULL);
        this->_last = this->_first;
        for(int i = 0; i < size - 1; i++) {
            this->_last = this->append(NULL);
        }
    } else {
        this->_first = NULL;
        this->_last = NULL;
    }
    this->_size = size;
}

DynamicArray::~DynamicArray() {
    //Frees the memory allocated to all nodes.
    struct Node* head = this->_first;
    struct Node* next;
    while(head) {
        next = head->next;
        free(head);
        head = next;
    }
}

template <class T> struct Node* DynamicArray::addNode(T datum, struct Node* next, struct Node* prev) {
    //Allocates memory for a new node and stitches it into the linked list.
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->datum = datum;
    node->next = next;
    node->prev = prev;
    return node;
}

struct Node* DynamicArray::scan(int loc) {
    //Returns a pointer to the node at the given location.
    //Location must be within the bounds of the array.
    if(loc < 0 || loc >= this->_size) { return NULL; }
    struct Node* head;
    //Do we scan from the beginning or the end of the list?
    if(loc >= this->_size/2) { //Start from the end.
        head = this->_last;
        for(int i = this->_size-1; i > loc; i--) {
            head = head->prev;
        }
    } else { //Start from the beginning.
        head = this->_first;
        for(int i = 0; i < loc; i++) {
            head = head->next;
        }
    }
    return head;
}

template <class T> struct Node* DynamicArray::append(T el) {
    //Adds an element to the back of the array, creating a new node.
    //If the array hasn't been initialized, takes care of that instead.
    if(this->_size == 0) {
        this->_first = this->addNode(el, NULL, NULL);
        this->_last = this->_first;
        this->_size++;
        return this->_first;
    } else {
        struct Node* node = this->addNode(el, NULL, this->_last);
        this->_last->next = node;
        this->_last = node;
        this->_size++;
        return node;
    }
}

template <class T> bool DynamicArray::insert(T el, int loc) {
    //Inserts an element at a given location, creating a new node.
    //Location must be within bounds of the array.
    if(loc < 0 || loc >= this->_size) { return false; }
    struct Node* head = this->scan(loc);
    struct Node* prev = head->prev;
    struct Node* node = this->addNode(el, head, prev);
    head->prev = node;
    if(prev) { //Is this not the first node?
        prev->next = node;
    } else { //There's a new first in town.
        this->_first = node;
    }
    this->_size++;
    return true;
}

bool DynamicArray::deleteElement(int loc) {
    //Removes a given node from memory.
    //Location must be within bounds of the array.
    if(loc < 0 || loc >= this->_size){ return false; }
    struct Node* head = this->scan(loc);
    struct Node* prev = head->prev;
    struct Node* next = head->next;
    //Stitch the list back together to close the gap,
    //  but be careful of null pointers.
    if(prev) { //Is this not the first node?
        prev->next = next;
    } else { //There's a new first in town.
        this->_first = next;
    }
    if(next) { //Is this not the last node?
        next->prev = prev; 
    } else { //There's a new last in town.
        this->_last = prev;
    }
    free(head);
    this->_size--;
    return true;
}
#endif
