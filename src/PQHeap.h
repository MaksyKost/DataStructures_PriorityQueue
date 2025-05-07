#ifndef PQHeap_H
#define PQHeap_H


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
    virtual void resize() = 0;
    virtual void insert(int e, int p) = 0;
    virtual Element extractMax() = 0;
    virtual Element peek() const = 0;
    virtual void modifyKey(int e, int p) = 0;
    virtual int returnSize() const = 0;
    virtual void clear() = 0;
    virtual void fillRandom(int size, int seed) = 0;
    virtual void print() const = 0;
    virtual ~PriorityQueue() {}
};

class HeapPriorityQueue : public PriorityQueue {
private:
    Element* heap;
    int capacity;
    int count;

    void up(int index);
    void down(int index);
    int findIndex(int value) const;

public:
    HeapPriorityQueue(int initialCapacity = 10);
    ~HeapPriorityQueue();
    void resize() override;
    void insert(int e, int p) override;
    Element extractMax() override;
    Element peek() const override;
    void modifyKey(int e, int p) override;
    int returnSize() const override;
    void clear() override;
    void fillRandom(int size, int seed) override;
    virtual void print() const override;
};

#endif