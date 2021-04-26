//
// Created by anthony on 22/4/21.
//
#include <iostream>
#include <string>
#include "../ListMemory.h"

#ifndef PROYECTO_1_DATOS_2_STRUCT_H
#define PROYECTO_1_DATOS_2_STRUCT_H

using namespace std;
class Struct {
public:
    Struct * next = NULL;
    string type_ident = "";
    ListMemory<string> * scheme = new ListMemory<string>();
};


#endif //PROYECTO_1_DATOS_2_STRUCT_H
