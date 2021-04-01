//
// Created by pablo on 31/3/21.
//

#ifndef PROYECTO_1_DATOS_2_MAINWINDOW_H
#define PROYECTO_1_DATOS_2_MAINWINDOW_H


#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm.h>

using namespace Gtk;
class MainWindow : public Window{

public:
    MainWindow();
    virtual ~MainWindow();
    void exampl(MainWindow *m);
    Button server,client;
private:
    Grid box;
    void goToClientWindow();

};


#endif //PROYECTO_1_DATOS_2_MAINWINDOW_H
