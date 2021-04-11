//
// Created by anthony on 11/4/21.
//

#ifndef PROYECTO_1_DATOS_2_NODE_H
#define PROYECTO_1_DATOS_2_NODE_H
#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

template <class T>
class Node {
public:
    T * dir;
    bool init = false;
    string identifier;
    struct Node * next = NULL;
    T data;
;};


#endif //PROYECTO_1_DATOS_2_NODE_H
