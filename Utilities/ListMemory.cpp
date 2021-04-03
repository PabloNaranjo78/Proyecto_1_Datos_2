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
    if (this->head->identifier == id){
        this->head = this->head->next;
    }else{
        Node<T> * tmp = this->head;
        while (tmp->next->identifier !=  id){
            tmp = tmp->next;
        }
        tmp->next = tmp->next->next;
    }
}

template <class T>
bool ListMemory<T>::isIn(string id) {
    Node<T> * tmp = this->head;
    bool result = false;
    while(tmp != NULL){
        if (tmp->identifier == id) {
            result = true;
            break;
        }
    }
    return result;
}

template <class T>
void ListMemory<T>::updateVar(string id, T data) {
    Node<T> * tmp = this->head;
    while(tmp != NULL){
        if (tmp->identifier == id) {
            if (typeid(data) == typeid(tmp->data)){
                tmp->data = data;
            }else{
                cout << "error datatype" << endl;
            }
        }
    }
}

template <class T>
void ListMemory<T>::showValues() {
    Node<T> * tmp = this->head;
    while(tmp != NULL){
        cout << "ID: " << tmp->identifier << "Data: " << tmp->data << "Dir: " << tmp->dir << endl;
    }
}