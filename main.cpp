//#include <gtkmm-3.0/gtkmm.h>
#include <iostream>
#include "Interpreter/Interpreter.h"
/*
#include "GUI/MainWindow.h"
#include "GUI/IDE/CodeEditor.h"
using namespace Gtk;
 */
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
    Interpreter * inter = new Interpreter();
    inter->interpretLine("int var;\n");


}