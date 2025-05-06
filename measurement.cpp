#include <iostream>
#include <chrono>
#include <fstream>
#include "src/PQDoublyLinkedList.h"

using namespace std;
using namespace std::chrono;

// Pomiar czasu operacji
template<typename Function>
double measure_time(Function func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    duration<double> elapsed = end - start;
    return elapsed.count();
}

int main() {
    const int SIZES[] = {1000, 5000, 10000, 20000, 50000}; // Różne rozmiary testowe
    const int TESTS = 100;
    const int SEEDS[] = {250, 300, 350, 400, 450};

    // Plik do zapisu wyników testów
    ofstream pqFile("results/PriorityQueueResults.txt");

    if (!pqFile.is_open()) {
        cerr << "Nie udało się otworzyć pliku do zapisu wyników." << endl;
        return 1;
    }

    // Testy dla PriorityQueueDLL
    for (int size : SIZES) {
        cout << "\n\n==== Testowanie kolejki priorytetowej dla rozmiaru: " 
             << size << " elementów ====" << endl;
        pqFile << "\n\n==== Testowanie kolejki priorytetowej dla rozmiaru: " 
               << size << " elementów ====" << endl;

        double total_insert = 0.0;
        double total_extractMax = 0.0;
        double total_modifyKey = 0.0;
        int seedCount = 0;

        for (int seed : SEEDS) {
            srand(seed);

            double insert_sum = 0.0;
            double extractMax_sum = 0.0;
            double modifyKey_sum = 0.0;

            PriorityQueueDLL pq;

            for (int t = 0; t < TESTS; t++) {
                pq.fillRandom(size, seed);

                // Pomiar operacji insert (dodanie losowego elementu)
                int value = rand() % 10000;
                int priority = rand() % (size * 5);
                insert_sum += measure_time([&]() {
                    pq.insert(value, priority);
                });

                // Pomiar operacji extractMax (usunięcie maksymalnego elementu)
                if (pq.returnSize() > 0) {
                    extractMax_sum += measure_time([&]() {
                        pq.extractMax();
                    });
                }

                // Pomiar operacji modifyKey (zmiana priorytetu losowego elementu)
                if (pq.returnSize() > 0) {
                    int modify_value = rand() % 10000;
                    int new_priority = rand() % (size * 5);
                    modifyKey_sum += measure_time([&]() {
                        pq.modifyKey(modify_value, new_priority);
                    });
                }
            }

            // Średnie wyniki dla danego seeda
            total_insert += insert_sum / TESTS;
            total_extractMax += extractMax_sum / TESTS;
            total_modifyKey += modifyKey_sum / TESTS;
            seedCount++;
        }

        cout << "\n*** Średnie wyniki dla kolejki priorytetowej dla rozmiaru " 
             << size << " (średnia z " << seedCount << " seedów):\n";
        pqFile << "\n*** Średnie wyniki dla kolejki priorytetowej dla rozmiaru " 
               << size << " (średnia z " << seedCount << " seedów):\n";
        
        cout << "  Wstawienie (insert):       " << (total_insert / seedCount) << " s\n";
        cout << "  Pobranie max (extractMax): " << (total_extractMax / seedCount) << " s\n";
        cout << "  Modyfikacja priorytetu:    " << (total_modifyKey / seedCount) << " s\n";

        pqFile << "  Wstawienie (insert):       " << (total_insert / seedCount) << " s\n";
        pqFile << "  Pobranie max (extractMax): " << (total_extractMax / seedCount) << " s\n";
        pqFile << "  Modyfikacja priorytetu:    " << (total_modifyKey / seedCount) << " s\n";
    }

    // Zamknięcie pliku
    pqFile.close();
    return 0;
}