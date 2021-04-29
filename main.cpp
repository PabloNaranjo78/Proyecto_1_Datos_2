/**
 * Proyecto I
 * Algoritmos y Estructuras de Datos II
 * Realizado por:
 * Anthony Chaves Achoy
 * Pablo Naranjo Monge
 */


#include <gtkmm.h>


#include "GUI/MainWindow.h"
#include "GUI/IDE/CodeEditor.h"
#include "ServerSocket/Client/Client.h"
#include "ServerSocket/Server/Server.h"


using namespace Gtk;



#include <iostream>
#include "Interpreter/Interpreter.h"

using namespace std;



int main (int argc, char *argv[])
{

    auto app = Gtk::Application::create();
    MainWindow mainWindow;
    mainWindow.set_position(Gtk::WIN_POS_CENTER);
    return app->run(mainWindow);


    Interpreter * inter = new Interpreter("int var = 5;\nstruct classA\n{\n   int x;\n   int z;\n}\nclassA cA;\n{\n   cA.z = 8;\n   int j = cA.z;\n}\n");
//    Interpreter * inter = new Interpreter("reference<int> var;\ngetAddress(var);\n");
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();

}