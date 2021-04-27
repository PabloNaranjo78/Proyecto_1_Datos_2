//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_MEMORYMANAGER_H
#define PROYECTO_1_DATOS_2_MEMORYMANAGER_H

#include <string>
#include <iostream>
#include <typeinfo>
#include "../Utilities/ListMemory.h"
#include "../JsonManeger/JsonManager.h"
#include "../Logger/Logger.h"
//#include "../Utilities/SpecialTypes/Struct.h"
//#include "../Utilities/SpecialTypes/StructType.h"


using namespace std;

/**
 * @brief Clase de gestor de memoria, administra un nivel de memoria especifica
 */
class MemoryManager {

    ListMemory<int> * list_int = new ListMemory<int>();
    ListMemory<float> * list_float = new ListMemory<float>();
    ListMemory<char> * list_char = new ListMemory<char>();
    ListMemory<long> * list_long = new ListMemory<long>();
    ListMemory<double> * list_double = new ListMemory<double>();

public:

    MemoryManager * next;
    int lvl;
    /**
     * @brief Constructor de la clase de gestor de memoria
     * @param level nivel asociado
     */
    MemoryManager(int level);
    /**
     * @brief Retorna el nivel en el que se encuentra la memoria apartada
     * @return el nivel en forma de numero entero
     */
    int getLvL();
    /**
     * @brief  Valora si una variable es una referencia de memoria
     * @param id identificador que se busca en la memoria
     * @return booleano que indica si un valor es una referencia
     */
    bool isRef(string id);
    /**
     * @brief Elimina una variable de la memoria
     * @param ident identificador relacionado a la variable
     */
    void deleteVar(string ident);
    /**
     * @brief Muestra la RAM y envia el string relacionado al jsonManager
     * @param jsonManager Manager que envia strings por medio de Json
     */
    void showRAM(JsonManager *jsonManager,Logger *log,string printing);
    /**
     * @brief Verifica si una variable esta en memoria
     * @param ident identificador relacionado a la variable
     * @return booleano que indica si una variable relacionada a su identificador esta en memoria
     */
    bool isInMemory(string ident);
    /**
     * @brief Devuelve el tipo de dato
     * @param ident identificador de la variable
     * @return string que indica el tipo de dato de la variable
     */
    string getType(string ident);
    /**
     * @brief Suma una referencia al conteo de una variable
     * @param id Identificador de la variable
     * @param lvl_from nivel del que se referencia la variable
     */
    void add_reference(string id, int lvl_from);
    /**
     * @brief Actualiza las referencias asociadas a una variable en caso de eliminar un nivel
     * @param lvl_from nivel que se elimina
     */
    void update_refs(int lvl_from);
    /**
     * @brief Verifica si una variable fue inicializada
     * @param ident identificador de la variable
     * @return booleano que indica si la variable ya fue asignada
     */
    bool isInit(string ident);
    /**
     * @brief Se agrega una variable al mapa de memoria de un nivel especifico
     * @tparam T tipo de dato generico
     * @param id identificador de la nueva variable
     * @param data valor asociado a la nueva variable
     * @param isRef booleano que indica si es referencia
     */
    template<class T>
    void addVar(string id, T data, bool isRef){

        if(typeid(int) == typeid(data)){
            this->list_int->add(id, data, isRef);
        }else if(typeid(float) == typeid(data)){
            this->list_float->add(id, data, isRef);
        }else if(typeid(long) == typeid(data)){
            this->list_long->add(id, data, isRef);
        }else if(typeid(char) == typeid(data)){
            this->list_char->add(id, data, isRef);
        }else if(typeid(double) == typeid(data)){
            this->list_double->add(id, data, isRef);
        }

    }
    /**
     * @brief Actualiza el valor asociado a una variable especifica
     * @tparam T tipo de dato generico
     * @param ident identificador de la nueva variable
     * @param data nuevo dato que se asigna a la variable
     */
    template<class T>
    void updateVar(string ident, T * data){
        if (this->list_int->isIn(ident)){
            this->list_int->updateVar(ident, (int* )data);
        }else if(this->list_float->isIn(ident)){
            this->list_float->updateVar(ident, (float* )data);
        }else if(this->list_long->isIn(ident)){
            this->list_long->updateVar(ident, (long* )data);
        }else if(this->list_char->isIn(ident)){
            this->list_char->updateVar(ident, (char* )data);
        }else if(this->list_double->isIn(ident)){
            this->list_double->updateVar(ident, (double * )data);
        }
    }
    /**
     * @brief Obtiene el valor asociado a una variable
     * @tparam T tipo de dato generico
     * @param ident identificador asociado a la variable
     * @return valor actual de la variable segun el tipo con el que se haya instanciado
     */
    template<class T>
    T getValue(string ident){
        if (this->list_int->isIn(ident)){
            return this->list_int->getData(ident);
        }else if(this->list_float->isIn(ident)){
            return this->list_float->getData(ident);
        }else if(this->list_long->isIn(ident)){
            return this->list_long->getData(ident);
        }else if(this->list_char->isIn(ident)){
            return this->list_char->getData(ident);
        }else if(this->list_double->isIn(ident)){
            return this->list_double->getData(ident);
        }

    }
    /**
     * @brief Retorna la direccion de memoria de una variable
     * @tparam T tipo de dato generico
     * @param ident identificador asociado a la variable
     * @return Puntero del tipo de dato de la variable que referencia su direccion de memoria
     */
    template<class T>
    T* getAddress(string ident){

        if (this->list_int->isIn(ident)){
            return (T *)this->list_int->getAddress(ident);

        }else if(this->list_float->isIn(ident)){
            return (T *)this->list_float->getAddress(ident);

        }else if(this->list_long->isIn(ident)){
            return (T *)this->list_long->getAddress(ident);

        }else if(this->list_char->isIn(ident)){
            return (T *)this->list_char->getAddress(ident);

        }else if(this->list_double->isIn(ident)){
            return (T *)this->list_double->getAddress(ident);
        }
    }
    /**
     * @brief Devuelve el puntero al que un valor de tipo referencia apunta
     * @tparam T tipo de dato generico
     * @param ident identificador asociado a la variable
     * @return puntero contenido en un dato de tipo reference
     */
    template<class T>
    T* getAddPoint(string ident){

        if (this->list_int->isIn(ident)){
            return (T *)this->list_int->getAddPointed(ident);

        }else if(this->list_float->isIn(ident)){
            return (T *)this->list_float->getAddPointed(ident);

        }else if(this->list_long->isIn(ident)){
            return (T *)this->list_long->getAddPointed(ident);

        }else if(this->list_char->isIn(ident)){
            return (T *)this->list_char->getAddPointed(ident);

        }else if(this->list_double->isIn(ident)){
            return (T *)this->list_double->getAddPointed(ident);
        }
    }
};


#endif //PROYECTO_1_DATOS_2_MEMORYMANAGER_H
