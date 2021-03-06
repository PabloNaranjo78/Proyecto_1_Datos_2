//
// Created by pablo on 13/4/21.
//

#ifndef PROYECTO_1_DATOS_2_SERVER_H
#define PROYECTO_1_DATOS_2_SERVER_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <thread>
#include <iostream>
#include "../../Interpreter/Interpreter.h"
#include "../../JsonManeger/JsonManager.h"

using namespace std;

//! @brief Manejador del servidor e intérprete de C!, este envía al intérprete el texto a analizar
class Server {
public:
    /***
    * @brief Da inicio al servidor, este tendrá el objetivo de tomar la entrada en forma de string que viene del la entrada
    * de texto para código del IDE e interpretarlo, para luego responder con un string en forma de json para
    * ser leído por el cliente.
    */
    Server();
    ~Server();
    void startServer();

private:
    int server = socket(AF_INET,SOCK_STREAM,0);
    int port = 5000;
    int queue = 20;
    int conection;
    string outData;

    struct sockaddr_in server_sockaddr;
    Interpreter * inter;

};


#endif //PROYECTO_1_DATOS_2_SERVER_H
