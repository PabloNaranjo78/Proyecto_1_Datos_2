
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
    std::cout<<&app<<endl;
    return app->run(mainWindow);


    //Interpreter * inter = new Interpreter("int var = 5;\nint var2=var;\n{\n   int var3=4;\n   var3=var;\n}\n");
<<<<<<< HEAD
    Interpreter * inter = new Interpreter("int var;\nreference<int> x;\nint var2 = 7;\n x = getAddress(var2);\nvar = getValue(x);\nint var3 = var2-var;\n");
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
    inter->interpretLine();
=======
//    Interpreter * inter = new Interpreter("reference<int> var;\ngetAddress(var);\n");
//    inter->interpretLine();
//    inter->interpretLine();
>>>>>>> 2e2950e4762a45b6e02f4f23fdcc8af9e9751939
}