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
    MemoryLayout * memory = new MemoryLayout();
    LineReader * lineReader = new LineReader(memory);
    OutputManager * output = new OutputManager();
    string outString;
    Interpreter();
    void interpretLine(string src);

};


#endif //PROYECTO_1_DATOS_2_INTERPRETER_H
