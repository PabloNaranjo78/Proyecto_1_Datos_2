//
// Created by anthony on 8/4/21.
//

#include "MemoryLayout.h"


MemoryLayout::MemoryLayout() {
    this->head = NULL;
    this->lvl = 0;
    this->structManager = new StructType();
}

MemoryManager * MemoryLayout::addLevel() {
    this->lvl ++;
    MemoryManager * tmp = this->head;
    MemoryManager * to_return = NULL;
    if (tmp == NULL){
        tmp = new MemoryManager(this->lvl);
        this->head = tmp;
        this->head->lvl = this->lvl;
        to_return = tmp;
    }else{
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new MemoryManager(this->lvl);
        tmp->next->lvl = this->lvl;
        to_return = tmp->next;
    }
    cout << "Level added lvl: " << this->lvl << endl;
    return to_return;
}

int MemoryLayout::checkOnLevel(int level, string ident) {
    MemoryManager * tmp = this->head;
    int level_found = -1;

    while (tmp != NULL){
        if (tmp->isInMemory(ident) && tmp->lvl<=level){
            level_found = tmp->lvl;
            break;
        }
        tmp = tmp->next;
    }

    cout << "Level Found: " << level_found << endl;

    if (level_found == -1){
        cout << "No se encuentra el id en los niveles disponibles" << endl;
    }

    return level_found;
}


void MemoryLayout::deleteLevel(int lvl) {
    MemoryManager * tmp = this->head;
    if (lvl == 1){
        this->head = this->head->next;
    }else{
        while (tmp->next != NULL && tmp->next->lvl != lvl){
            tmp = tmp->next;
        }
        tmp->next = tmp->next->next;
    }
    this->lvl--;
}

MemoryManager * MemoryLayout::getLevel(int lvl) {
    MemoryManager * tmp = this->head;
    while (tmp != NULL){
        if (tmp->lvl == lvl){
            break;
        }
        tmp = tmp->next;
        cout << "Ciclo inf" << endl;
    }
    return tmp;
}

void MemoryLayout::count_reference(string id, int lvl_from) {
    MemoryManager * tmp = this->head;
    while (tmp != NULL){
        if (tmp->isInMemory(id)){
            tmp->add_reference(id, lvl_from);
            break;
        }
        tmp = tmp->next;
    }
}

void MemoryLayout::delete_refs(int lvl_del) {
    MemoryManager * tmp = this->head;
    while (tmp != NULL){
        tmp->update_refs(lvl_del);
        tmp = tmp->next;
    }
}

string MemoryLayout::showRam() {
    MemoryManager * tmp = this->head;
    while (tmp != NULL){
        tmp->showRAM(jsonManager);
        tmp = tmp->next;
    }
    return jsonManager->convertDataToString();
}

bool MemoryLayout::isInit(string id, int lvl) {
    MemoryManager * tmp = this->head;
    while (tmp != NULL){
        if (tmp->getLvL() == lvl){
            break;
        }
        tmp = tmp->next;
    }
    return tmp->isInit(id);
}

string MemoryLayout::getType(string id) {
    MemoryManager * tmp = this->head;
    while (tmp != NULL){
        if (tmp->getLvL() == lvl){
            break;
        }
        tmp = tmp->next;
    }
    return tmp->getType(id);
}