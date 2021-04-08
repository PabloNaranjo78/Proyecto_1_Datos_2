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
}

int MemoryLayout::checkOnLevel(int level, string ident) {
    MemoryManager * tmp = this->head;
    int level_found = -1;
    while (tmp->lvl <= level){
        if (tmp->isInMemory(ident)){
            level_found = tmp->lvl;
            break;
        }
        tmp = tmp->next;
    }
    if (level_found == -1){
        cout << "No se encuentra el id en los niveles disponibles" << endl;
    }
    return level_found;
}
template <class T>
T MemoryLayout::getValue(int level, string ident) {
    MemoryManager * tmp = this->head;
    T value[5];
    T concreteVal;
    while(tmp->lvl == level){
        value[0] = tmp->getValue<int>(ident);
        value[1] = tmp->getValue<float>(ident);
        value[2] = tmp->getValue<long>(ident);
        value[3] = tmp->getValue<char>(ident);
        value[4] = tmp->getValue<double>(ident);

        for (int i=0; i<5; i++){
            if (value[i] != NULL){
                concreteVal = value[i];
                break;
            }
        }
        break;
    }
    return concreteVal;
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