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
    int lvl;
    MemoryLayout();
    MemoryManager * addLevel();
    int checkOnLevel(int level, string ident);
    template<class T>
    T getValue(int level, string ident);
    MemoryManager * getLevel(int lvl);
    void deleteLevel(int lvl);
    void showRam();
};


#endif //PROYECTO_1_DATOS_2_MEMORYLAYOUT_H
