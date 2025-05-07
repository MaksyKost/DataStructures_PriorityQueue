#include <iostream>
#include <cstdlib>
#include "PQHeap.h"

HeapPriorityQueue::HeapPriorityQueue(int initialCapacity) {
    heap = new Element[initialCapacity];
    capacity = initialCapacity;
    count = 0;
}

HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] heap;
}

void HeapPriorityQueue::resize() {
    capacity *= 2;
    Element* newHeap = new Element[capacity];
    for (int i = 0; i < count; ++i) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
}

void HeapPriorityQueue::up(int index) {
    while (index > 0){
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else break;
    }
}

void HeapPriorityQueue::insert(int e, int p) {
    if (count == capacity) resize();

    heap[count] = Element(e, p);
    up(count);
    count++;
}

void HeapPriorityQueue::down(int index) {
    int leftChild = index * 2 + 1;
    int rightChild = index * 2 + 2;
    int largest = index;

    while (leftChild < count) {
        if (leftChild < count && heap[leftChild] > heap[largest]) {
            largest = leftChild;
        } 
        if (rightChild < count && heap[rightChild] > heap[largest]) {
            largest = rightChild;
        } else break;
    }

    std::swap(heap[index], heap[largest]);
    index = largest;
}

Element HeapPriorityQueue::extractMax() {
    if (count == 0) {
        std::cerr << "Queue is empty" << std::endl;
        return Element();
    }

    Element max = heap[0];
    std::swap(heap[0], heap[count - 1]);
    count--;
    down(0);
    return max;
}

void HeapPriorityQueue::print() const {
    for (int i = 0; i < count; ++i) {
        std::cout << "(" << heap[i].e << ", " << heap[i].p << ") ";
    }
    std::cout << std::endl;
}

Element HeapPriorityQueue::peek() const {
    if (count == 0) {
        std::cerr << "Queue is empty" << std::endl;
        return Element();
    }
    return heap[0];
}

int HeapPriorityQueue::returnSize() const {
    return count;
}

void HeapPriorityQueue::clear() {
    count = 0;
}

int HeapPriorityQueue::findIndex(int value) const {
    for (int i = 0; i < count; ++i) {
        if (heap[i].e == value) return i;
    }
    return -1;
}

void HeapPriorityQueue::modifyKey(int e, int newPriority) {
    int a = findIndex(e);
    if (a == -1) {
        std::cerr << "Can't find element\n";
        return;
    }

    int oldPriority = heap[a].p;
    heap[a].p = newPriority;
    if (newPriority > oldPriority) up(a);
    else down(a);
}

void HeapPriorityQueue::fillRandom(int size, int seed) {
    srand(seed);

    for (int i = 0; i < size; ++i) {
        int value = rand() % 1001;
        int priority = rand() % 101;
        insert(value, priority);
    }
}