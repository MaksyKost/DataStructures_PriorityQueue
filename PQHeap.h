#ifndef PQHeap_H
#define PQHeap_H
#include <utility>

class PriorityQueue {
public:
    virtual void insert(int e, int p) = 0;
    virtual std::pair<int, int> extractMax() = 0;
    virtual std::pair<int, int> peek() const = 0;
    virtual void modifyKey(int e, int p) const = 0;
    virtual int returnSize() const = 0;
    virtual void clear() = 0;
    virtual void fillRandom(int size, int seed) = 0;
};

class HeapPriorityQueue : public PriorityQueue {
    
};

#endif