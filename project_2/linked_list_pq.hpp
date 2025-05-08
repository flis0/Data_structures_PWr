#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>
#include <random>
#include "priority_queue.hpp"

template <typename T, typename P>
class Node {
    public:
        element<T, P> data;
        Node* next;

        Node(element<T, P> elem) : data(elem), next(nullptr) {}
};

template <typename T, typename P>
class LinkedList : public PriorityQueue<T, P> {
    private:
        Node<T, P>* head;
    public:
        LinkedList() {
            head = nullptr;
        }

        LinkedList(int randSize) {
            head = nullptr;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dis_1m(0, 999999);
            std::uniform_int_distribution<int> dis_1k(0, 999);
            for (int i = 0; i < randSize; i++) {
                push({dis_1m(gen), dis_1k(gen)});
            }
        }

        ~LinkedList() {
            Node<T, P>* current = head;
            Node<T, P>* nextNode;
            while (current != nullptr) {
                nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        void push(element<T, P> e) {
            // insert in sorted order based on priority
            Node<T, P>* newNode = new Node<T, P>(e);
            if (head == nullptr || head->data < e) {
                newNode->next = head;
                head = newNode;
            } else {
                Node<T, P>* current = head;
                while (current->next != nullptr && e <= current->next->data) {
                    current = current->next;
                }
                newNode->next = current->next;
                current->next = newNode;
            }
        };

        T pop() {
            if (head == nullptr)
                return 0;
            Node<T, P>* temp = head;
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
            Node<T, P>* iterator = head;
            int count = 0;
            while (iterator != nullptr) {
                count++;
                iterator = iterator->next;
            }
            return count;
        }

        void modify(T value, P new_priority) {
            // finds first node with value, removes it and pushes it back with new priority
            // if not found does nothing
            int index = find(value);
            if (index == -1) return;
            push({erase(index), new_priority});
        };

        void print() {
            Node<T, P>* iterator = head;
            while (iterator != nullptr) {
                std::cout << iterator->data << " ";
                iterator = iterator->next;
            }
            std::cout << std::endl;
        }


        private:
        T erase(int index) {
            if (index == 0) return pop();

            Node<T, P>** iterator = &head;
            for (int i = 0; i < index - 1 && *iterator != nullptr; i++) {
                iterator = &((*iterator)->next);
            }
            if (*iterator != nullptr && (*iterator)->next != nullptr) {
                Node<T, P>* temp = (*iterator)->next;
                (*iterator)->next = temp->next;
                element<T, P> elem = temp->data;
                delete temp;
                return elem;
            }

            return 0; // Not found
        };

        int find(T value) {
            Node<T, P>* iterator = head;
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