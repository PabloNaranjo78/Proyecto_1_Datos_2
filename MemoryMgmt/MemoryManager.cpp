//
// Created by anthony on 1/4/21.
//

#include "MemoryManager.h"


MemoryManager::MemoryManager(int level) {
    this->next = NULL;
    this->lvl = level;
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

    return this->list_int->isIn(ident) || this->list_char->isIn(ident) || this->list_double->isIn(ident) || this->list_float->isIn(ident) || this->list_long->isIn(ident);

}

void MemoryManager::showRAM() {

    this->list_int->showValues();
    this->list_char->showValues();
    this->list_double->showValues();
    this->list_float->showValues();
    this->list_long->showValues();

}

string MemoryManager::getType(string ident) {
    if (this->list_int->isIn(ident)){
        cout << "paso 4" << endl;
        return "int";
    }else if(this->list_float->isIn(ident)){
        return "float";
    }else if(this->list_long->isIn(ident)){
        return "long";
    }else if(this->list_char->isIn(ident)){
        return "char";
    }else if(this->list_double->isIn(ident)){
        return "double";
    }
}

int MemoryManager::getLvL() {
    return this->lvl;
}