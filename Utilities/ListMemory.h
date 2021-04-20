//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_LISTMEMORY_H
#define PROYECTO_1_DATOS_2_LISTMEMORY_H

#include <iostream>
#include <string>
#include <typeinfo>
#include "Node.h"
#include "SpecialTypes/ReferenceType.h"

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

    bool isInit(string ident){
        Node<T> * tmp = this->head;
        while (tmp != NULL) {
            if (tmp->identifier == ident) {
                break;
            }
            tmp = tmp->next;
        }
        return tmp->init;
    }

    void add(string id, T data, bool ref) {
        cout << "Agregando data" << endl;
        Node<T> * newNode = new Node<T>;
        if (this->head == NULL){
            this->head = newNode;
        }else{
            Node<T> * tmp = head;
            while(tmp->next != NULL){
                cout << "buscando..." << endl;
                tmp = tmp->next;
            }
            tmp->next = newNode;
        }

        if (!ref){
            newNode->dir = (T*)malloc(sizeof(data));
            newNode->data = data;
            * newNode->dir = newNode->data;
        }else{
            cout << "Here 2" << endl;
            newNode->dir = (T*)malloc(sizeof(data));
            newNode->data_ref = NULL;
        }

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
            free(tmp->next);
        }
    }

    bool isIn(string id) {
        Node<T> * tmp = this->head;
        bool result = false;
        while(tmp != NULL){
            cout << "Ident: " << tmp->identifier << endl;
            if (tmp->identifier == id) {
                result = true;
                break;
            }
            cout << tmp << "actual" << endl;
            tmp = tmp->next;
        }
        cout << "nivel: "<< result << endl;
        return result;
    }

    void updateVar(string id, T * data) {
        Node<T> * tmp = this->head;
        while(tmp != NULL){
            if (tmp->identifier == id) {
                if (typeid(* data) == typeid(tmp->data)){
                    if (!isRef(id)){
                        tmp->init = true;
                        tmp->data = * data;
                        * tmp->dir = tmp->data;
                    }else{
                        tmp->init = true;
                        tmp->data_ref = data;
                    }

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
            if (tmp->init && !tmp->ref){
                T data = * tmp->dir;
                cout << "ID: " << tmp->identifier << " Data: " << data << " Dir: " << tmp->dir << " Referencias: " << tmp->refs->getRefs() << endl;
            }else if (tmp->init && !tmp->ref){
                cout << "ID: " << tmp->identifier << " Data: " << tmp->data_ref << " Dir: " << tmp->dir << " Referencias: " << tmp->refs->getRefs() << endl;
            }
            else{
                cout << "ID: " << tmp->identifier << " Data: NULL" << " Dir: " << tmp->dir << " Referencias: " << tmp->refs->getRefs() << endl;
            }
            tmp = tmp->next;
        }
    }
    T getData(string id) {
        Node<T> * tmp = this->head;
        T data;
        bool found = false;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                data = tmp->data;
                found = true;
                break;
            }
            tmp = tmp->next;
        }
        if (found && tmp->init) {
            return data;
        } else {
            throw "Error";
        }
    }

    T * getAddress(string id){
        cout << "getting address" << endl;
        Node<T> * tmp = this->head;
        T * data_dir;
        bool found = false;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                data_dir = tmp->dir;
                found = true;
                break;
            }
            tmp = tmp->next;
        }
        if (found) {
            return data_dir;
        } else {
            throw "Error";
        }
    }

    T * getAddPointed(string id){
        Node<T> * tmp = this->head;
        T * data_ref;
        bool found = false;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                data_ref = tmp->data_ref;
                found = true;
                break;
            }
            tmp = tmp->next;
        }
        if (found && tmp->init) {
            return data_ref;
        } else {
            throw "Error";
        }
    }

    void count_reference(string id, int lvl_from){
        Node<T> * tmp = this->head;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                tmp->refs->add(lvl_from);
                break;
            }
            tmp = tmp->next;
        }
    }

    void update_refences(int lvl_del){
        Node<T> * tmp = this->head;
        while (tmp != NULL) {
            tmp->refs->update(lvl_del);
            tmp = tmp->next;
        }
    }

    bool isRef(string id){
        Node<T> * tmp = this->head;
        bool isRef = false;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                isRef = tmp->ref;
                break;
            }
            tmp = tmp->next;
        }
        return isRef;
    }


};


#endif //PROYECTO_1_DATOS_2_LISTMEMORY_H
