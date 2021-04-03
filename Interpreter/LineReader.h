//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_LINEREADER_H
#define PROYECTO_1_DATOS_2_LINEREADER_H

#include <string>
#include <iostream>
#include "../MemoryMgmt/MemoryManager.h"

using namespace std;

class LineReader {
public:
    string readLine(string line, MemoryManager memMgmt);
    bool processDeclaration(int first,string line, MemoryManager mgmt);
    int searchFirst(string cut);
    string searchIdent(int first, string line);
};


#endif //PROYECTO_1_DATOS_2_LINEREADER_H
