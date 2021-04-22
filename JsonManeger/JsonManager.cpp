//
// Created by pablo on 15/4/21.
//


#include <iostream>
#include "JsonManager.h"
#include "../ExternalLibraries/nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;

/***
 * El constructor se encarga de instanciar el formato que tendrá el json, para luego solo agregar la información
 * a las diferentes nombres.
 */
JsonManager::JsonManager() {
    
    list["lineCounter"];
    list["ramDir"]={};
    list["ramValue"] = {};
    list["ramTag"] = {};
    list["ramRef"] = {};
    list["stdOutText"] = {};
    list["logText"] = {};
    list["refText"] = 0;
}

JsonManager::~JsonManager() {

}

/***
 * Toma el json que se posee en esta instancia y lo convierte en un string, para así luego poder enviarlo mediante
 * sockets. También limpia el json para poder utilizarlo posteriormente y agrega los valores de refCounter y string
 * Counter al json antes de enviarlo.
 * @return un string con el json de esta instancia.
 */
string JsonManager::convertDataToString() {
    string stringCounter(std::to_string(counter));
    list["lineCounter"] = counter;
    json temp = list;
    clearJson();
    return temp.dump();
}

/***
 * Toma información en forma de strings y los inserta en el formato del json
 * @param _counter contador de líneas que se han leído
 * @param ramDir dirección de memoria de la variable
 * @param ramValue valor de la variable
 * @param ramTag etiqueta de la variable
 * @param ramRef conteo de referencias de esta variable
 * @param stdoutText texto que se desee agregar al stdOut del IDE producto de métodos de impresión
 * @param logText texto a agregar al log del IDE
 */
void JsonManager::addDatatoJson(int _counter, string ramDir, string ramValue, string ramTag, string ramRef,
                                  string logText) {

    counter+= _counter;
    list["ramDir"]+= ramDir;
    list["ramValue"] += ramValue;
    list["ramTag"] += ramTag;
    list["ramRef"] += ramRef;
   // list["stdOutText"] += stdoutText;
    list["logText"] += logText;

    std::cout<<"Se añade una tanda   " <<ramDir<<std::endl;

}
/***
 * Limpia el json para poder utilizarlo después y vuelve a crear el formato original.
 */
void JsonManager::clearJson() {
    list.clear();
    counter = 0;
    list["lineCounter"] = 0;
    list["ramDir"]={};
    list["ramValue"] = {};
    list["ramTag"] = {};
    list["ramRef"] = {};
 //   list["stdOutText"] = {};
    list["logText"] = {};

}
