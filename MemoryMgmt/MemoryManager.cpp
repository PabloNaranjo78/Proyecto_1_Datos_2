//
// Created by anthony on 1/4/21.
//

#include "MemoryManager.h"


MemoryManager::MemoryManager() {
   // this->nodes_arr = NULL;
    this->var_count = 0;
}
template<class T>
void MemoryManager::addVar(string id, T data) {
    this->var_count++;
    void * current_vars = malloc(sizeof(T)*this->var_count);
    if (this->var_count){
      //  this->nodes_arr = current_vars;
      //  this->nodes_arr[0] = new Node<T>;
    }
}
