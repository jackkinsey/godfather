/*
 * array.h
 * Implements the (templated) dynamic array data structure.
 */
#ifndef _dynamic_h
#define _dynamic_h
#include <stdlib.h> //For malloc, etc.
#include <string.h> //For memcpy.
#include <iostream>

template <class T> struct Node {
    T* datum;
    struct Node<T>* next;
    struct Node<T>* prev;
};

template <class T> class DynamicArrayIterator {
    private:
        struct Node<T>* _iter;
        struct Node<T>* _next;
        bool _direction; //True is forward, false is backward.

    public:
        DynamicArrayIterator(struct Node<T>* iter, bool direction);

        T* step();
};

template <class T> class DynamicArray {
    private:
        struct Node<T>* _first; //Pointer to the eventual physical array space.
        struct Node<T>* _last; //Pointer to the eventual physical array space.

        int _size = 0; //How many nodes does the array contain?

        //Helper methods.
        struct Node<T>* addNode(T* datum, struct Node<T>* next, struct Node<T>* prev);
        struct Node<T>* scan(int loc);

        struct Node<T>* _sort(struct Node<T>* head);
        struct Node<T>* _merge(struct Node<T>* left, struct Node<T>* right);
        struct Node<T>* _split(struct Node<T>* head);

    public:
        //Public interface.
        DynamicArray(int size = 0); //Default size of a DynamicArray is 0.
        ~DynamicArray();

        struct Node<T>* append(T* el);
        struct Node<T>* insert(T* el, int loc);
        bool remove(int loc);
        void sort();
        DynamicArrayIterator<T>* iterate(bool direction=true);

        int size() { return this->_size; };
};

template <class T> DynamicArrayIterator<T>::DynamicArrayIterator(struct Node<T>* iter, bool direction) {
    this->_iter = nullptr;   
    this->_next = iter;
    this->_direction = direction;
}

template <class T> T* DynamicArrayIterator<T>::step() {
    //Moves to the next node in the list and returns its datum.
    if(!this->_iter) {
        this->_iter = this->_next;
        this->_next = nullptr;
        if(this->_iter) {
            return this->_iter->datum;
        } else {
            return nullptr;
        }
    }
    if(this->_direction && this->_iter) {
        this->_iter = this->_iter->next;
    } else if(this->_iter) {
        this->_iter = this->_iter->prev;
    } else {
        return nullptr;
    }
    if(this->_iter) {
        return this->_iter->datum;
    } else {
        return nullptr;
    }
}

template <class T> DynamicArray<T>::DynamicArray(int size) {
    //Allocate the memory for the array, initialize it, and set the size counter.
    //Negative sizes are treated as 0.
    if(size < 0) { size = 0; }
    if(size > 0) {
        this->_first = this->addNode(nullptr, nullptr, nullptr);
        this->_last = this->_first;
        for(int i = 0; i < size - 1; i++) {
            this->_last = this->append(nullptr);
        }
    } else {
        this->_first = nullptr;
        this->_last = nullptr;
    }
    this->_size = size;
}

template <class T> DynamicArray<T>::~DynamicArray() {
    //Frees the memory allocated to all nodes.
    struct Node<T>* head = this->_first;
    struct Node<T>* next;
    while(head) {
        next = head->next;
        delete head->datum;
        free(head);
        head = next;
    }
}

template <class T> struct Node<T>* DynamicArray<T>::addNode(T* datum, struct Node<T>* next, struct Node<T>* prev) {
    //Allocates memory for a new node and stitches it into the linked list.
    struct Node<T>* node = (struct Node<T>*)malloc(sizeof(struct Node<T>));
    node->datum = datum;
    node->next = next;
    node->prev = prev;
    return node;
}

template <class T> struct Node<T>* DynamicArray<T>::scan(int loc) {
    //Returns a pointer to the node at the given location.
    //Location must be within the bounds of the array.
    if(loc < 0 || loc >= this->_size) { return nullptr; }
    struct Node<T>* head;
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

template <class T> struct Node<T>* DynamicArray<T>::append(T* el) {
    //Adds an element to the back of the array, creating a new node.
    //If the array hasn't been initialized, takes care of that instead.
    if(this->_size == 0) {
        this->_first = this->addNode(el, nullptr, nullptr);
        this->_last = this->_first;
        this->_size++;
        return this->_first;
    } else {
        struct Node<T>* node = this->addNode(el, nullptr, this->_last);
        this->_last->next = node;
        this->_last = node;
        this->_size++;
        return node;
    }
}

template <class T> struct Node<T>* DynamicArray<T>::insert(T* el, int loc) {
    //Inserts an element at a given location, creating a new node.
    //Location must be within bounds of the array.
    if(loc < 0 || loc >= this->_size) { return nullptr; }
    struct Node<T>* head = this->scan(loc);
    struct Node<T>* prev = head->prev;
    struct Node<T>* node = this->addNode(el, head, prev);
    head->prev = node;
    if(prev) { //Is this not the first node?
        prev->next = node;
    } else { //There's a new first in town.
        this->_first = node;
    }
    this->_size++;
    return node;
}

template <class T> bool DynamicArray<T>::remove(int loc) {
    //Removes a given node from memory.
    //Location must be within bounds of the array.
    if(loc < 0 || loc >= this->_size){ return false; }
    struct Node<T>* head = this->scan(loc);
    struct Node<T>* prev = head->prev;
    struct Node<T>* next = head->next;
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

template <class T> void DynamicArray<T>::sort() {
    //Public sort function. Sorts the list greatest to least.
    this->_first = this->_sort(this->_first);
    this->_last = this->_first;
    while(this->_last->next) {
        this->_last = this->_last->next;
    }
}

template <class T> struct Node<T>* DynamicArray<T>::_sort(struct Node<T>* head) {
    //Private recursive sort function.
    //Uses MergeSort.
    if(head && head->next) {
        struct Node<T>* back = this->_split(head);
        head = this->_sort(head);
        back = this->_sort(back);
        head = this->_merge(head, back);
    }
    return head;
}

template <class T> struct Node<T>* DynamicArray<T>::_merge(struct Node<T>* left, struct Node<T>* right) {
    //Merges two lists.
    struct Node<T>* out = nullptr;
    if(left == nullptr) return right;
    if(right == nullptr) return left;
    if(*(left->datum) > *(right->datum)) {
        out = right;
        out->next = this->_merge(left, right->next);
    } else {
        out = left;
        out->next = this->_merge(right, left->next);
    }
    return out;
}

template <class T> struct Node<T>* DynamicArray<T>::_split(struct Node<T>* head) {
    //Splits the list with first node head in half.
    struct Node<T>* fast;
    struct Node<T>* slow;
    slow = head;
    fast = head->next;
    while(fast) {
        fast = fast->next;
        if(fast) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    struct Node<T>* out = slow->next;
    out->prev = nullptr;
    slow->next = nullptr;
    return out;
}

template <class T> DynamicArrayIterator<T>* DynamicArray<T>::iterate(bool direction) {
    //Returns an array iterator that allows the user to step through the array
    // in the given direction. True: forward, false: backward.
    DynamicArrayIterator<T>* out;
    if(direction) {
        out = new DynamicArrayIterator<T>(this->_first, direction);
    } else {
        out = new DynamicArrayIterator<T>(this->_last, direction);
    }
    return out;
}
#endif
