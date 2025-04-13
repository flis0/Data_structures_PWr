#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <random>

template <typename T>
class Node {
    public:
        T data;
        Node* next;

        Node(T value) {
            data = value;
            next = nullptr;
        }
};

template <typename T>
class LinkedList {
    private:
        Node<T>* head;
    public:
        LinkedList() {
            head = nullptr;
        }

        LinkedList(int randSize) {
            head = nullptr;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis(0, 999999);
            for (int i = 0; i < randSize; i++) {
                push_front(dis(gen));
            }
        }

        ~LinkedList() {
            Node<T>* current = head;
            Node<T>* nextNode;
            while (current != nullptr) {
                nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        void push_front(T value) {
            Node<T>* newNode = new Node<T>(value);
            newNode->next = head;
            head = newNode;
        };

        void push_back(T value) {
            Node<T>* newNode = new Node<T>(value);
            Node<T>** iterator = &head;
            while(*iterator != nullptr) {
                iterator = &((*iterator)->next);
            }
            *iterator = newNode;
        };

        T pop_front() {
            if (head == nullptr)
                return 0; // Not found
            Node<T>* temp = head;
            T value = head->data;
            head = head->next;
            delete temp;
            return value;
        };

        T pop_back() {
            if (head == nullptr) return 0; // Not found
            if (head->next == nullptr) {
                delete head;
                head = nullptr;
                return 0; // Not found
            }
            Node<T>* current = head;
            while (current->next->next != nullptr) {
                current = current->next;
            }
            T value = current->next->data;
            delete current->next;
            current->next = nullptr;
            return value;
        };

        void insert(int index, T value) {
            if (index == 0) {
                push_front(value);
                return;
            }
            Node<T>* newNode = new Node<T>(value);
            Node<T>** iterator = &head;
            for (int i = 0; i < index && *iterator != nullptr; i++) {
                iterator = &((*iterator)->next);
            }
            newNode->next = *iterator;
            *iterator = newNode;
        };

        T erase(int index) {
            if (index == 0) return pop_front();

            Node<T>** iterator = &head;
            for (int i = 0; i < index - 1 && *iterator != nullptr; i++) {
                iterator = &((*iterator)->next);
            }
            if (*iterator != nullptr && (*iterator)->next != nullptr) {
                Node<T>* temp = (*iterator)->next;
                (*iterator)->next = temp->next;
                T value = temp->data;
                delete temp;
                return value;
            }

            return 0; // Not found
        };

        int find(T value) {
            Node<T>* iterator = head;
            int index = 0;
            while (iterator != nullptr) {
                if (iterator->data == value) {
                    return index;
                }
                iterator = iterator->next;
                index++;
            }
            return -1; // Not found
        }

        void print() {
            Node<T>* iterator = head;
            while (iterator != nullptr) {
                std::cout << iterator->data << " ";
                iterator = iterator->next;
            }
            std::cout << std::endl;
        }

        int get_size() {
            Node<T>* iterator = head;
            int count = 0;
            while (iterator != nullptr) {
                count++;
                iterator = iterator->next;
            }
            return count;
        }
};
#endif