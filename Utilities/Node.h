//
// Created by anthony on 11/4/21.
//

#ifndef PROYECTO_1_DATOS_2_NODE_H
#define PROYECTO_1_DATOS_2_NODE_H
#include <iostream>
#include <string>
#include <typeinfo>
#include "ReferenceList.h"

using namespace std;

/**
 * @brief Nodo de la lista de memoria
 * @tparam T tipo de dato generico que puede ser int, float, long, char o double
 */
template <class T>
class Node {
public:
    T * dir;
    bool init = false;
    string identifier;
    struct Node * next = NULL;
    ReferenceList * refs = new ReferenceList();
    T data;
    T * data_ref;
    bool ref;
};


#endif //PROYECTO_1_DATOS_2_NODE_H
