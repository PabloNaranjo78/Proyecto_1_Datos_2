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

using namespace std;


class Server {
public:
    Server();
    ~Server();
    void startServer();

private:
    int server = socket(AF_INET,SOCK_STREAM,0);
    int port = 5000;
    int queue = 20;
    int conection;
    string outData;
    char inData[1024];
    struct sockaddr_in server_sockaddr;
    Interpreter * inter;

};


#endif //PROYECTO_1_DATOS_2_SERVER_H
