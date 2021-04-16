#include <gtkmm.h>
#include <iostream>
#include "Interpreter/Interpreter.h"

#include "GUI/MainWindow.h"
#include "GUI/IDE/CodeEditor.h"
#include "ServerSocket/Client/Client.h"
#include "ServerSocket/Server/Server.h"

using namespace Gtk;

using namespace std;



int main (int argc, char *argv[])
{

//    auto app = Gtk::Application::create();
//    MainWindow mainWindow;
//    mainWindow.set_position(Gtk::WIN_POS_CENTER);
//    std::cout<<&app<<endl;
//    return app->run(mainWindow);

//    Interpreter * inter = new Interpreter("int var = 8;\nint var2 = 9;\nvar = var2;\n");
//    inter->interpretLine();
//    inter->interpretLine();
//    inter->interpretLine();

  //  Server server;
  //  server.startServer();

    Client client;
    client.sendData("int bhb = 3;\n int a = 2; \n");
}