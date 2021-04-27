//
// Created by anthony on 26/4/21.
//

#include <iostream>
#include <string>


#ifndef PROYECTO_1_DATOS_2_LOGGER_H
#define PROYECTO_1_DATOS_2_LOGGER_H
using namespace std;
/**
 * Clase para realizar logs
 */
class Logger {
public:
    /**
     * Genera un mensaje de tipo log, incluyendo su nivel de prioridad
     * @param lvl nivel de prioridad/gravedad
     * @param message mensaje
     * @return log formado a partir del mensaje y su prioridad
     */
    string logStatement(int lvl, string message);
};


#endif //PROYECTO_1_DATOS_2_LOGGER_H
