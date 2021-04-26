//
// Created by anthony on 16/4/21.
//

#include "ReferenceList.h"

ReferenceList::ReferenceList() {
    this->listLenght = 0;
    this->head = NULL;
}

void ReferenceList::add(int lvl_from) {
    this->listLenght++;
    if (this->head == NULL){
        this->head = new Reference(lvl_from);
    }else{
        Reference * tmp = this->head;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new Reference(lvl_from);
    }
}

int ReferenceList::getRefs() {
    return this->listLenght;
}

void ReferenceList::update(int lvlDel) {
    bool check_head = false;
    bool haveToErase = false;
    cout << "Ciclo 1: " << this->listLenght << endl;
    while (!check_head){
        if (this->head->next == NULL){
            check_head = true;
        }
        else if (this->head->lvl_from == lvlDel){
            haveToErase = true;
            this->head = this->head->next;
            cout << "Eliminado lvl" << endl;
        }
        else{
            check_head = true;
            cout << "No se encuentra" << endl;
        }
    }
    cout << "Ciclo 2" << endl;
    Reference * tmp = this->head->next;
    while (tmp != NULL){
        //cout << "Level in: "<< tmp->lvl_from << endl;
        if (tmp->lvl_from == lvlDel){
            cout << "Level in: "<< tmp->lvl_from << endl;
            cout << "found" << endl;
            haveToErase = true;
            tmp = tmp->next;
        }
        if (tmp != NULL){
            tmp = tmp->next;
        }

    }
    if (haveToErase){
        cout << "Level dec" << endl;
        this->listLenght--;
    }
    cout << "Finalizada en referencias: "<< this->listLenght << endl;

}