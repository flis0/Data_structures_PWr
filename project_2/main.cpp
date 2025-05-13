#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "priority_queue.hpp"
#include "linked_list_pq.hpp"
#include "linked_list_2_pq.hpp"
#include "dynamic_array_pq.hpp"


#define AVG_N 100
#define ARR_INIT_CAP 10

template <size_t N>
inline void zeros(long (&arr)[N]) { for (size_t i = 0; i < N; ++i) arr[i] = 0; }

void structure_tests();

int main() {
    // structure_tests(); return 0;

    long time_sums[] = {0, 0, 0};
    PriorityQueue<int, int>* structures[3];
    std::chrono::high_resolution_clock::time_point start, end;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_1m(0, 999999);
    std::uniform_int_distribution<int> dis_1k(0, 999);

    std::ofstream file;
    file.open("output.csv", std::ios::out | std::ios::trunc);
    file << "N;Operation;Case;LinkedList [ns];DynamicArray [ns];LinkedList2 [ns]" << std::endl;

    for (int size = 10000; size <= 100000; size += 10000) {
        structures[0] = new LinkedList<int, int>(size);
        structures[1] = new DynamicArray<int, int>(size, ARR_INIT_CAP);
        structures[2] = new LinkedList2<int, int>(size);
        zeros(time_sums);

        // ########## AVG ##########

        for (int i = 0; i < sizeof(structures) / sizeof(structures[0]); i++) {
            for (int j = 0; j < AVG_N; j++) {
                start = std::chrono::high_resolution_clock::now();
                structures[i]->push({dis_1m(gen), dis_1k(gen)});
                end = std::chrono::high_resolution_clock::now();
                time_sums[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                structures[i]->pop();
            }
        }
        file << size << ";push;avg;" << time_sums[0] / AVG_N << ';' << time_sums[1] / AVG_N << ';' << time_sums[2] / AVG_N << std::endl;
        zeros(time_sums);

        for (int i = 0; i < sizeof(structures) / sizeof(structures[0]); i++) {
            for (int j = 0; j < AVG_N; j++) {
                start = std::chrono::high_resolution_clock::now();
                structures[i]->pop();
                end = std::chrono::high_resolution_clock::now();
                time_sums[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
                structures[i]->push({dis_1m(gen), dis_1k(gen)});
            }
        }
        file << size << ";pop;avg;" << time_sums[0] / AVG_N << ';' << time_sums[1] / AVG_N << ';' << time_sums[2] / AVG_N << std::endl;
        zeros(time_sums);

        for (int i = 0; i < sizeof(structures) / sizeof(structures[0]); i++) {
            for (int j = 0; j < AVG_N; j++) {
                start = std::chrono::high_resolution_clock::now();
                structures[i]->peek();
                end = std::chrono::high_resolution_clock::now();
                time_sums[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }
        file << size << ";peek;avg;" << time_sums[0] / AVG_N << ';' << time_sums[1] / AVG_N << ';' << time_sums[2] / AVG_N << std::endl;
        zeros(time_sums);

        for (int i = 0; i < sizeof(structures) / sizeof(structures[0]); i++) {
            for (int j = 0; j < AVG_N; j++) {
                start = std::chrono::high_resolution_clock::now();
                structures[i]->size();
                end = std::chrono::high_resolution_clock::now();
                time_sums[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }
        file << size << ";size;avg;" << time_sums[0] / AVG_N << ';' << time_sums[1] / AVG_N << ';' << time_sums[2] / AVG_N << std::endl;
        zeros(time_sums);

        for (int i = 0; i < sizeof(structures) / sizeof(structures[0]); i++) {
            for (int j = 0; j < AVG_N; j++) {
                start = std::chrono::high_resolution_clock::now();
                structures[i]->modify(dis_1m(gen), dis_1k(gen));
                end = std::chrono::high_resolution_clock::now();
                time_sums[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }
        file << size << ";modify;avg;" << time_sums[0] / AVG_N << ';' << time_sums[1] / AVG_N << ';' << time_sums[2] / AVG_N << std::endl;
        zeros(time_sums);

        // ########## BEST ##########

        for (auto i : {0,2}) { // LinkedList and LinkedList2
            for (int j = 0; j < AVG_N; j++) {
                start = std::chrono::high_resolution_clock::now();
                structures[i]->push({dis_1m(gen), 999});
                end = std::chrono::high_resolution_clock::now();
                time_sums[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }
        for (int j = 0; j < AVG_N; j++) { // DynamicArray
            start = std::chrono::high_resolution_clock::now();
            structures[1]->push({dis_1m(gen), 0});
            end = std::chrono::high_resolution_clock::now();
            time_sums[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        file << size << ";push;best;" << time_sums[0] / AVG_N << ';' << time_sums[1] / AVG_N << ';' << time_sums[2] / AVG_N << std::endl;
        zeros(time_sums);

        for (auto i : {0,2}) { // LinkedList and LinkedList2
            for (int j = 0; j < AVG_N; j++) {
                start = std::chrono::high_resolution_clock::now();
                structures[i]->modify(dis_1k(gen), 999, structures[i]->find_p(999));
                end = std::chrono::high_resolution_clock::now();
                time_sums[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }
        for (int j = 0; j < AVG_N; j++) { // DynamicArray
            start = std::chrono::high_resolution_clock::now();
            structures[1]->modify(dis_1k(gen), 0, structures[1]->find_p(0));
            end = std::chrono::high_resolution_clock::now();
            time_sums[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        file << size << ";modify;best;" << time_sums[0] / AVG_N << ';' << time_sums[1] / AVG_N << ';' << time_sums[2] / AVG_N << std::endl;
        zeros(time_sums);

        // ########## WORST ##########

        for (auto i : {0,2}) { // LinkedList and LinkedList2
            for (int j = 0; j < AVG_N; j++) {
                start = std::chrono::high_resolution_clock::now();
                structures[i]->push({dis_1m(gen), 0});
                end = std::chrono::high_resolution_clock::now();
                time_sums[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }
        for (int j = 0; j < AVG_N; j++) { // DynamicArray
            start = std::chrono::high_resolution_clock::now();
            structures[1]->push({dis_1m(gen), 999});
            end = std::chrono::high_resolution_clock::now();
            time_sums[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        file << size << ";push;worst;" << time_sums[0] / AVG_N << ';' << time_sums[1] / AVG_N << ';' << time_sums[2] / AVG_N << std::endl;
        zeros(time_sums);

        for (auto i : {0,2}) { // LinkedList and LinkedList2
            for (int j = 0; j < AVG_N; j++) {
                start = std::chrono::high_resolution_clock::now();
                structures[i]->modify(dis_1k(gen), 0, structures[i]->find_p(0));
                end = std::chrono::high_resolution_clock::now();
                time_sums[i] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            }
        }
        for (int j = 0; j < AVG_N; j++) { // DynamicArray
            start = std::chrono::high_resolution_clock::now();
            structures[1]->modify(dis_1k(gen), 999, structures[1]->find_p(999));
            end = std::chrono::high_resolution_clock::now();
            time_sums[1] += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        file << size << ";modify;worst;" << time_sums[0] / AVG_N << ';' << time_sums[1] / AVG_N << ';' << time_sums[2] / AVG_N << std::endl;
        zeros(time_sums);

        std::cout << size << " done" << std::endl;
    }
}

void structure_tests() {
    PriorityQueue<int, int> * list = new LinkedList<int, int>();
    std::cout << std::endl << "Linked List Priority Queue" << std::endl;
    std::cout << "-------------------------" << std::endl;
    list->push({6, 1});
    list->push({5, 2});
    list->push({4, 3});
    list->push({3, 3});
    list->push({2, 4});
    list->push({1, 5});

    list->print();

    std::cout << "Size: " << list->size() << std::endl;
    std::cout << "Peek: " << list->peek() << std::endl;
    std::cout << "Pop: " << list->pop() << std::endl;
    list->print();
    std::cout << "Size: " << list->size() << std::endl;
    std::cout << "Peek: " << list->peek() << std::endl;
    list->modify(4, 2);
    std::cout << "Modify 4 to 2" << std::endl;
    list->print();

    std::cout << std::endl << """Dynamic Array Priority Queue" << std::endl;
    std::cout << "-------------------------" << std::endl;


    PriorityQueue<int, int> * arr = new DynamicArray<int, int>();
    arr->push({6, 1});
    arr->push({5, 2});
    arr->push({4, 3});
    arr->push({3, 3});
    arr->push({2, 4});
    arr->push({1, 5});

    arr->print();

    std::cout << "Size: " << arr->size() << std::endl;
    std::cout << "Peek: " << arr->peek() << std::endl;
    std::cout << "Pop: " << arr->pop() << std::endl;
    arr->print();
    std::cout << "Size: " << arr->size() << std::endl;
    std::cout << "Peek: " << arr->peek() << std::endl;
    arr->modify(4, 2);
    std::cout << "Modify 4 to 2" << std::endl;
    arr->print();

    PriorityQueue<int, int> * list2 = new LinkedList2<int, int>();
    std::cout << std::endl << "Linked List2 Priority Queue" << std::endl;
    std::cout << "-------------------------" << std::endl;
    list2->push({6, 1});
    list2->push({5, 2});
    list2->push({4, 3});
    list2->push({3, 3});
    list2->push({2, 4});
    list2->push({1, 5});

    list2->print();

    std::cout << "Size: " << list2->size() << std::endl;
    std::cout << "Peek: " << list2->peek() << std::endl;
    std::cout << "Pop: " << list2->pop() << std::endl;
    list2->print();
    std::cout << "Size: " << list2->size() << std::endl;
    std::cout << "Peek: " << list2->peek() << std::endl;
    list2->modify(4, 2);
    std::cout << "Modify 4 to 2" << std::endl;
    list2->print();
}