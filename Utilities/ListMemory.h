//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_LISTMEMORY_H
#define PROYECTO_1_DATOS_2_LISTMEMORY_H

#include <iostream>
#include <string>
#include <typeinfo>
#include "Node.h"

using namespace std;


//Convertir el Node a clase y agregarle el getAdress

template <class T>
class ListMemory {
public:
    /*
    ListMemory<T>(){
        this->head = NULL;
    };
    void add(string id);
    void deleteVar(string id);
    void updateVar(string id, T data);
    bool isIn(string id);
    void showValues();
    T * getData(string id);
     */
    Node<T> * head;

    ListMemory<T>(){
        this->head = NULL;
    }

    void add(string id, T data) {
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
        newNode->dir = (T*)&data;
        newNode->identifier = id;
    }

    void deleteVar(string id) {
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

    bool isIn(string id) {
        Node<T> * tmp = this->head;
        bool result = false;
        while(tmp != NULL){
            if (tmp->identifier == id) {
                result = true;
                break;
            }
            tmp = tmp->next;
        }
        cout << result << endl;
        return result;
    }

    void updateVar(string id, T * data) {
        Node<T> * tmp = this->head;
        while(tmp != NULL){
            if (tmp->identifier == id) {
                if (typeid(* data) == typeid(tmp->data)){
                    tmp->init = true;
                    tmp->data = * data;

                }else{
                    cout << "Error de tipo de datos" << endl;
                }
            }
            tmp = tmp->next;
        }
    }

    void showValues() {
        Node<T> * tmp = this->head;
        while(tmp != NULL){
            if (tmp->init){
                T data = tmp->data;
                cout << "ID: " << tmp->identifier << " Data: " << data << " Dir: " << tmp->dir << endl;
            }else{
                cout << "ID: " << tmp->identifier << " Data: NULL" << " Dir: " << tmp->dir << endl;
            }
            tmp = tmp->next;
        }
    }
    T * getData(string id) {
        Node<T> *tmp = this->head;
        T * data_dir;
        bool found = false;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                data_dir = tmp->dir;
                found = true;
                break;
            }
        }
        if (found) {
            return (T*)data_dir;
        } else {
            cout << "No se encuentra el ID" << endl;
            return NULL;
        }
    }

};


#endif //PROYECTO_1_DATOS_2_LISTMEMORY_H
