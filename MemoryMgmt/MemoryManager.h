//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_MEMORYMANAGER_H
#define PROYECTO_1_DATOS_2_MEMORYMANAGER_H

#include <string>
#include <iostream>
#include <typeinfo>
#include "../Utilities/ListMemory.h"
#include "../JsonManeger/JsonManager.h"
//#include "../Utilities/SpecialTypes/Struct.h"
#include "../Utilities/SpecialTypes/StructType.h"


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
    bool isRef(string id);
    void deleteVar(string ident);
    void showRAM(JsonManager *jsonManager);
    bool isInMemory(string ident);
    string getType(string ident);
    void add_reference(string id, int lvl_from);
    void update_refs(int lvl_from);
    bool isInit(string ident);

    template<class T>
    void addVar(string id, T data, bool isRef){

        if(typeid(int) == typeid(data)){
            this->list_int->add(id, data, isRef);
        }else if(typeid(float) == typeid(data)){
            this->list_float->add(id, data, isRef);
        }else if(typeid(long) == typeid(data)){
            this->list_long->add(id, data, isRef);
        }else if(typeid(char) == typeid(data)){
            this->list_char->add(id, data, isRef);
        }else if(typeid(double) == typeid(data)){
            this->list_double->add(id, data, isRef);
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

    template<class T>
    T* getAddress(string ident){

        if (this->list_int->isIn(ident)){
            return (T *)this->list_int->getAddress(ident);

        }else if(this->list_float->isIn(ident)){
            return (T *)this->list_float->getAddress(ident);

        }else if(this->list_long->isIn(ident)){
            return (T *)this->list_long->getAddress(ident);

        }else if(this->list_char->isIn(ident)){
            return (T *)this->list_char->getAddress(ident);

        }else if(this->list_double->isIn(ident)){
            return (T *)this->list_double->getAddress(ident);
        }
    }

    template<class T>
    T* getAddPoint(string ident){

        if (this->list_int->isIn(ident)){
            return (T *)this->list_int->getAddPointed(ident);

        }else if(this->list_float->isIn(ident)){
            return (T *)this->list_float->getAddPointed(ident);

        }else if(this->list_long->isIn(ident)){
            return (T *)this->list_long->getAddPointed(ident);

        }else if(this->list_char->isIn(ident)){
            return (T *)this->list_char->getAddPointed(ident);

        }else if(this->list_double->isIn(ident)){
            return (T *)this->list_double->getAddPointed(ident);
        }
    }
};


#endif //PROYECTO_1_DATOS_2_MEMORYMANAGER_H
