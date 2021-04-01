//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_MEMORYMANAGER_H
#define PROYECTO_1_DATOS_2_MEMORYMANAGER_H

#include <string>
#include <iostream>

using namespace std;


class MemoryManager {
    struct Node{
        int dir;
        string identifier;
        struct Node * next;
    };
    Node * head;
    int var_count;
    MemoryManager();
    template<class T>
    void addVar(string id, T data);
    void deleteVar(string ident);
    template<class T>
    void updateVar(string ident, T data);
    void showRAM();

};


#endif //PROYECTO_1_DATOS_2_MEMORYMANAGER_H
