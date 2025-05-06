#ifndef PRIORITYQUEUE_DLL_H
#define PRIORITYQUEUE_DLL_H

#include <iostream>
#include <utility> // dla std::pair

// Definicja struktury węzła kolejki priorytetowej
struct PQNode {
    int value;      // Przechowywana wartość (element kolejki)
    int priority;   // Klucz (priorytet)
    PQNode* next;
    PQNode* prev;
    
    PQNode(int val, int prio) : value(val), priority(prio), next(nullptr), prev(nullptr) {}
};

class PriorityQueueDLL {
private:
    PQNode* head; // wskaźnik na początek listy (element o największym priorytecie)
    PQNode* tail; // wskaźnik na koniec listy
    
public:
    PriorityQueueDLL();
    ~PriorityQueueDLL();
    
    // Operacje kolejki priorytetowej:
    // Wstawienie elementu (wartość, priorytet) z zachowaniem porządku malejącego wg priorytetu.
    void insert(int e, int p);
    
    // Usunięcie (i zwrócenie) elementu o najwyższym priorytecie [jeśli kolejka pusta – zgłoszenie wyjątku]
    std::pair<int, int> extractMax();
    
    // Podejrzenie elementu o najwyższym priorytecie (bez usuwania)
    std::pair<int, int> peek() const;
    
    // Modyfikacja priorytetu danego elementu.
    // W tej implementacji szukamy węzła o podanej wartości, usuwamy go, aktualizujemy klucz,
    // a następnie wstawiamy ponownie, zachowując właściwy porządek.
    void modifyKey(int e, int p);
    
    // Zwraca liczbę elementów w kolejce
    int size() const;
    
    // Czyści kolejkę (usuwa wszystkie elementy)
    void clear();
    
    // Pomocnicza funkcja do wyświetlania zawartości kolejki (dla celów debugowania)
    void print() const;

    void fillRandom(int size, int seed);
};

#endif // PRIORITYQUEUE_DLL_H