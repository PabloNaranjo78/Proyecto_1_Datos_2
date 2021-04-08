//
// Created by anthony on 1/4/21.
//

#include "MemoryManager.h"


MemoryManager::MemoryManager(int level) {
    this->next = NULL;
    this->lvl = level;
}


template<class T>
void MemoryManager::addVar(string id, T data) {

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
void MemoryManager::updateVar(string ident, T data) {

    if (this->list_int->isIn(ident)){
        this->list_int->updateVar(ident, data);
    }else if(this->list_float->isIn(ident)){
        this->list_float->updateVar(ident, data);
    }else if(this->list_long->isIn(ident)){
        this->list_long->updateVar(ident, data);
    }else if(this->list_char->isIn(ident)){
        this->list_char->updateVar(ident, data);
    }else if(this->list_double->isIn(ident)){
        this->list_double->updateVar(ident, data);
    }

}

void MemoryManager::deleteVar(string ident) {

    if (this->list_int->isIn(ident)) {
        this->list_int->deleteVar(ident);
    } else if (this->list_float->isIn(ident)) {
        this->list_float->deleteVar(ident);
    } else if (this->list_long->isIn(ident)) {
        this->list_long->deleteVar(ident);
    } else if (this->list_char->isIn(ident)) {
        this->list_char->deleteVar(ident);
    } else if (this->list_double->isIn(ident)) {
        this->list_double->deleteVar(ident);
    }
}

bool MemoryManager::isInMemory(string ident) {

    return this->list_int->isIn(ident) || this->list_char->isIn(ident) || this->list_double->isIn(ident) ||
    this->list_float->isIn(ident) || this->list_long->isIn(ident);

}

void MemoryManager::showRAM() {

    this->list_int->showValues();
    this->list_char->showValues();
    this->list_double->showValues();
    this->list_float->showValues();
    this->list_long->showValues();

}
template<class T>
T MemoryManager::getValue(string ident) {

    if (this->list_int->isIn(ident)){
        this->list_int->getData(ident);
    }else if(this->list_float->isIn(ident)){
        this->list_float->getData(ident);
    }else if(this->list_long->isIn(ident)){
        this->list_long->getData(ident);
    }else if(this->list_char->isIn(ident)){
        this->list_char->getData(ident);
    }else if(this->list_double->isIn(ident)){
        this->list_double->getData(ident);
    }
}