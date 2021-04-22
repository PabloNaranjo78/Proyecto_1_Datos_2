//
// Created by anthony on 17/4/21.
//

#ifndef PROYECTO_1_DATOS_2_STRUCTTYPE_H
#define PROYECTO_1_DATOS_2_STRUCTTYPE_H

#include "../../MemoryMgmt/MemoryManager.h"
#include <iostream>
#include <string>

using namespace std;
class StructType {
public:
    ListMemory<string> * types = new ListMemory<string>();
    void addType(string type);
};


#endif //PROYECTO_1_DATOS_2_STRUCTTYPE_H
