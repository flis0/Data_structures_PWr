#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <iostream>
#include <random>

template <typename T, typename P>
class DynamicArray : public PriorityQueue<T, P> {
    private:
        element<T, P>* arr;
        int capacity;
        size_t arr_size;
        void up_arr_size() {
            capacity *= 2;
            element<T, P>* new_arr = new element<T, P>[capacity];
            for (int i = 0; i < arr_size; i++) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }

        public:
        DynamicArray(int initial_capacity = 10) {
            capacity = initial_capacity;
            arr_size = 0;
            arr = new element<T, P>[capacity];
        }

        DynamicArray(int randarr_Size, int initial_capacity = 10) {
            capacity = initial_capacity;
            arr_size = 0;
            arr = new element<T, P>[capacity];
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis_1m(0, 999999);
            std::uniform_int_distribution<int> dis_1k(0, 999);
            for (int i = 0; i < randarr_Size; i++) {
                push({dis_1m(gen), dis_1k(gen)});
            }
        }

        ~DynamicArray() {
            delete[] arr;
        }

        void push(element<T, P> value) {
            if (arr_size == capacity) up_arr_size();

            int i = arr_size - 1;
            while (i >= 0 && arr[i] < value) {
                arr[i + 1] = arr[i];
                i--;
            }
            arr[i + 1] = value;

            arr_size++;
        };

        T pop() {
            if (arr_size == 0) return 0;
            T value = arr[0];
            for (int i = 0; i < arr_size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            arr_size--;
            return value;
        };

        T peek() {
            if (arr_size == 0) return 0;
            return arr[0];
        };

        size_t size() {
            return arr_size;
        }

        void modify(T value, P new_priority, size_t index = -1) {
            // finds first array element with value, removes it and pushes it back with new priority
            // if not found does nothing
            if (index == -1)
                index = find(value);
            if (index == -1) return;
            push({erase(index), new_priority});
        }

        void print() {
            for (int i = 0; i < arr_size; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }

        size_t find_p(P priority) {
            for (int i = 0; i < arr_size; i++) {
                if (arr[i].priority == priority) {
                    return i;
                }
            }
            return -1; // Not found
        }


    private:
        T erase(int index) {
            if (index < 0 || index >= arr_size) return 0; // Invalid index
            T value = arr[index];
            for (int i = index; i < arr_size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            arr_size--;
            return value;
        };

        int find(T value) {
            for (int i = 0; i < arr_size; i++) {
                if (arr[i] == value) return i;
            }
            return -1; // Not found
        }
};

#endif