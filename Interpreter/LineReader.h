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
/**
 * Clase lectora de lineas para el interprete (caso particular de un Facade)
 */
class LineReader {
public:
    MemoryLayout * mgmt;
    MemoryManager * current;
    OutputManager * outmgmt;
    MemoryManager * to_assign;
    string id_assign = "";
    bool isRef;
    bool operation;
    int position = 0;
    /**
     * Constructor de la clase
     * @param mgmt instancia unica del MemoryLayout
     * @param output
     */
    LineReader(MemoryLayout * mgmt, OutputManager * output);
    /**
     * Metodo lector de linea
     * @param line Linea que se interpreta en formato string
     * @return un booleano que indica
     */
    bool readLine(string line);
    /**
     * Verifica si se esta agregando un nivel en la ejecucion
     * @param line Linea a analizar
     * @return boolean que indica si se agrega un nivel en la linea
     */
    bool addingLevel(string line);
    /**
     * Procesa las funciones del lenguaje C!
     * @param first primer index desde donde se busca
     * @param line Linea que se evalua
     * @return Valor booleano que indica si se procesa una funcion
     */
    bool processFunction(int first, string line);
    /**
     * Verifica si se realiza una declaracion
     * @param first primer index desde donde se busca
     * @param line Linea que se evalua
     * @return index desde el que se comienza a evaluar la siguiente operacion
     */
    int processDeclaration(int first,string line);
    /**
     * Procesa la asignacion de una variable como ultimo paso
     * @param first primer index desde donde se busca
     * @param line Linea que se analiza
     */
    void processAssignment(int first, string line);
    /**
     * Busca el primer caracter analizable en una linea
     * @param cut una seccion de la linea de codigo
     * @return index donde se encuentra el primer caracter
     */
    int searchFirst(string cut);
    /**
     * Revisa si existe una operacion aritemtica
     * @param cut una seccion de la linea de codigo
     * @return el index del operador
     */
    int checkOperation(string cut);
    /**
     * Busca un identificador en una linea de codigo
     * @param first primer index desde el que se analiza
     * @param line Linea evaluada
     * @return Identificador encontrado
     */
    string searchIdent(int first, string line);
    /**
     * Busca el valor de asignacion de una linea codigo
     * @param line Linea analizada en forma de string
     * @return valor de asignacion
     */
    string searchAssign(string line);

};


#endif //PROYECTO_1_DATOS_2_LINEREADER_H
