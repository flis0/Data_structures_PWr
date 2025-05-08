#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include "linked_list_pq.hpp"
#include "dynamic_array_pq.hpp"
#include "priority_queue.hpp"


#define AVG_N 100
#define ARR_INIT_CAP 10

int main() {
    // structure_tests();

    long list_time_sum, arr_time_sum;
    int temp;
    std::chrono::high_resolution_clock::time_point start, end;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_1m(0, 999999);
    std::uniform_int_distribution<int> dis_1k(0, 999);

    std::ofstream file;
    file.open("output.csv", std::ios::out | std::ios::trunc);
    file << "N;Operation;LinkedList_PriorityQueue [ns];DynamicArray_PriorityQueue [ns]" << std::endl;

    for (int size = 10000; size <= 100000; size += 10000) {
        PriorityQueue<int, int> * list = new LinkedList<int, int>(size);
        PriorityQueue<int, int> * arr = new DynamicArray<int, int>(size, ARR_INIT_CAP);

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            start = std::chrono::high_resolution_clock::now();
            list->push({dis_1m(gen), dis_1k(gen)});
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            list->pop();

            start = std::chrono::high_resolution_clock::now();
            arr->push({dis_1m(gen), dis_1k(gen)});
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            arr->pop();
        }
        file << size << ";push;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            start = std::chrono::high_resolution_clock::now();
            list->pop();
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            list->push({dis_1m(gen), dis_1k(gen)});

            start = std::chrono::high_resolution_clock::now();
            arr->pop();
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            arr->push({dis_1m(gen), dis_1k(gen)});
        }
        file << size << ";pop;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            start = std::chrono::high_resolution_clock::now();
            list->peek();
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            arr->peek();
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        file << size << ";peek;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            start = std::chrono::high_resolution_clock::now();
            list->size();
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            arr->size();
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        file << size << ";size;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            start = std::chrono::high_resolution_clock::now();
            list->modify(dis_1m(gen), dis_1k(gen));
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            start = std::chrono::high_resolution_clock::now();
            arr->modify(dis_1m(gen), dis_1k(gen));
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        }
        file << size << ";modify;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;

        delete list;
        delete arr;

        std::cout << "size " << size << " done" << std::endl;
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
}

