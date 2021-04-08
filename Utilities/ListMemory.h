//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_LISTMEMORY_H
#define PROYECTO_1_DATOS_2_LISTMEMORY_H

#include <iostream>
#include <string>
#include <typeinfo>


using namespace std;


template <class T>
struct Node{
    int dir;
    bool init = false;
    string identifier;
    struct Node * next = NULL;
    T data;
};

template <class T>
class ListMemory {
public:
    Node<T> * head;
    ListMemory<T>(){
        this->head = NULL;
    };
    void add(string id, T data);
    void deleteVar(string id);
    void updateVar(string id, T data);
    bool isIn(string id);
    void showValues();
    T getData(string id);
};


#endif //PROYECTO_1_DATOS_2_LISTMEMORY_H
