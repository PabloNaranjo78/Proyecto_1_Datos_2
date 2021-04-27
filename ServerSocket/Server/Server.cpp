//
// Created by pablo on 13/4/21.
//

#include "Server.h"


void Server::startServer() {
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(port);

    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server,(struct sockaddr*)&server_sockaddr, sizeof(server_sockaddr))==-1){
        cout<<"Error conectando"<<endl;
        return;
    }
    if (listen(server,queue)==-1){
        cout<<"Error escuchando cliente"<<endl;
        return;
    }

    struct  sockaddr_in client_addr;
    socklen_t socklen = sizeof(client_addr);

    conection = accept(server, (struct sockaddr *) &client_addr, &socklen);
    if (conection < 0) {
        cout << "Error de conexión" << endl;
        return;
    }

    while(true) {
        cout << "Esperando conexión..." << endl;

        recv(conection, inData, sizeof(inData), 0);
        cout << "Nueva conexión" << endl;
        cout << inData << "---------" << endl;
        if (inData == "$$") break;
        inter = new Interpreter(inData);

        int counter = 0;
        string inDataString = inData;

        for (int i = 0; i < inDataString.length();i++){
            if (inDataString[i]=='\n'){
                counter++;
            }
            else if (inDataString[i]=='{' or inDataString[i]=='}'){
                counter--;
            }
        }

        for (int i= 0; i<counter;i++){
            outData = inter->interpretLine();
        }

        char outChar[1024];
        strcpy(outChar,outData.c_str());
        send(conection, outChar, sizeof (outChar), 0);

    }
    close(conection);
    close(server);
}

Server::~Server() {
}

Server::Server() {

}
