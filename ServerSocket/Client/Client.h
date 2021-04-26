//
// Created by pablo on 13/4/21.
//
#include <sys/types.h>
#include <sys/socket.h>
#include <cstdio>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>
#include <sys/shm.h>

#ifndef PROYECTO_1_DATOS_2_CLIENT_H
#define PROYECTO_1_DATOS_2_CLIENT_H

using namespace std;

//! @brief Clase encargada de manejar las salidas y entradas de información del IDE hacia el servidor por sockets
class Client {
public:
    /***
    * @brief Inicia el cliete, lo mantiene abierto para no perder la conexión con el servidor.
    */
    Client();
    ~Client();
    /***
    * @brief Envía información en forma de string por medio de sockets hacia el servidor
    * @param _outData string con el texto que se obtiene del cajón de entrada de código del IDE.
    * @return Retorna el resultado dado por el servidor, que está en forma de string y debe ser paseado a un json
    * posteriormente.
    */
    string sendData(string outData);
private:
    int port = 5000;
    string ip = "127.0.0.1";
    struct sockaddr_in server_addr;
    int client = socket(AF_INET,SOCK_STREAM,0);
    char inData[1024];
    char outData[1024];
};


#endif //PROYECTO_1_DATOS_2_CLIENT_H
