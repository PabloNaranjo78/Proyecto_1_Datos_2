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
    /*
    auto app = Gtk::Application::create();
    MainWindow mainWindow;
    mainWindow.set_position(Gtk::WIN_POS_CENTER);
    std::cout<<&app<<endl;
    return app->run(mainWindow);
    */
    Interpreter * inter = new Interpreter("int var = 5;\nint var2=var;\n{\n   int var3=4;\n    var3=var;\n}");
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
}