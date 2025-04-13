#include <iostream>
#include "linked_list.hpp"
#include "dynamic_array.hpp"
#include <chrono>
#include <random>
#include <fstream>

#define AVG_N 100
#define ARR_INIT_CAP 10

int main() {
    // LinkedList<int> list;
    // DynamicArray<int> arr;

    long list_time_sum, arr_time_sum;
    int temp;
    std::chrono::high_resolution_clock::time_point start, end;

    // initialalize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_1k(0, 999);
    std::uniform_int_distribution<int> dis_1m(0, 999999);

    std::ofstream file;
    file.open("output.csv", std::ios::out | std::ios::trunc);
    file << "N;Operation;LinkedList [ns];DynamicArray [ns]" << std::endl;

    for (int size = 10000; size <= 100000; size += 10000) {
        // for (int i = size - list.get_size(); i > 0; i--) { list.push_back(dis_1m(gen)); }
        // for (int i = size - arr.get_size(); i > 0; i--) { arr.push_back(dis_1m(gen)); }

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            LinkedList<int> * list = new LinkedList<int>(size);
            start = std::chrono::high_resolution_clock::now();
            list->push_back(dis_1m(gen));
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete list;

            DynamicArray<int> * arr = new DynamicArray<int>(size, ARR_INIT_CAP);
            start = std::chrono::high_resolution_clock::now();
            arr->push_back(dis_1m(gen));
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete arr;
        }
        file << size << ";push_back;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;
        // std::cout << "push_back done" << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            LinkedList<int> * list = new LinkedList<int>(size);
            start = std::chrono::high_resolution_clock::now();
            list->push_front(dis_1m(gen));
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete list;

            DynamicArray<int> * arr = new DynamicArray<int>(size, ARR_INIT_CAP);
            start = std::chrono::high_resolution_clock::now();
            arr->push_front(dis_1m(gen));
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete arr;
        }
        file << size << ";push_front;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;
        // std::cout << "push_front done" << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            LinkedList<int> * list = new LinkedList<int>(size);
            start = std::chrono::high_resolution_clock::now();
            list->pop_back();
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete list;

            DynamicArray<int> * arr = new DynamicArray<int>(size, ARR_INIT_CAP);
            start = std::chrono::high_resolution_clock::now();
            arr->pop_back();
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete arr;
        }
        file << size << ";pop_back;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;
        // std::cout << "pop_back done" << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            LinkedList<int> * list = new LinkedList<int>(size);
            start = std::chrono::high_resolution_clock::now();
            list->pop_front();
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete list;

            DynamicArray<int> * arr = new DynamicArray<int>(size, ARR_INIT_CAP);
            start = std::chrono::high_resolution_clock::now();
            arr->pop_front();
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete arr;
        }
        file << size << ";pop_front;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;
        // std::cout << "pop_front done" << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            LinkedList<int> * list = new LinkedList<int>(size);
            start = std::chrono::high_resolution_clock::now();
            list->insert(dis_1k(gen)*(size/1000), dis_1m(gen));
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete list;

            DynamicArray<int> * arr = new DynamicArray<int>(size, ARR_INIT_CAP);
            start = std::chrono::high_resolution_clock::now();
            arr->insert(dis_1k(gen)*(size/1000), dis_1m(gen));
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete arr;
        }
        file << size << ";insert;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;
        // std::cout << "insert done" << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            LinkedList<int> * list = new LinkedList<int>(size);
            start = std::chrono::high_resolution_clock::now();
            list->erase(dis_1k(gen)*(size/1000));
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete list;

            DynamicArray<int> * arr = new DynamicArray<int>(size, ARR_INIT_CAP);
            start = std::chrono::high_resolution_clock::now();
            arr->erase(dis_1k(gen)*(size/1000));
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete arr;
        }
        file << size << ";erase;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;
        // std::cout << "erase done" << std::endl;

        list_time_sum = 0;
        arr_time_sum = 0;
        for (int i = 0; i < AVG_N; i++) {
            LinkedList<int> * list = new LinkedList<int>(size);
            start = std::chrono::high_resolution_clock::now();
            list->find(dis_1m(gen));
            end = std::chrono::high_resolution_clock::now();
            list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete list;

            DynamicArray<int> * arr = new DynamicArray<int>(size, ARR_INIT_CAP);
            start = std::chrono::high_resolution_clock::now();
            arr->find(dis_1m(gen));
            end = std::chrono::high_resolution_clock::now();
            arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
            delete arr;
        }
        file << size << ";find;" << list_time_sum / AVG_N << ';' << arr_time_sum / AVG_N << std::endl;
        // std::cout << "find done" << std::endl;

        std::cout << "size " << size << " done" << std::endl;
    }
}