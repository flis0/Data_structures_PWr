#ifndef LINKED_LIST2_HPP
#define LINKED_LIST2_HPP

#include <iostream>
#include <random>
#include "priority_queue.hpp"

template <typename T, typename P>
class Node2 {
    public:
        element<T, P> data;
        Node2 *next, *prev;

        Node2(element<T, P> elem) : data(elem), next(nullptr) {}
};

template <typename T, typename P>
class LinkedList2 : public PriorityQueue<T, P> {
    private:
        Node2<T, P> *head, *tail;
    public:
        LinkedList2() {
            head = nullptr;
            tail = nullptr;
        }

        LinkedList2(int randSize) {
            head = nullptr;
            tail = nullptr;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis_1m(0, 999999);
            std::uniform_int_distribution<int> dis_1k(0, 999);
            for (int i = 0; i < randSize; i++) {
                push({dis_1m(gen), dis_1k(gen)});
            }
        }

        ~LinkedList2() {
            Node2<T, P>* current = head;
            Node2<T, P>* nextNode;
            while (current != nullptr) {
                nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        void push(element<T, P> e) {
            // insert in sorted order based on priority
            Node2<T, P>* newNode = new Node2<T, P>(e);
            if (head == nullptr || head->data < e) {
                newNode->next = head;
                head = newNode;
                tail = newNode;
            } else {
                Node2<T, P>* current = head;
                while (current->next != nullptr && e <= current->next->data) {
                    current = current->next;
                }
                newNode->next = current->next;
                newNode->prev = current;
                current->next = newNode;
                if (newNode->next != nullptr) {
                    newNode->next->prev = newNode;
                } else {
                    tail = newNode;
                }
            }
        };

        T pop() {
            if (head == nullptr)
                return 0;
            Node2<T, P>* temp = head;
            T value = head->data;
            head = head->next;
            delete temp;
            return value;
        };

        T peek() {
            if (head == nullptr)
                return 0;
            return head->data;
        };

        size_t size() {
            Node2<T, P>* iterator = head;
            int count = 0;
            while (iterator != nullptr) {
                count++;
                iterator = iterator->next;
            }
            return count;
        }

        void modify(T value, P new_priority, size_t index=-1) {
            // finds first node with value, removes it and pushes it back with new priority
            // if not found does nothing
            if (index == -1)
                index = find(value);
            if (index == -1) return;
            push({erase(index), new_priority});
        };

        void print() {
            Node2<T, P>* iterator = head;
            while (iterator != nullptr) {
                std::cout << iterator->data << " ";
                iterator = iterator->next;
            }
            std::cout << std::endl;
        }

        size_t find_p(P priority) {
            Node2<T, P>* iterator = head;
            int index = 0;
            while (iterator != nullptr) {
                if (iterator->data.priority == priority) {
                    return index;
                }
                iterator = iterator->next;
                index++;
            }
            return -1; // Not found
        }


        private:
        T erase(int index) {
            if (index == 0) return pop();

            Node2<T, P>** iterator = &head;
            for (int i = 0; i < index - 1 && *iterator != nullptr; i++) {
                iterator = &((*iterator)->next);
            }
            if (*iterator != nullptr && (*iterator)->next != nullptr) {
                Node2<T, P>* temp = (*iterator)->next;
                (*iterator)->next = temp->next;
                element<T, P> elem = temp->data;
                delete temp;
                return elem;
            }

            return 0; // Not found
        };

        int find(T value) {
            Node2<T, P>* iterator = head;
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
    };

#endif