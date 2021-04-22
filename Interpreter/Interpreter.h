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

/**
 * Interprete del codigo fuente de  C!
 */
class Interpreter {

public:
    MemoryLayout * memory;
    OutputManager * output;
    LineReader * lineReader;
    string outString;
    string pending;
    /**
     * Constructor de la clase
     * @param src codigo fuente a interpretar como string
     */
    Interpreter(string src);
    /**
     * Metodo para intepretar lineas de codigo
     */
    void interpretLine();

};


#endif //PROYECTO_1_DATOS_2_INTERPRETER_H
