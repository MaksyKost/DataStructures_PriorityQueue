#include <iostream>
#include <chrono>
#include <fstream>
#include "src/PQDoublyLinkedList.h"
#include "src/PQHeap.h"

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

    // Testy dla PriorityQueueDLL (lista dwukierunkowa)
    for (int size : SIZES) {
        cout << "\n\n==== Testowanie kolejki priorytetowej dla rozmiaru: " 
             << size << " elementów ====" << endl;
        pqFile << "\n\n==== Testowanie kolejki priorytetowej dla rozmiaru: " 
               << size << " elementów ====" << endl;

        double total_insert_DLL = 0.0;
        double total_extractMax_DLL = 0.0;
        double total_peek_DLL = 0.0;
        double total_modifyKeyIncrease_DLL = 0.0;
        double total_modifyKeyDecrease_DLL = 0.0;
        double total_size_DLL = 0.0;

        double total_insert_heap = 0.0;
        double total_extractMax_heap = 0.0;
        double total_peek_heap = 0.0;
        double total_modifyKeyIncrease_heap = 0.0;
        double total_modifyKeyDecrease_heap = 0.0;
        double total_size_heap = 0.0;

        int seedCount = 0;

        for (int seed : SEEDS) {
            srand(seed);

            PriorityQueueDLL pqDLL;
            HeapPriorityQueue pqHeap;

            double insert_sum_DLL = 0.0, insert_sum_heap = 0.0;
            double extractMax_sum_DLL = 0.0, extractMax_sum_heap = 0.0;
            double peek_sum_DLL = 0.0, peek_sum_heap = 0.0;
            double modifyKeyIncrease_sum_DLL = 0.0, modifyKeyIncrease_sum_heap = 0.0;
            double modifyKeyDecrease_sum_DLL = 0.0, modifyKeyDecrease_sum_heap = 0.0;
            double size_sum_DLL = 0.0, size_sum_heap = 0.0;

            for (int t = 0; t < TESTS; t++) {
                pqDLL.fillRandom(size);
                pqHeap.fillRandom(size);

                // 📌 TESTY INSERT
                int value = rand() % 10000;
                int priority = rand() % (size * 5);
                insert_sum_DLL += measure_time([&]() { pqDLL.insert(value, priority); });
                insert_sum_heap += measure_time([&]() { pqHeap.insert(value, priority); });

                // 📌 TESTY EXTRACT-MAX
                if (pqDLL.returnSize() > 0) {
                    extractMax_sum_DLL += measure_time([&]() { pqDLL.extractMax(); });
                }
                if (pqHeap.returnSize() > 0) {
                    extractMax_sum_heap += measure_time([&]() { pqHeap.extractMax(); });
                }

                // 📌 TESTY PEEK
                if (pqDLL.returnSize() > 0) {
                    peek_sum_DLL += measure_time([&]() { pqDLL.peek(); });
                }
                if (pqHeap.returnSize() > 0) {
                    peek_sum_heap += measure_time([&]() { pqHeap.peek(); });
                }

                // 📌 TESTY MODIFY-KEY (INCREASE)
                int new_priority_high = rand() % (size * 10);
                modifyKeyIncrease_sum_DLL += measure_time([&]() { pqDLL.modifyKey(value, new_priority_high); });
                modifyKeyIncrease_sum_heap += measure_time([&]() { pqHeap.modifyKey(value, new_priority_high); });

                // 📌 TESTY MODIFY-KEY (DECREASE)
                int new_priority_low = rand() % (size / 2);
                modifyKeyDecrease_sum_DLL += measure_time([&]() { pqDLL.modifyKey(value, new_priority_low); });
                modifyKeyDecrease_sum_heap += measure_time([&]() { pqHeap.modifyKey(value, new_priority_low); });

                // 📌 TESTY SIZE
                size_sum_DLL += measure_time([&]() { pqDLL.returnSize(); });
                size_sum_heap += measure_time([&]() { pqHeap.returnSize(); });

                pqDLL.clear();
                pqHeap.clear();
            }

            // Średnie wyniki dla danego seeda
            total_insert_DLL += insert_sum_DLL / TESTS;
            total_insert_heap += insert_sum_heap / TESTS;

            total_extractMax_DLL += extractMax_sum_DLL / TESTS;
            total_extractMax_heap += extractMax_sum_heap / TESTS;

            total_peek_DLL += peek_sum_DLL / TESTS;
            total_peek_heap += peek_sum_heap / TESTS;

            total_modifyKeyIncrease_DLL += modifyKeyIncrease_sum_DLL / TESTS;
            total_modifyKeyIncrease_heap += modifyKeyIncrease_sum_heap / TESTS;

            total_modifyKeyDecrease_DLL += modifyKeyDecrease_sum_DLL / TESTS;
            total_modifyKeyDecrease_heap += modifyKeyDecrease_sum_heap / TESTS;

            total_size_DLL += size_sum_DLL / TESTS;
            total_size_heap += size_sum_heap / TESTS;

            seedCount++;
        }

        pqFile << "\n*** Wyniki dla listy dwukierunkowej: ***\n";
        pqFile << "Insert: " << (total_insert_DLL / seedCount) << " s\n";
        pqFile << "ExtractMax: " << (total_extractMax_DLL / seedCount) << " s\n";

        pqFile << "\n*** Wyniki dla kopca binarnego: ***\n";
        pqFile << "Insert: " << (total_insert_heap / seedCount) << " s\n";
        pqFile << "ExtractMax: " << (total_extractMax_heap / seedCount) << " s\n";

    }

    pqFile.close();
    return 0;
}