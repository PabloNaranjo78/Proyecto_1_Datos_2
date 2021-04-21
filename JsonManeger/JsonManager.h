//
// Created by pablo on 15/4/21.
//
#include "../ExternalLibraries/nlohmann/json.hpp"

#ifndef PROYECTO_1_DATOS_2_JSONMANGER_H
#define PROYECTO_1_DATOS_2_JSONMANGER_H

using namespace std;
using json = nlohmann::json;
class JsonManager {
public:
    JsonManager();
    ~JsonManager();
    string convertDataToJson();
    void addDatatoJson(int counter, string ramDir, string ramValue, string ramTag, string ramRef, string stdoutText,
                         string logText);
private:
    json list;
    void clearJson();
    int counter;
    int refCounter;


};


#endif //PROYECTO_1_DATOS_2_JSONMANGER_H
