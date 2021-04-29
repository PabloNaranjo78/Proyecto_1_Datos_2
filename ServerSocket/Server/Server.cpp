//
// Created by pablo on 13/4/21.
//

#include "Server.h"
using json = nlohmann::json;

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
        if (inData[0] == '$' and inData[1]=='#'){
            cout<<"Cerrando servidor....";
            break;
        }
        inter = new Interpreter(inData);

        int counter = 0;
        string inDataString = inData;

        for (int i = 0; i < inDataString.length();i++){
            if (inDataString[i]=='\n'){
                counter++;
            }
//            else if (inDataString[i]=='{'){
//                counter--;
//            }
        }

        json outDataJson = {};

        cout<<counter<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
        for (int i= 0; i<counter;i++){
            cout<<outData<<"#######"<<i<<endl;
   //         outDataJson+=inter->interpretLine();
            outData= inter->interpretLine();
            outDataJson+=outData;

        }

        cout<<outDataJson.dump()<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;

        string outDataFinal = outDataJson.dump();

        char outChar[10000];
        //strcpy(outChar,outDataJson.dump().c_str());
        strcpy(outChar,outDataFinal.c_str());
        send(conection, outChar, sizeof (outChar), 0);

    }
    close(conection);
    close(server);
}

Server::~Server() {
}

Server::Server() {

}
