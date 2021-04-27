//
// Created by pablo on 15/4/21.
//
#include "../ExternalLibraries/nlohmann/json.hpp"

#ifndef PROYECTO_1_DATOS_2_JSONMANGER_H
#define PROYECTO_1_DATOS_2_JSONMANGER_H

using namespace std;
using json = nlohmann::json;

//! @brief Manejador de json, este se encarga de manejar las entradas y salidas para la creación de json
class JsonManager {
public:
    JsonManager();
    ~JsonManager();
    /***
    * @brief Toma el json que se posee en esta instancia y lo convierte en un string, para así luego poder enviarlo mediante
    * sockets. También limpia el json para poder utilizarlo posteriormente y agrega los valores de refCounter y string
    * Counter al json antes de enviarlo.
    * @return un string con el json de esta instancia.
    */
    string convertDataToString();
    /***
    * @brief Toma información en forma de strings y los inserta en el formato del json
    * @param _counter contador de líneas que se han leído
    * @param ramDir dirección de memoria de la variable
    * @param ramValue valor de la variable
    * @param ramTag etiqueta de la variable
    * @param ramRef conteo de referencias de esta variable
    * @param stdoutText texto que se desee agregar al stdOut del IDE producto de métodos de impresión
    * @param logText texto a agregar al log del IDE
    */
    void addDatatoJson(int counter, string ramDir, string ramValue, string ramTag, string ramRef,
                         string logText);
private:
    json list;
    /***
     * @brief toma el json de la instancia y le elimina los datos que almacena
     */
    void clearJson();
    int counter;
    int refCounter;


};


#endif //PROYECTO_1_DATOS_2_JSONMANGER_H
