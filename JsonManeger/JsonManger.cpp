//
// Created by pablo on 15/4/21.
//


#include "JsonManger.h"
#include "../ExternalLibraries/nlohmann/json.hpp"

using json = nlohmann::json;

JsonManger::JsonManger() {

}

JsonManger::~JsonManger() {

}

string JsonManger::convertDataToJson() {
    list["Name"] = "hola";

    return std::string();
}
