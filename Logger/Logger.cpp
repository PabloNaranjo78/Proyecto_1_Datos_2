//
// Created by anthony on 26/4/21.
//

#include "Logger.h"


string Logger::logStatement(int lvl, string message) {
    string logOut = "";
    if (lvl == 1){
        logOut = "[INFO] "+message;
    }else if (lvl == 2){
        logOut = "[WARN] "+message;
    }else if (lvl == 3){
        logOut = "[ERROR] "+message;
    }else if (lvl == 4){
        logOut = "[FATAL] "+message;
    }

    return logOut;
}