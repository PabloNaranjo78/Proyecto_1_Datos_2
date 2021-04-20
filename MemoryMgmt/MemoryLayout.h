//
// Created by anthony on 8/4/21.
//

#ifndef PROYECTO_1_DATOS_2_MEMORYLAYOUT_H
#define PROYECTO_1_DATOS_2_MEMORYLAYOUT_H
#include "MemoryManager.h"
#include <string>
#include <iostream>
#include <typeinfo>

using namespace std;

class MemoryLayout {

public:
    MemoryManager * head;
    int lvl = 0;
    MemoryLayout();
    MemoryManager * addLevel();
    void count_reference(string id, int lvl_from);
    void delete_refs(int lvl_del);
    int checkOnLevel(int level, string ident);
    template<class T>
    T getValue(int level, string ident){
        MemoryManager * tmp = this->head;
        T value[5];
        T concreteVal;
        while(tmp->lvl <= level && tmp != NULL){
            value[0] = tmp->getValue<int>(ident);
            value[1] = tmp->getValue<float>(ident);
            value[2] = tmp->getValue<long>(ident);
            value[3] = tmp->getValue<char>(ident);
            value[4] = tmp->getValue<double>(ident);

            for (int i=0; i<5; i++){
                if (value[i] != NULL){
                    concreteVal = * value[i];
                    break;
                }
            }

            break;
        }
        return concreteVal;
    }
    MemoryManager * getLevel(int lvl);
    void deleteLevel(int lvl);
    bool isInit(string id, int lvl);
    string getType(string id);
    void showRam();

};


#endif //PROYECTO_1_DATOS_2_MEMORYLAYOUT_H
