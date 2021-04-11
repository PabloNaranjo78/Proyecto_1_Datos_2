//
// Created by anthony on 1/4/21.
//

#include "Interpreter.h"


Interpreter::Interpreter() {
    this->memory = new MemoryLayout();
    this->memory->addLevel();
    this->output = new OutputManager();
    this->lineReader = new LineReader(memory, output);
}

void Interpreter::interpretLine(string src) {
    string line = "";
    for (int i =0; i<src.length(); i++){
        if (src[i] != '\n'){
            line += src[i];
        }else{
            src = src.substr(i+1);
            break;
        }
    }
    this->pending = src;
    cout << line << endl;
    this->lineReader->readLine(line);

}