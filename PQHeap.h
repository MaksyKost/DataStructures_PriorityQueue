#ifndef PQHeap_H
#define PQHeap_H
#include <utility>
#include <vector>

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
private:
    std::vector<Element> heap;

    void up(int index);
    void down(int index);
    void findIndex(int value) const;

public:
    void insert(int e, int p) override;
    Element extractMax() override;
    Element peek() const override;
    void modifyKey(int e, int p) const override;
    int returnSize() const override;
    void clear() override;
    void fillRandom(int size, int seed) override;
};

#endif