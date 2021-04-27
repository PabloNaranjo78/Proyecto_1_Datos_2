//
// Created by pablo on 15/4/21.
//


#include <iostream>
#include "JsonManager.h"
#include "../ExternalLibraries/nlohmann/json.hpp"
using namespace std;
using json = nlohmann::json;


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

string JsonManager::convertDataToString() {
    string stringCounter(std::to_string(counter));
    list["lineCounter"] = counter;

    json temp = list;
    clearJson();
    return temp.dump();
}

void JsonManager::addDatatoJson(int _counter, string ramDir, string ramValue, string ramTag, string ramRef,
                                  string logText, string stdoutText) {




    counter+= _counter;
    list["ramDir"]+= ramDir;
    list["ramValue"] += ramValue;
    list["ramTag"] += ramTag;
    list["ramRef"] += ramRef;
    list["stdOutText"] += stdoutText;
    list["logText"] += logText;

    std::cout<<"Se añade una tanda   " <<ramDir<<std::endl;

}

void JsonManager::clearJson() {
    list.clear();
    counter = 0;
    list["lineCounter"] = 0;
    list["ramDir"]={};
    list["ramValue"] = {};
    list["ramTag"] = {};
    list["ramRef"] = {};
    list["stdOutText"] = {};
    list["logText"] = {};

}
