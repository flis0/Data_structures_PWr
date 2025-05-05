#ifndef ELEMENT_STRUCT
#define ELEMENT_STRUCT
template <typename T, typename P>
struct element {
    T value;
    P priority;

    operator T() const {
        return value;
    }

    bool operator<(const element& other) const {
        return priority < other.priority;
    }

    bool operator<=(const element& other) const {
        return priority <= other.priority;
    }

    bool operator==(const element& other) const {
        return value == other.value;
    }
};
#endif

#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <iostream>
#include <random>

template <typename T, typename P>
class DynamicArray_PriorityQueue {
    private:
        element<T, P>* arr;
        int capacity;
        int size;
        void upsize() {
            capacity *= 2;
            element<T, P>* new_arr = new element<T, P>[capacity];
            for (int i = 0; i < size; i++) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }
        public:
        DynamicArray_PriorityQueue(int initial_capacity = 10) {
            capacity = initial_capacity;
            size = 0;
            arr = new element<T, P>[capacity];
        }

        DynamicArray_PriorityQueue(int randSize, int initial_capacity = 10) {
            capacity = initial_capacity;
            size = 0;
            arr = new element<T, P>[capacity];
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis_1m(0, 999999);
            std::uniform_int_distribution<int> dis_1k(0, 999);
            for (int i = 0; i < randSize; i++) {
                push({dis_1m(gen), dis_1k(gen)});
            }
        }

        ~DynamicArray_PriorityQueue() {
            delete[] arr;
        }

        void push(element<T, P> value) {
            if (size == capacity) upsize();

            int i = size - 1;
            while (i >= 0 && arr[i] < value) {
                arr[i + 1] = arr[i];
                i--;
            }
            arr[i + 1] = value;

            size++;
        };

        T pop() {
            if (size == 0) return 0;
            T value = arr[0];
            for (int i = 0; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
            return value;
        };

        T peek() {
            if (size == 0) return 0;
            return arr[0];
        };

        int get_size() {
            return size;
        }

        void modify(T value, P new_priority) {
            // finds first array element with value, removes it and pushes it back with new priority
            // if not found does nothing
            int index = find(value);
            if (index == -1) return;
            push({erase(index), new_priority});
        }

        void print() {
            for (int i = 0; i < size; i++) {
                std::cout << arr[i] << " ";
            }
            std::cout << std::endl;
        }


    private:
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
};

#endif