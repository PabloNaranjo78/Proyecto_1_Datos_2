//
// Created by anthony on 8/4/21.
//

#ifndef PROYECTO_1_DATOS_2_MEMORYLAYOUT_H
#define PROYECTO_1_DATOS_2_MEMORYLAYOUT_H
#include "MemoryManager.h"
#include <string>
#include <iostream>
#include <typeinfo>
#include "../ExternalLibraries/nlohmann/json.hpp"
#include "../JsonManeger/JsonManager.h"
#include "../Utilities/SpecialTypes/StructType.h"

using json = nlohmann::json;
using namespace std;

/**
 * @brief Clase de la distribucion de memoria general
 */
class MemoryLayout {

public:
    MemoryManager * head;
    StructType * structManager;
    int lvl = 0;
    /**
     * @brief Constructor del mapa de memoria
     */
    MemoryLayout();
    /**
     * @brief Agrega un nivel a la memoria
     * @return Retorna el gestor de memoria creado para el nuevo nivel
     */
    MemoryManager * addLevel();
    /**
     * @brief Cuenta una referencia para una variable especifica en memoria
     * @param id identificador de la variable
     * @param lvl_from nivel en el que se referencia a la variable
     */
    void count_reference(string id, int lvl_from);
    /**
     * @brief Elimina todas las referencias a un nivel
     * @param lvl_del Entero que hace referencia al nivel eliminado
     */
    void delete_refs(int lvl_del);
    /**
     * @brief Encuentra el nivel en el que se encuentra una variable
     * @param level nivel en el que se deberia empezar a buscar la variable
     * @param ident Identificador de la variable
     * @return el nivel en el que se encuentra la variable
     */
    int checkOnLevel(int level, string ident);
    /**
     * @brief Obtiene el valor asociado a una variable de una nivel especifico
     * @tparam T tipo de dato generico
     * @param level nivel en el que se encuentra la variable
     * @param ident identificador de la variable
     * @return valor asociaddo a la variable en su tipo de dato instanciado
     */
    template<class T>
    T getValue(int level, string ident){
        MemoryManager * tmp = this->head;
        T value[5];
        T concreteVal;
        while(tmp->lvl <= level && tmp != NULL){
            value[0] = tmp->getValue<int>(ident);
            value[1] = tmp->getValue<float>(ident);
            value[2] = tmp->getValue<long>(ident);
            value[3] = tmp->getValue<char>(ident);
            value[4] = tmp->getValue<double>(ident);

            for (int i=0; i<5; i++){
                if (value[i] != NULL){
                    concreteVal = * value[i];
                    break;
                }
            }

            break;
        }
        return concreteVal;
    }
    /**
     * @brief Devuelve un gestor de memoria asociado a un nivel
     * @param lvl entero que identifica el nivel requerido
     * @return gestor de memoria asociado en el nivel solicitado
     */
    MemoryManager * getLevel(int lvl);
    /**
     * @brief Elimina un nivel segun el entero asoaciado al mismo
     * @param lvl numero entero que identifica el nivel
     */
    void deleteLevel(int lvl);
    /**
     * @brief Verifica si una variable fue inicializada
     * @param id Identificador de la variable
     * @param lvl nivel en el que se
     * @return
     */
    bool isInit(string id, int lvl);
    /**
     * @brief Devuelve el tipo de una variable
     * @param id identificador asociado ala variable buscada
     * @return el string asociado al tipo de dato de la variable
     */
    string getType(string id);
    /**
     * @brief Muestra las variables en la ram y sus caracteristicas
     * @return el string que contiene las variables actuales y sus caracteristicas
     */
    string showRam();

private:
    JsonManager * jsonManager = new JsonManager;



};


#endif //PROYECTO_1_DATOS_2_MEMORYLAYOUT_H
