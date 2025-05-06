#ifndef PQHeap_H
#define PQHeap_H
#include <utility>

struct Element {
    int e; //value
    int p; //priority

    Element(int value = 0, int priority = 0) : e(value), p(priority) {}
    
    bool operator>(const Element &other) const {
        return p > other.p;
    }

    bool operator<(const Element &other) const {
        return p < other.p;
    }

    bool operator==(const Element &other) const {
        return p == other.p;
    }
};

class PriorityQueue {
public:
    virtual void insert(int e, int p) = 0;
    virtual Element extractMax() = 0;
    virtual Element peek() const = 0;
    virtual void modifyKey(int e, int p) const = 0;
    virtual int returnSize() const = 0;
    virtual void clear() = 0;
    virtual void fillRandom(int size, int seed) = 0;
};

class HeapPriorityQueue : public PriorityQueue {

};

#endif