//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_INTERPRETER_H
#define PROYECTO_1_DATOS_2_INTERPRETER_H

#include "LineReader.h"
#include "OutputManager.h"
#include <string>
#include <iostream>
#include "../MemoryMgmt/MemoryManager.h"
#include "../MemoryMgmt/MemoryLayout.h"

using namespace std;

class Interpreter {

public:
    MemoryLayout * memory;
    OutputManager * output;
    LineReader * lineReader;
    string outString;
    string pending;
    Interpreter(string src);
    string interpretLine();

};


#endif //PROYECTO_1_DATOS_2_INTERPRETER_H
