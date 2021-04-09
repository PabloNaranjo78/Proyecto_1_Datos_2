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
    OutputManager * output = new OutputManager();
    LineReader * lineReader = new LineReader(memory, output);
    string outString;
    Interpreter();
    void interpretLine(string src);

};


#endif //PROYECTO_1_DATOS_2_INTERPRETER_H
