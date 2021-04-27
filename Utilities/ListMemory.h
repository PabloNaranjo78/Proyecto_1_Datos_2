//
// Created by anthony on 1/4/21.
//

#ifndef PROYECTO_1_DATOS_2_LISTMEMORY_H
#define PROYECTO_1_DATOS_2_LISTMEMORY_H

#include <iostream>
#include <string>
#include <typeinfo>
#include "Node.h"
#include <sstream>
#include "SpecialTypes/ReferenceType.h"
#include "../JsonManeger/JsonManager.h"
#include "../Logger/Logger.h"

using namespace std;

/**
 * @brief Clase de lista enlazada simple generica
 * @tparam T tipo de dato generico que puede ser int, float, long, char o double
 */

template <class T>
class ListMemory {


public:
    /*
    ListMemory<T>(){
        this->head = NULL;
    };
    void add(string id);
    void deleteVar(string id);
    void updateVar(string id, T data);
    bool isIn(string id);
    void showValues();
    T * getData(string id);
     */
    Node<T> * head;
    /**
     * @brief Constructor de la clase de memoria de lista
     */
    ListMemory<T>(){
        this->head = NULL;
    }
    /**
     * @brief Verifica si una variable fue inicializada
     * @param ident identificador del nodo
     * @return valor booleano que indica si ya fue asignado
     */
    bool isInit(string ident){
        Node<T> * tmp = this->head;
        while (tmp != NULL) {
            if (tmp->identifier == ident) {
                break;
            }
            tmp = tmp->next;
        }
        return tmp->init;
    }
    /**
     * @brief Agrega un nodo a la lista
     * @param id identificador asociado al nodo
     * @param data valor de referencia para definir el tipo de dato que almacena
     * @param ref indica si es de tipo reference y guarda una direccion de memoria
     */
    void add(string id, T data, bool ref) {
        cout << "Agregando data" << endl;
        Node<T> * newNode = new Node<T>;
        if (this->head == NULL){
            this->head = newNode;
        }else{
            Node<T> * tmp = head;
            while(tmp->next != NULL){
                cout << "buscando..." << endl;
                tmp = tmp->next;
            }
            tmp->next = newNode;
        }
        cout << "Agregando data 2" << endl;
        if (!ref && !(typeid(string) == typeid(data))){
            newNode->dir = (T*)malloc(sizeof(data));
            newNode->data = data;
            * newNode->dir = newNode->data;
        }else if (!ref && (typeid(string) == typeid(data))){
            //newNode->dir = (T*)malloc(sizeof(data));
            newNode->data = data;
            //* newNode->dir = newNode->data;
        }
        else{
            cout << "Here 2" << endl;
            newNode->dir = (T*)malloc(sizeof(data));
            newNode->data_ref = NULL;
        }
        newNode->ref = ref;
        newNode->identifier = id;
    }
    /**
     * @brief Elimina un valor de la lista
     * @param id identificador del valor
     */
    void deleteVar(string id) {
        if (this->head->identifier == id){
            this->head = this->head->next;
        }else{
            Node<T> * tmp = this->head;
            while (tmp->next->identifier !=  id){
                tmp = tmp->next;
            }
            tmp->next = tmp->next->next;
            free(tmp->next);
        }
    }
    /**
     * @brief Verifica si un valor esta en la lista
     * @param id identificador asociado al nodo
     * @return valor de verdad que indica si se encuentra en lista actual
     */
    bool isIn(string id) {
        Node<T> * tmp = this->head;
        bool result = false;
        while(tmp != NULL){
            cout << "Ident: " << tmp->identifier << endl;
            if (tmp->identifier == id) {
                result = true;
                break;
            }
            cout << tmp << "actual" << endl;
            tmp = tmp->next;
        }
        cout << "nivel: "<< result << endl;
        return result;
    }
    /**
     * @brief Actualiza el valor asociado a un nodo
     * @param id Identificador asociado al nodo
     * @param data valor nuevo que se asignara al nodo
     */
    void updateVar(string id, T * data) {
        Node<T> * tmp = this->head;
        while(tmp != NULL){
            if (tmp->identifier == id) {
                if (typeid(* data) == typeid(tmp->data)){
                    if (!isRef(id)){
                        tmp->init = true;
                        tmp->data = * data;
                        * tmp->dir = tmp->data;
                    }else{
                        tmp->init = true;
                        tmp->data_ref = data;
                    }

                }else{
                    cout << "Error de tipo de datos" << endl;
                }
            }
            tmp = tmp->next;
        }
    }
    /**
     * @brief Muestra los valores de la lista y envia un json con dischos valores
     * @param jsonManager gestor de json donde se enviaran los valores al cliente
     */
    void showValues(JsonManager *jsonManager,Logger *log,string printing) {
        Node<T> * tmp = this->head;
        while(tmp != NULL){
            if (tmp->init && !tmp->ref){
                T data = * tmp->dir;
                cout << "ID: " << tmp->identifier << " Data: " << data << " Dir: " << tmp->dir << " Referencias: " << tmp->refs->getRefs() << endl;

                ostringstream get_the_address;
                get_the_address<< tmp->dir;
                string _dir = get_the_address.str().substr(0,14);
                jsonManager->addDatatoJson(1, _dir, to_string(data), tmp->identifier, to_string(tmp->refs->getRefs()), log->getInfo(),printing);

            }else if (tmp->init && tmp->ref){
                cout << "ID: " << tmp->identifier << " Data: " << tmp->data_ref << " Dir: " << tmp->dir << " Referencias: " << tmp->refs->getRefs() << endl;
                ostringstream get_the_address;
                get_the_address<< tmp->dir;
                string _dir = get_the_address.str();
                get_the_address<<tmp->data_ref;
                string _data = get_the_address.str();

                jsonManager->addDatatoJson(1,_dir, _data ,tmp->identifier,to_string(tmp->refs->getRefs()),log->getInfo(),printing);
            }
            else{
                cout << "ID: " << tmp->identifier << " Data: NULL" << " Dir: " << tmp->dir << " Referencias: " << tmp->refs->getRefs() << endl;
                ostringstream get_the_address;
                get_the_address<< tmp->dir;
                string _dir = get_the_address.str();
                jsonManager->addDatatoJson(1,_dir,"NULL",tmp->identifier,to_string(tmp->refs->getRefs()),log->getInfo(),printing);
            }
            tmp = tmp->next;
        }
    }
    /**
     * @brief Obtiene el valor de un nodo
     * @param id identificador del nodo buscado
     * @return valor asociado al nodo
     */
    T getData(string id) {
        Node<T> * tmp = this->head;
        T data;
        bool found = false;
        while (tmp != NULL) {
            cout << tmp->identifier << "--Identificador" << endl;
            if (tmp->identifier == id) {
                data = tmp->data;
                found = true;
                cout << "obtenido" << endl;
                break;
            }
            tmp = tmp->next;
        }
        if (found && tmp->init) {
            return data;
        } else {
            throw "Error";
        }
    }
    /**
     * @brief Devuelve la direccion de memoria de un nodo
     * @param id identificador del nodo
     * @return puntero del tipo instanciado previamente que contiene la direccion de memoria del valor del nodo
     */
    T * getAddress(string id){
        cout << "getting address" << endl;
        Node<T> * tmp = this->head;
        T * data_dir;
        bool found = false;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                data_dir = tmp->dir;
                found = true;
                break;
            }
            tmp = tmp->next;
        }
        if (found) {
            return data_dir;
        } else {
            throw "Error";
        }
    }
    /**
     * @brief Devuelve la direccion de memoria que contiene un dato de tipo reference
     * @param id identificador del nodo
     * @return puntero del tipo instanciado previamente que contiene la direccion de memoria contenida por el nodo
     */
    T * getAddPointed(string id){
        Node<T> * tmp = this->head;
        T * data_ref;
        bool found = false;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                data_ref = tmp->data_ref;
                found = true;
                break;
            }
            tmp = tmp->next;
        }
        if (found && tmp->init) {
            return data_ref;
        } else {
            throw "Error";
        }
    }
    /**
     * @brief Suma una referencia a un nodo
     * @param id identificador del nodo
     * @param lvl_from nivel desde el que se realiza la referencia
     */
    void count_reference(string id, int lvl_from){
        Node<T> * tmp = this->head;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                tmp->refs->add(lvl_from);
                break;
            }
            tmp = tmp->next;
        }
    }
    /**
     * @brief Actualiza las referencias del nodo al eliminar un nivel
     * @param lvl_del nivel eliminado
     */
    void update_refences(int lvl_del){
        Node<T> * tmp = this->head;
        while (tmp != NULL) {
            tmp->refs->update(lvl_del);
            tmp = tmp->next;
        }
    }
    /**
     * @brief Indica si el valor del nodo es una referencia a otra direccion
     * @param id identificador del nodo
     * @return valor de verdad que indica si es del tipo reference
     */
    bool isRef(string id){
        Node<T> * tmp = this->head;
        bool isRef = false;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                cout << "Identificador encontrado" << endl;
                isRef = tmp->ref;
                break;
            }
            tmp = tmp->next;
        }
        return isRef;
    }
    /**
     * @brief Retorna el tipo de dato de una variable
     * @param id identificador de la variable
     * @return string que contiene el tipo de dato
     */
    string getType(string id){
        Node<T> * tmp = this->head;
        T type;
        while (tmp != NULL) {
            if (tmp->identifier == id) {
                type = tmp->data;
                break;
            }
            tmp = tmp->next;
        }
        return type;
    }


};


#endif //PROYECTO_1_DATOS_2_LISTMEMORY_H
