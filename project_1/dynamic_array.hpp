#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <iostream>
#include <random>

template <typename T>
class DynamicArray {
    private:
        T* arr;
        int capacity;
        int size;
        void upsize() {
            capacity *= 2;
            T* new_arr = new T[capacity];
            for (int i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }
        public:
        DynamicArray(int initial_capacity = 10) {
            capacity = initial_capacity;
            size = 0;
            arr = new T[capacity];
        }

        DynamicArray(int randSize, int initial_capacity = 10) {
            capacity = initial_capacity;
            size = 0;
            arr = new T[capacity];
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(0, 999999);
            for (int i = 0; i < randSize; i++) {
                push_back(dis(gen));
            }
        }

        ~DynamicArray() {
            delete[] arr;
        }

        void push_front(T value) {
            if (size == capacity) upsize();

            for (int i = size; i > 0; i--) {
                arr[i] = arr[i - 1];
            }
            arr[0] = value;
            size++;
        };

        void push_back(T value) {
            if (size == capacity) upsize();
            arr[size] = value;
            size++;
        };

        T pop_front() {
            if (size == 0) return 0; // Not found
            T value = arr[0];
            for (int i = 0; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
            return value;
        };

        T pop_back() {
            if (size == 0) return 0; // Not found
            T value = arr[size - 1];
            size--;
            return value;
        };

        void insert(int index, T value) {
            if (index < 0 || index > size) return; // Invalid index
            if (size == capacity) upsize();

            for (int i = size; i > index; i--) {
                arr[i] = arr[i - 1];
            }
            arr[index] = value;
            size++;
        };

        T erase(int index) {
            if (index < 0 || index >= size) return 0; // Invalid index
            T value = arr[index];
            for (int i = index; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
            return value;
        };

        int find(T value) {
            for (int i = 0; i < size; i++) {
                if (arr[i] == value) return i;
            }
            return -1; // Not found
        }

        void print() {
            for (int i = 0; i < size; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

        int get_size() {
            return size;
        }
};

#endif