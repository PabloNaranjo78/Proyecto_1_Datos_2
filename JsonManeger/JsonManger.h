//
// Created by pablo on 15/4/21.
//
#include "../ExternalLibraries/nlohmann/json.hpp"

#ifndef PROYECTO_1_DATOS_2_JSONMANGER_H
#define PROYECTO_1_DATOS_2_JSONMANGER_H

using namespace std;
using json = nlohmann::json;
class JsonManger {
public:
    JsonManger();
    ~JsonManger();
    string convertDataToJson();
private:
    json list;

};


#endif //PROYECTO_1_DATOS_2_JSONMANGER_H
