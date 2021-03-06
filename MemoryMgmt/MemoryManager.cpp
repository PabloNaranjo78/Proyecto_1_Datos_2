//
// Created by anthony on 1/4/21.
//

#include "MemoryManager.h"
#include "../Logger/Logger.h"


MemoryManager::MemoryManager(int level) {
    this->next = NULL;
    this->lvl = level;
    cout << "Level at: " << this->lvl << endl;
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

bool MemoryManager::isInit(string ident) {

    return this->list_int->isInit(ident) || this->list_char->isInit(ident) || this->list_double->isInit(ident) || this->list_float->isInit(ident) || this->list_long->isInit(ident);

}

void MemoryManager::showRAM(JsonManager *jsonManager, Logger *log,string printing) {

    this->list_int->showValues(jsonManager, log, printing);
    this->list_char->showValues(jsonManager,log, printing);
    this->list_double->showValues(jsonManager,log, printing);
    this->list_float->showValues(jsonManager,log, printing);
    this->list_long->showValues(jsonManager,log, printing);

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

void MemoryManager::add_reference(string id, int lvl_from) {
    if (this->list_int->isIn(id)){
        cout << "referencia agregada" << endl;
        this->list_int->count_reference(id, lvl_from);
    }else if(this->list_float->isIn(id)){
        this->list_float->count_reference(id, lvl_from);
    }else if(this->list_long->isIn(id)){
        this->list_long->count_reference(id, lvl_from);
    }else if(this->list_char->isIn(id)){
        this->list_char->count_reference(id, lvl_from);
    }else if(this->list_double->isIn(id)){
        this->list_double->count_reference(id, lvl_from);
    }
}

void MemoryManager::update_refs(int lvl_from) {

    this->list_int->update_refences(lvl_from);
    this->list_char->update_refences(lvl_from);
    this->list_double->update_refences(lvl_from);
    this->list_float->update_refences(lvl_from);
    this->list_long->update_refences(lvl_from);
}

bool MemoryManager::isRef(string id) {
    if (this->list_int->isIn(id)){
        return this->list_int->isRef(id);
    }else if(this->list_float->isIn(id)){
        return this->list_float->isRef(id);
    }else if(this->list_long->isIn(id)){
        return this->list_long->isRef(id);
    }else if(this->list_char->isIn(id)){
        return this->list_char->isRef(id);
    }else if(this->list_double->isIn(id)){
        return this->list_double->isRef(id);
    }
}
