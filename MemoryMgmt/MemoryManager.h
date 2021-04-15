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
    int getLvL();
    void deleteVar(string ident);
    void showRAM();
    bool isInMemory(string ident);
    string getType(string ident);
    void collectGarbage();
    template<class T>
    void addVar(string id, T data){

        if(typeid(int) == typeid(data)){
            this->list_int->add(id, data);
        }else if(typeid(float) == typeid(data)){
            this->list_float->add(id, data);
        }else if(typeid(long) == typeid(data)){
            this->list_long->add(id, data);
        }else if(typeid(char) == typeid(data)){
            this->list_char->add(id, data);
        }else if(typeid(double) == typeid(data)){
            this->list_double->add(id, data);
        }

    }

    template<class T>
    void updateVar(string ident, T * data){
        if (this->list_int->isIn(ident)){
            this->list_int->updateVar(ident, (int* )data);
        }else if(this->list_float->isIn(ident)){
            this->list_float->updateVar(ident, (float* )data);
        }else if(this->list_long->isIn(ident)){
            this->list_long->updateVar(ident, (long* )data);
        }else if(this->list_char->isIn(ident)){
            this->list_char->updateVar(ident, (char* )data);
        }else if(this->list_double->isIn(ident)){
            this->list_double->updateVar(ident, (double * )data);
        }
    }

    template<class T>
    T getValue(string ident){
        if (this->list_int->isIn(ident)){
            return this->list_int->getData(ident);
        }else if(this->list_float->isIn(ident)){
            return this->list_float->getData(ident);
        }else if(this->list_long->isIn(ident)){
            return this->list_long->getData(ident);
        }else if(this->list_char->isIn(ident)){
            return this->list_char->getData(ident);
        }else if(this->list_double->isIn(ident)){
            return this->list_double->getData(ident);
        }

    }

};


#endif //PROYECTO_1_DATOS_2_MEMORYMANAGER_H
