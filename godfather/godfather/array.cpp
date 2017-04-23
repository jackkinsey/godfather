/*
 * array.cpp
 * Implements the (templated) dynamic array data structure.
 */
#include <stdlib.h> //For malloc, etc.
#include <string.h> //For memcpy.
#include <iostream>
#include "array.h"

struct Node{
    int datum;
    struct Node* next;
    struct Node* prev;
};

DynamicArray::DynamicArray(int size) {
    //Allocate the memory for the array, initialize it, and set the size counter.
    //Negative sizes are treated as 0.
    if(size < 0) { size = 0; }
    if(size > 0) {
        this->_first = this->addNode(0, NULL, NULL);
        this->_last = this->_first;
        for(int i = 0; i < size - 1; i++) {
            this->_last = this->addElementBack(0);
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

struct Node* DynamicArray::addNode(int datum, struct Node* next, struct Node* prev) {
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

struct Node* DynamicArray::addElementFront(int el) {
    //Adds an element to the front of the array, creating a new node.
    //If the array hasn't been initialized, takes care of that instead.
    if(this->_size == 0) {
        this->_first = this->addNode(el, NULL, NULL);
        this->_last = this->_first;
        this->_size++;
        return this->_first;
    } else {
        struct Node* node = this->addNode(el, this->_first, NULL);
        this->_first->prev = node;
        this->_first = node;
        this->_size++;
        return node;
    }
}

struct Node* DynamicArray::addElementBack(int el) {
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

bool DynamicArray::insertElement(int el, int loc) {
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

bool DynamicArray::removeFront() {
    //Removes the first node from memory.
    return this->deleteElement(0);
}

bool DynamicArray::removeBack() {
    //Removes the last node from memory.
    return this->deleteElement(this->_size-1);
}

void DynamicArray::print() {
    //Prints the array contents nicely, like a Python array.
    if(this->_size != 0) {
        struct Node* head = this->_first;
        //std::cout << 's' << this->_size << '['; //Debug printline.
        std::cout << '[';
        for(int i = 0; i < this->_size - 1; i++) {
            //Scan through the list and print every node's datum.
            std::cout << head->datum;
            head = head->next;
            std::cout << ',' << ' ';
        }
        std::cout << head->datum;
        std::cout << ']' << '\n';
    } else {
        std::cout << "[]" << '\n';
    }
}
