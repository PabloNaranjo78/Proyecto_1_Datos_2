//
// Created by pablo on 13/4/21.
//


#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "Client.h"

/***
 * Inicia el cliete, lo mantiene abierto para no perder la conexión con el servidor.
 */
Client::Client() {

    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());

    if (connect(client,(struct sockaddr*)&server_addr, sizeof(server_addr))<0){
        cout<<"Error de conexión"<<endl;
    }
}

Client::~Client() {
    close(client);
}
/***
 * Envía información en forma de string por medio de sockets hacia el servidor
 * @param _outData string con el texto que se obtiene del cajón de entrada de código del IDE.
 * @return Retorna el resultado dado por el servidor, que está en forma de string y debe ser paseado a un json
 * posteriormente.
 */
string Client::sendData(string _outData) {


    strncpy(outData,_outData.c_str(),1024);
    send(client,outData, strlen(outData),0);
    recv(client, inData, sizeof(inData), 0);
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<inData<<endl;
    cout<<"----------------------------------------------------------------------------"<<endl;
  //  close(client);

    return inData;
};

