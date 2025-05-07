#include <iostream>
#include <cstdlib>
#include "PQHeap.h"

//konstruktor
HeapPriorityQueue::HeapPriorityQueue(int initialCapacity) {
    heap = new Element[initialCapacity];
    capacity = initialCapacity;
    count = 0;
}

//destruktor
HeapPriorityQueue::~HeapPriorityQueue() {
    delete[] heap;
}

//relokacja pamięci
void HeapPriorityQueue::resize() {
    capacity *= 2;
    Element* newHeap = new Element[capacity];
    for (int i = 0; i < count; ++i) {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
}

// przesuwa element "w górę" póki nie znajdzie jego miejsce
void HeapPriorityQueue::up(int index) {
    while (index > 0){
        int parent = (index - 1) / 2;
        if (heap[index] > heap[parent]) {
            std::swap(heap[index], heap[parent]);
            index = parent;
        } else break;
    }
}

// wstawianie elementu o pryorytecie
void HeapPriorityQueue::insert(int e, int p) {
    if (count == capacity) resize();

    heap[count] = Element(e, p);
    up(count);
    count++;
}

// przesuwa element "w dół" póki nie znajdzie jego miejsce
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

// usuwa element o maksymalnym pryorytecie
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

// wyświetla KP
void HeapPriorityQueue::print() const {
    for (int i = 0; i < count; ++i) {
        std::cout << "(" << heap[i].e << ", " << heap[i].p << ") ";
    }
    std::cout << std::endl;
}

// zwraca element o najwyższym pryorytecie
Element HeapPriorityQueue::peek() const {
    if (count == 0) {
        std::cerr << "Queue is empty" << std::endl;
        return Element();
    }
    return heap[0];
}

//zwraca rozmiar
int HeapPriorityQueue::returnSize() const {
    return count;
}

// czyszczy KP
void HeapPriorityQueue::clear() {
    count = 0;
}

// szuka indeks elementu
int HeapPriorityQueue::findIndex(int value) const {
    for (int i = 0; i < count; ++i) {
        if (heap[i].e == value) return i;
    }
    return -1;
}

// zamienia stary pryorytet na nowy
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

//wypełnia losowymi elementami i pryorytetami
void HeapPriorityQueue::fillRandom(int size) {
    for (int i = 0; i < size; ++i) {
        int value = rand() % 10000;
        int priority = rand() % (size * 5);
        insert(value, priority);
    }
}