//
// Created by anthony on 17/4/21.
//

#include "StructType.h"


void StructType::addType(string type) {
    this->types->add(type, type, false);
}