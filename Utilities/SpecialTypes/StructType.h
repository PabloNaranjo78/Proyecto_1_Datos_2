//
// Created by anthony on 17/4/21.
//

#ifndef PROYECTO_1_DATOS_2_STRUCTTYPE_H
#define PROYECTO_1_DATOS_2_STRUCTTYPE_H

#include "Struct.h"
#include <iostream>
#include <string>
#include <typeinfo>
#include "../../MemoryMgmt/MemoryManager.h"

/**
 * Clase para almacenar y procesar los datos de los tipos generados por medio de structs
 */
using namespace std;
class StructType {
public:
    Struct * head;
    /**
     * Constructor de la clase
     */
    StructType();
    /**
     * Agrega un tipo a la lista
     * @param ident identificador del tipo
     */
    void addType(string ident);
    /**
     * Revisa si un identificador se encuentra en lista de structs
     * @param idType identificador del tipo buscado
     * @return valor de verdad que indica si se enmcuentra en la lista
     */
    bool isIn(string idType);
    /**
     * Agrega atributos a un struct
     * @param idType idenfitificador del tipo de struct
     * @param varType tipo del atributo
     * @param varName identificador del atributo
     */
    void addToType(string idType, string varType, string varName);
    /**
     * Crea una instancia de un struct previamente definido
     * @param idT identificador del tipo de struct
     * @param instName nombre de la variable de la instancia
     * @param manager gestor de memoria en el que se escriben las variables
     */
    void createInstance(string idT,string instName ,MemoryManager * manager);
    /**
     * Muestra los valores relacionados a un struct especifico
     * @param idT identificador del struct
     */
    void showValues(string idT);
};


#endif //PROYECTO_1_DATOS_2_STRUCTTYPE_H
