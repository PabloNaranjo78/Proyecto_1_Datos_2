//
// Created by anthony on 22/4/21.
//

#ifndef PROYECTO_1_DATOS_2_STRUCT_H
#define PROYECTO_1_DATOS_2_STRUCT_H


class Struct {

    template <class T>
    void add(string id, T ref){
        this->container->addVar(id, ref);
    }

    template <class T>
    void setData(string id, T * data){
        this->container->updateVar(id, data);
    }

    void showValues(){
        //this->container->showRAM();
    }
};


#endif //PROYECTO_1_DATOS_2_STRUCT_H
