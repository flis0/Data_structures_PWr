#include <iostream>
#include "linked_list.hpp"
#include "dynamic_array.hpp"
#include <chrono>
#include <random>

int main() {
    LinkedList<int> list;
    DynamicArray<int> arr;

    long list_time_sum, arr_time_sum;
    std::chrono::high_resolution_clock::time_point start, end;

    // initialalize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis_1k(0, 1000);
    std::uniform_int_distribution<int> dis_100(0, 100);

    list_time_sum = 0;
    arr_time_sum = 0;
    for (int i = 0; i < 1000; i++) {
        start = std::chrono::high_resolution_clock::now();
        list.push_front(i);
        end = std::chrono::high_resolution_clock::now();
        list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        arr.push_front(i);
        end = std::chrono::high_resolution_clock::now();
        arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "List size " << list.size() << "; Array size " << arr.get_size() << std::endl;
    std::cout << "LinkedList push_front time: " << list_time_sum / 1000 << " ns" << std::endl;
    std::cout << "DynamicArray push_front time: " << arr_time_sum / 1000 << " ns" << std::endl;

    list_time_sum = 0;
    arr_time_sum = 0;
    for (int i = 0; i < 1000; i++) {
        start = std::chrono::high_resolution_clock::now();
        list.push_back(i);
        end = std::chrono::high_resolution_clock::now();
        list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        arr.push_back(i);
        end = std::chrono::high_resolution_clock::now();
        arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "List size " << list.size() << "; Array size " << arr.get_size() << std::endl;
    std::cout << "LinkedList push_back time: " << list_time_sum / 1000 << " ns" << std::endl;
    std::cout << "DynamicArray push_back time: " << arr_time_sum / 1000 << " ns" << std::endl;

    list_time_sum = 0;
    arr_time_sum = 0;
    for (int i = 0; i < 1000; i++) {
        start = std::chrono::high_resolution_clock::now();
        list.pop_front();
        end = std::chrono::high_resolution_clock::now();
        list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        arr.pop_front();
        end = std::chrono::high_resolution_clock::now();
        arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "List size " << list.size() << "; Array size " << arr.get_size() << std::endl;
    std::cout << "LinkedList pop_front time: " << list_time_sum / 1000 << " ns" << std::endl;
    std::cout << "DynamicArray pop_front time: " << arr_time_sum / 1000 << " ns" << std::endl;

    list_time_sum = 0;
    arr_time_sum = 0;
    for (int i = 0; i < 1000; i++) {
        start = std::chrono::high_resolution_clock::now();
        list.pop_back();
        end = std::chrono::high_resolution_clock::now();
        list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        arr.pop_back();
        end = std::chrono::high_resolution_clock::now();
        arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "List size " << list.size() << "; Array size " << arr.get_size() << std::endl;
    std::cout << "LinkedList pop_back time: " << list_time_sum / 1000 << " ns" << std::endl;
    std::cout << "DynamicArray pop_back time: " << arr_time_sum / 1000 << " ns" << std::endl;

    list_time_sum = 0;
    arr_time_sum = 0;
    for (int i = 0; i < 1000; i++) {
        start = std::chrono::high_resolution_clock::now();
        list.insert(i, i);
        end = std::chrono::high_resolution_clock::now();
        list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        arr.insert(i, i);
        end = std::chrono::high_resolution_clock::now();
        arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "List size " << list.size() << "; Array size " << arr.get_size() << std::endl;
    std::cout << "LinkedList insert time: " << list_time_sum / 1000 << " ns" << std::endl;
    std::cout << "DynamicArray insert time: " << arr_time_sum / 1000 << " ns" << std::endl;

    list_time_sum = 0;
    arr_time_sum = 0;
    for (int i = 0; i < 500; i++) {
        start = std::chrono::high_resolution_clock::now();
        list.find(dis_1k(gen));
        end = std::chrono::high_resolution_clock::now();
        list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        arr.find(dis_1k(gen));
        end = std::chrono::high_resolution_clock::now();
        arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "List size " << list.size() << "; Array size " << arr.get_size() << std::endl;
    std::cout << "LinkedList find time: " << list_time_sum / 500 << " ns" << std::endl;
    std::cout << "DynamicArray find time: " << arr_time_sum / 500 << " ns" << std::endl;

    list_time_sum = 0;
    arr_time_sum = 0;
    for (int i = 0; i < 950; i++) {
        start = std::chrono::high_resolution_clock::now();
        list.erase(dis_100(gen));
        end = std::chrono::high_resolution_clock::now();
        list_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        arr.erase(dis_100(gen));
        end = std::chrono::high_resolution_clock::now();
        arr_time_sum += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    }
    std::cout << "List size " << list.size() << "; Array size " << arr.get_size() << std::endl;
    std::cout << "LinkedList erase time: " << list_time_sum / 950 << " ns" << std::endl;
    std::cout << "DynamicArray erase time: " << arr_time_sum / 950 << " ns" << std::endl;


    std::cout << "LinkedList: ";
    list.print();
    std::cout << "DynamicArray: ";
    arr.print();
}