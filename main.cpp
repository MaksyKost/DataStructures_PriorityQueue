#include <iostream>
#include <chrono>
#include <string>
#include <windows.h>
#include <thread>
#include "src/PQDoublyLinkedList.h"
#include "src/PQHeap.h"

int seed = 123;

void setTextColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void fancyMenuTitle() {
    const std::string lines[] = {
        " __  __ _____ _   _ _   _ ",
        "|  \\/  | ____| \\ | | | | |",
        "| |\\/| |  _| |  \\| | | | |",
        "| |  | | |___| |\\  | \\_/ |",
        "|_|  |_|_____|_| \\_|\\___/ "
    };

    int colors[] = { 0x0C, 0x0A, 0x0E, 0x09, 0x0B, 0x0D, 0x08 };

    std::srand(static_cast<unsigned int>(std::time(0)));
    system("cls");
    for (const auto& line : lines) {
        for (size_t i = 0; i < line.size(); ++i) {
            setTextColor(colors[std::rand() % 7]);
            std::cout << line[i] << std::flush;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::cout << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    for (int i = 0; i < 5; ++i) {
        setTextColor(colors[i % 7]);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "\r";
        for (const auto& line : lines) {
            std::cout << line << '\n';
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "\r";
    }
    setTextColor(0x07);
}


void menuHeap(HeapPriorityQueue& heap) {
    int choice, e, p, index;
    do {
        std::cout << "\n|------------------------- Heap PQ MENU ------------------------|\n";
        std::cout << "| 1. Dodanie elementu e o priorytecie p                           |\n";
        std::cout << "| 2. Usunięcie i zwrócenie elementu o największym priorytecie     |\n";
        std::cout << "| 3. Zwrócenie elementu o największym priorytecie                 |\n";
        std::cout << "| 4. Zmiana priorytetu elementu e na p                            |\n";
        std::cout << "| 5. Zwrócenie rozmiaru                                           |\n";
        std::cout << "| 6. Wypełnianie losowymi elementami                              |\n";
        std::cout << "| 7. Wyświetlanie kolejki                                         |\n";
        std::cout << "| 8. Czyszczenie kolejki                                          |\n";
        std::cout << "| 0. Wyjdź                                                        |\n";
        std::cout << "|-----------------------------------------------------------------|\n";
        std::cout << "Twój wybór: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Podaj wartość: "; std::cin >> e;
                std::cout << "Podaj priorytet: "; std::cin >> p;
                heap.insert(e, p);
                std::cout << "Dodano (" << e << ", " << p << ").\n";
                break;
            case 2: {
                Element max = heap.extractMax();
                std::cout << "Usunięto: (" << max.e << ", " << max.p << ")\n";
                break;
            }
            case 3: {
                Element top = heap.peek();
                std::cout << "Najwyższy priorytet: (" << top.e << ", " << top.p << ")\n";
                break;
            }
            case 4:
                std::cout << "Podaj wartość elementu do zmiany: "; std::cin >> e;
                std::cout << "Podaj priorytet: "; std::cin >> p;
                heap.modifyKey(e, p);
                std::cout << "Zmieniono priorytet elementu " << e << " na " << p << ".\n";
                break;
            case 5:
                std::cout << "Rozmiar kolejki: " << heap.returnSize() << "\n";
                break;
            case 6:
                std::cout << "Podaj rozmiar: "; std::cin >> e;
                heap.fillRandom(e, seed);
                break;
            case 7:
                heap.print();
                break;
            case 8:
                heap.clear();
                break;
        }

    } while (choice != 0);
}

void menuDDL(PriorityQueueDLL& ddl) {
    int choice, e, p, amount;
    do {
        std::cout << "\n|------------------------- Doubly Linked List PQ MENU ------------------------|\n";
        std::cout << "| 1. Dodanie elementu e o priorytecie p                                         |\n";
        std::cout << "| 2. Usunięcie i zwrócenie elementu o największym priorytecie                   |\n";
        std::cout << "| 3. Zwrócenie elementu o największym priorytecie                               |\n";
        std::cout << "| 4. Zmiana priorytetu elementu e na p                                          |\n";
        std::cout << "| 5. Zwrócenie rozmiaru                                                         |\n";
        std::cout << "| 6. Wypełnianie losowymi elementami                                            |\n";
        std::cout << "| 7. Wyświetlanie kolejki                                                       |\n";
        std::cout << "| 8. Czyszczenie kolejki                                                        |\n";
        std::cout << "| 0. Wyjdź                                                                      |\n";
        std::cout << "|-------------------------------------------------------------------------------|\n";
        std::cout << "Twój wybór: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Podaj wartość: "; std::cin >> e;
                std::cout << "Podaj priorytet: "; std::cin >> p;
                ddl.insert(e, p);
                std::cout << "Dodano (" << e << ", " << p << ").\n";
                break;
            case 2:
                std::cout << "Usunięto: " << ddl.extractMax() << "\n";
                break;
            case 3:
                std::cout << "Najwyższy priorytet ma: " << ddl.peek() << "\n";
                break;
            case 4:
                std::cout << "Podaj wartość elementu do zmiany: "; std::cin >> e;
                std::cout << "Nowy priorytet: "; std::cin >> p;
                ddl.modifyKey(e, p);
                std::cout << "Zmieniono priorytet elementu " << e << " na " << p << ".\n";
                break;
            case 5:
                std::cout << "Rozmiar kolejki: " << ddl.returnSize() << "\n";
                break;
            case 6:
                std::cout << "Podaj rozmiar: "; std::cin >> amount;
                ddl.fillRandom(amount);
                break;
            case 7:
                ddl.print();
                break;
            case 8:
                ddl.clear();
                break;
        }

    } while (choice != 0);
}


int main()
{
    system("chcp 65001 > nul");
    int choice;
    do {
        fancyMenuTitle();
        std::cout << "----------------  Wybierz opcję ---------------\n";
        std::cout << "| 1. Implementacja KP na kopcu                |\n";
        std::cout << "| 2. Implementacja KP liście dwukierunkowej   |\n";
        std::cout << "| 0. Wyjdź                                    |\n";
        std::cout << "Twój wybór: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                HeapPriorityQueue heapPQ;
                menuHeap(heapPQ);
                break;
            }
            case 2: {
                PriorityQueueDLL dllPQ;
                menuDDL(dllPQ);
                break;
            }
        }

    } while (choice != 0);

    return 0;
}