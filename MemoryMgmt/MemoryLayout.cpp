//
// Created by anthony on 8/4/21.
//

#include "MemoryLayout.h"


MemoryLayout::MemoryLayout() {
    this->head = NULL;
    this->lvl = 0;
}

MemoryManager * MemoryLayout::addLevel() {
    this->lvl++;
    MemoryManager * tmp = this->head;
    if (tmp == NULL){
        tmp = new MemoryManager(this->lvl);
        this->head = tmp;
        this->head->lvl = this->lvl;
    }else{
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new MemoryManager(this->lvl);
        tmp->next->lvl = this->lvl;
    }
    cout << "Level added Head: " << this->head << " lvl: " << this->lvl << endl;
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
        while (tmp->next->lvl != lvl){
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

void MemoryLayout::showRam() {
    MemoryManager * tmp = this->head;
    while (tmp != NULL){
        tmp->showRAM();
        tmp = tmp->next;
    }
}