#include <iostream>
#include "src/PQDoublyLinkedList.h"


int main()
{
    PriorityQueueDLL pq;

    // Wstawienie kilku elementów do kolejki
    pq.insert(10, 5);
    pq.insert(20, 10);
    pq.insert(30, 3);
    pq.insert(40, 15);
    
    std::cout << "Rozmiar kolejki po wstawieniu elementów:\t" << pq.size() << std::endl;


    // Wyświetlenie kolejki
    std::cout << "Kolejka po wstawieniu elementów:\n";
    pq.print();
    
    // Podejrzenie maksymalnego elementu
    std::cout << "Element o najwyższym priorytecie: ";
    auto maxElement = pq.peek();
    std::cout << "(" << maxElement.first << ", " << maxElement.second << ")\n";
    
    // Usunięcie elementu o najwyższym priorytecie
    std::cout << "Usuwanie elementu o najwyższym priorytecie...\n";
    pq.extractMax();
    pq.print();
    
    std::cout << "Rozmiar kolejki po wstawieniu elementów:\t" << pq.size() << std::endl;



    // Modyfikacja priorytetu jednego z elementów
    std::cout << "Modyfikacja priorytetu elementu 20 na 18...\n";
    pq.modifyKey(20, 18);
    pq.print();

    // Wypełnienie kolejki losowymi danymi
    std::cout << "Dodanie losowych danych...\n";
    pq.fillRandom(5, 42);
    pq.print();

    std::cout << "Rozmiar kolejki po wstawieniu elementów:\t" << pq.size() << std::endl;
    


    return 0;
}