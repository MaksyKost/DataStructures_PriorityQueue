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
    const int SIZES[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
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
        double total_peek = 0.0;
        double total_modifyKeyIncrease = 0.0;
        double total_modifyKeyDecrease = 0.0;
        double total_size = 0.0;
        int seedCount = 0;

        for (int seed : SEEDS) {
            srand(seed);

            double insert_sum = 0.0;
            double extractMax_sum = 0.0;
            double peek_sum = 0.0;
            double modifyKeyIncrease_sum = 0.0;
            double modifyKeyDecrease_sum = 0.0;
            double size_sum = 0.0;

            PriorityQueueDLL pq;

            for (int t = 0; t < TESTS; t++) {
                pq.fillRandom(size);

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

                // Pomiar operacji peek (podejrzenie maksymalnego elementu)
                if (pq.returnSize() > 0) {
                    peek_sum += measure_time([&]() {
                        pq.peek();
                    });
                }

                // Pomiar operacji modifyKeyIncrease (zwiększenie priorytetu)
                if (pq.returnSize() > 0) {
                    int modify_value = rand() % 10000;
                    int new_priority_high = rand() % (size * 10); // Wyższy priorytet
                    modifyKeyIncrease_sum += measure_time([&]() {
                        pq.modifyKey(modify_value, new_priority_high);
                    });
                }

                // Pomiar operacji modifyKeyDecrease (zmniejszenie priorytetu)
                if (pq.returnSize() > 0) {
                    int modify_value = rand() % 10000;
                    int new_priority_low = rand() % (size / 2); // Niższy priorytet
                    modifyKeyDecrease_sum += measure_time([&]() {
                        pq.modifyKey(modify_value, new_priority_low);
                    });
                }

                // Pomiar operacji size (zwrócenie rozmiaru)
                size_sum += measure_time([&]() {
                    pq.returnSize();
                });
                pq.clear();
            }

            // Średnie wyniki dla danego seeda
            total_insert += insert_sum / TESTS;
            total_extractMax += extractMax_sum / TESTS;
            total_peek += peek_sum / TESTS;
            total_modifyKeyIncrease += modifyKeyIncrease_sum / TESTS;
            total_modifyKeyDecrease += modifyKeyDecrease_sum / TESTS;
            total_size += size_sum / TESTS;
            seedCount++;
        }

        cout << "\n*** Średnie wyniki dla kolejki priorytetowej dla rozmiaru " 
             << size << " (średnia z " << seedCount << " seedów):\n";
        pqFile << "\n*** Średnie wyniki dla kolejki priorytetowej dla rozmiaru " 
               << size << " (średnia z " << seedCount << " seedów):\n";
        
        cout << "  Wstawienie (insert):          " << (total_insert / seedCount) << " s\n";
        cout << "  Pobranie max (extractMax):    " << (total_extractMax / seedCount) << " s\n";
        cout << "  Podejrzenie max (peek):       " << (total_peek / seedCount) << " s\n";
        cout << "  Zwiększenie priorytetu:       " << (total_modifyKeyIncrease / seedCount) << " s\n";
        cout << "  Zmniejszenie priorytetu:      " << (total_modifyKeyDecrease / seedCount) << " s\n";
        cout << "  Zwrot rozmiaru (size):        " << (total_size / seedCount) << " s\n";

        pqFile << "  Wstawienie (insert):          " << (total_insert / seedCount) << " s\n";
        pqFile << "  Pobranie max (extractMax):    " << (total_extractMax / seedCount) << " s\n";
        pqFile << "  Podejrzenie max (peek):       " << (total_peek / seedCount) << " s\n";
        pqFile << "  Zwiększenie priorytetu:       " << (total_modifyKeyIncrease / seedCount) << " s\n";
        pqFile << "  Zmniejszenie priorytetu:      " << (total_modifyKeyDecrease / seedCount) << " s\n";
        pqFile << "  Zwrot rozmiaru (size):        " << (total_size / seedCount) << " s\n";
    }

    // Zamknięcie pliku
    pqFile.close();
    return 0;
}