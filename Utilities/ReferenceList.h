//
// Created by anthony on 16/4/21.
//

#include <iostream>
#include <string>
#include "Reference.h"

#ifndef PROYECTO_1_DATOS_2_REFERENCELIST_H
#define PROYECTO_1_DATOS_2_REFERENCELIST_H

using namespace std;

class ReferenceList {
public:
    Reference * head;
    int listLenght;
    ReferenceList();
    void add(int lvl_from);
    void update(int lvlDel);
    int getRefs();
};


#endif //PROYECTO_1_DATOS_2_REFERENCELIST_H
