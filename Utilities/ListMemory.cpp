//
// Created by anthony on 1/4/21.
//

#include "ListMemory.h"


template <class T>
void ListMemory<T>::add(string id) {
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
    newNode->dir = (T *) malloc(sizeof(T));
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
                tmp->init = true;
                * tmp->dir =  data;
                tmp->data = tmp->dir;

            }else{
                cout << "Error de tipo de datos" << endl;
            }
        }
    }
}

template <class T>
void ListMemory<T>::showValues() {
    Node<T> * tmp = this->head;
    while(tmp != NULL){
        if (tmp->init){
            T data = * tmp->data;
            cout << "ID: " << tmp->identifier << " Data: " << data << " Dir: " << tmp->dir << endl;
        }else{
            cout << "ID: " << tmp->identifier << " Data: NULL" << " Dir: " << tmp->dir << endl;
        }
    }
}
template <class T>
T * ListMemory<T>::getData(string id) {
    Node<T> * tmp = this->head;
    T data;
    bool found = false;
    while(tmp != NULL){
        if (tmp->identifier == id) {
            data = tmp->data;
            found = true;
            break;
        }
    }
    if (found){
        return data;
    }else{
        cout << "No se encuentra el ID" << endl;
        return NULL;
    }

}