//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_LINEREADER_H
#define PROYECTO_1_DATOS_2_LINEREADER_H

#include <string>
#include <iostream>
#include "../MemoryMgmt/MemoryManager.h"
#include "../MemoryMgmt/MemoryLayout.h"
#include "OutputManager.h"

using namespace std;

class LineReader {
public:
    MemoryLayout * mgmt;
    MemoryManager * current;
    OutputManager * outmgmt;
    int position = 0;
    LineReader(MemoryLayout * mgmt, OutputManager * output);
    bool readLine(string line);
    bool addingLevel(string line);
    bool processDeclaration(int first,string line);
    void processAssignment(int first, string line);
    int searchFirst(string cut);
    string searchIdent(int first, string line);
    void levelDeclaration();
    string searchAssign(string line);

};


#endif //PROYECTO_1_DATOS_2_LINEREADER_H
