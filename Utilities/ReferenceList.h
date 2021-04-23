//
// Created by anthony on 16/4/21.
//

#include <iostream>
#include <string>
#include "Reference.h"

#ifndef PROYECTO_1_DATOS_2_REFERENCELIST_H
#define PROYECTO_1_DATOS_2_REFERENCELIST_H

using namespace std;

class ReferenceList {
public:
    Reference * head;
    int listLenght;
    /**
     * Constructor de la clase de lista de referencias
     */
    ReferenceList();
    /**
     * Agrega una referencia a la lista
     * @param lvl_from entero que se refiere al nivel proveniente
     */
    void add(int lvl_from);
    /**
     * Actualiza un nodo referencia al eliminar un nivel
     * @param lvlDel nivel eliminado
     */
    void update(int lvlDel);
    /**
     * Devuelve las referencias que se han contado hasta el momento
     * @return cantidad de referencias
     */
    int getRefs();
};


#endif //PROYECTO_1_DATOS_2_REFERENCELIST_H
