//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_MEMORYMANAGER_H
#define PROYECTO_1_DATOS_2_MEMORYMANAGER_H

#include <string>
#include <iostream>
#include <typeinfo>
#include "../Utilities/ListMemory.h"

using namespace std;


class MemoryManager {

    ListMemory<int> * list_int = new ListMemory<int>();
    ListMemory<float> * list_float = new ListMemory<float>();
    ListMemory<char> * list_char = new ListMemory<char>();
    ListMemory<long> * list_long = new ListMemory<long>();
    ListMemory<double> * list_double = new ListMemory<double>();

public:

    MemoryManager * next;
    int lvl;
    MemoryManager(int level);
    template<class T>
    void addVar(string id, T data);
    void deleteVar(string ident);
    template<class T>
    void updateVar(string ident, T data);
    void showRAM();
    bool isInMemory(string ident);
    template<class T>
    T getValue(string ident);
    void collectGarbage();

};


#endif //PROYECTO_1_DATOS_2_MEMORYMANAGER_H
