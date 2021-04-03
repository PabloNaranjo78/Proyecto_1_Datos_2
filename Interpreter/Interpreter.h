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

using namespace std;

class Interpreter {

public:
    LineReader * lineReader = new LineReader();
    OutputManager * output = new OutputManager();
    MemoryManager * memomanager = new MemoryManager();
    string outString;
    Interpreter();
    void interpretLine(string src);

};


#endif //PROYECTO_1_DATOS_2_INTERPRETER_H
