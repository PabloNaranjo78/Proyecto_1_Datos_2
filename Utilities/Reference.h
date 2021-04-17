//
// Created by anthony on 16/4/21.
//

#include <iostream>
#include <string>

#ifndef PROYECTO_1_DATOS_2_REFERENCE_H
#define PROYECTO_1_DATOS_2_REFERENCE_H

class Reference {
public:
    Reference * next;
    int lvl_from;
    Reference(int lvl);
};


#endif //PROYECTO_1_DATOS_2_REFERENCE_H
