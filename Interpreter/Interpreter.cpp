//
// Created by anthony on 1/4/21.
//

#include "Interpreter.h"


Interpreter::Interpreter(string src) {
    this->memory = new MemoryLayout();
    this->memory->addLevel();
    this->output = new OutputManager();
    this->lineReader = new LineReader(memory, output);
    this->pending = src;
}

void Interpreter::interpretLine() {
    string line = "";
    for (int i =0; i<this->pending.length(); i++){
        if (this->pending[i] != '\n'){
            line += this->pending[i];
        }else{
            this->pending = this->pending.substr(i+1);
            break;
        }
    }
    cout << line << endl;
    this->lineReader->readLine(line);

}