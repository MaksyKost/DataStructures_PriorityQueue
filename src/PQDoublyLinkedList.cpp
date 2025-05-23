#include "PQDoublyLinkedList.h"
#include <stdexcept>

PriorityQueueDLL::PriorityQueueDLL() : head(nullptr), tail(nullptr) {}

PriorityQueueDLL::~PriorityQueueDLL() {
    clear();
}

// Wstawia nowy węzeł w porządku malejącym wg priorytetu
void PriorityQueueDLL::insert(int e, int p) {
    PQNode* newNode = new PQNode(e, p);
    size++;

    // Jeśli kolejka jest pusta – nowy węzeł staje się head i tail
    if (!head) {
        head = tail = newNode;
        return;
    }
    
    // Jeśli nowy węzeł ma priorytet większy niż aktualny head – dodaj na początek
    if (newNode->priority > head->priority) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        return;
    }
    
    // W przeciwnym razie wyszukujemy odpowiednią pozycję (wstawienie sortowane)
    PQNode* current = head;
    while (current->next != nullptr && current->next->priority >= newNode->priority) {
        current = current->next;
    }
    
    // Wstawienie newNode zaraz za current
    newNode->next = current->next;
    newNode->prev = current;
    
    if (current->next != nullptr) {
        current->next->prev = newNode;
    } else {
        tail = newNode; // nowy węzeł trafia na koniec
    }
    current->next = newNode;
}


// Usuwa i zwraca element o największym priorytecie (czyli head listy)
int PriorityQueueDLL::extractMax() {
    if (!head) {
        throw std::runtime_error("Kolejka jest pusta");
    }
    
    PQNode* temp = head;
    int result = temp->value;
    
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    
    size--;
    delete temp;
    return result;
}



// Zwraca element o najwyższym priorytecie bez usuwania
int PriorityQueueDLL::peek() const {
    if (!head) {
        throw std::runtime_error("Kolejka jest pusta");
    }
    return head->value;
}


// Modyfikacja priorytetu elementu.
// Szukamy pierwszego wystąpienia węzła o podanej wartości, usuwamy go z kolejki,
// aktualizujemy priorytet, a potem wstawiamy ponownie w odpowiednie miejsce.
void PriorityQueueDLL::modifyKey(int e, int p) {
    PQNode* current = head;
    while (current) {
        if (current->value == e)
            break;
        current = current->next;
    }
    // Jeśli nie znaleziono – można zgłosić wyjątek lub po prostu opuścić funkcję.
    if (!current) return;
    
    // Usuwamy znaleziony węzeł z listy
    if (current->prev)
        current->prev->next = current->next;
    else
        head = current->next;
    
    if (current->next)
        current->next->prev = current->prev;
    else
        tail = current->prev;
    
    // Aktualizujemy priorytet
    current->priority = p;
    current->next = current->prev = nullptr;
    
    // Ponownie wstawiamy węzeł, aby lista zachowała porządek
    if (!head) {
        head = tail = current;
        return;
    }
    
    if (current->priority > head->priority) {
        current->next = head;
        head->prev = current;
        head = current;
        return;
    }
    
    PQNode* temp = head;
    while (temp->next != nullptr && temp->next->priority >= current->priority) {
        temp = temp->next;
    }
    
    current->next = temp->next;
    current->prev = temp;
    
    if (temp->next != nullptr) {
        temp->next->prev = current;
    } else {
        tail = current;
    }
    
    temp->next = current;
}

// Zwraca rozmiar kolejki, przeglądając listę
int PriorityQueueDLL::returnSize() const { return size; }

// Usuwa wszystkie elementy z kolejki
void PriorityQueueDLL::clear() {
    PQNode* current = head;
    while (current) {
        PQNode* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}

// Funkcja pomocnicza do wyświetlania zawartości kolejki
void PriorityQueueDLL::print() const {
    PQNode* current = head;
    while (current) {
        std::cout << "(" << current->value << ", " << current->priority << ") ";
        current = current->next;
    }
    std::cout << std::endl;
}

// Generowanie losowych danych
void PriorityQueueDLL::fillRandom(int size) {
    for (int i = 0; i < size; ++i) {
        int value = rand() % 10000;    // Losowa wartość (0-9999)
        int priority = rand() % (size * 5); // Priorytet (większy zakres dla lepszego rozkładu)
        insert(value, priority);  // Wstawienie elementu zgodnie z priorytetem
    }
}