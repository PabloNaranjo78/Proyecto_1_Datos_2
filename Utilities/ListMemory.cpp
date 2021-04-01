//
// Created by anthony on 1/4/21.
//

#include "ListMemory.h"


template <class T>
void ListMemory<T>::add(string id, T data) {
    Node<T> * newNode = new Node<T>;
    if (this->head == NULL){
        this->head = newNode;
    }else{
        Node<T> * tmp = head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = newNode;
    }
    newNode->data = data;
    newNode->dir = newNode;
    newNode->identifier = id;
}

template <class T>
void ListMemory<T>::deleteVar(string id) {

}