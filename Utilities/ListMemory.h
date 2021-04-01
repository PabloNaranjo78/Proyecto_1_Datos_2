//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_LISTMEMORY_H
#define PROYECTO_1_DATOS_2_LISTMEMORY_H

#include <iostream>
#include <string>

using namespace std;


template <class T>
struct Node{
    int dir;
    string identifier;
    struct Node * next = NULL;
    T data;
};

template <class T>
class ListMemory {
    Node<T> * head;
    ListMemory<T>(){
        head = NULL;
    };
    void add(string id, T data);
    void deleteVar(string id);
    void updateVar(string id, T data);
    bool isIn(string id);
    void showValues();
};


#endif //PROYECTO_1_DATOS_2_LISTMEMORY_H
