//
// Created by pablo on 31/3/21.
//
/*
#include "MainWindow.h"
#include "IDE/CodeEditor.h"

MainWindow::MainWindow() {

    set_default_size(700,400);
    set_resizable(false);
    set_title("C!");
    set_icon_from_file("../Images/Ico.png");

    server.add_pixlabel("info.xpm","Servidor");
    server.signal_clicked().connect([this]{this->goToServer();});
    client.add_pixlabel("info.xpm","Cliente");
    client.signal_clicked().connect([this] {this->goToClientWindow();});

   set_border_width(100);

    add(box);

    box.set_vexpand(true);
    box.set_hexpand(true);
    server.set_vexpand(true);
    client.set_vexpand(true);
    server.set_hexpand(true);
    client.set_hexpand(true);

    box.attach(server,0,1);
    box.attach(client,0,0);
    show_all_children();
}

MainWindow::~MainWindow() {
}

void MainWindow::goToClientWindow() {

    close();
    Main main;
    CodeEditor codeEditor;
    codeEditor.set_position(Gtk::WIN_POS_CENTER);
    main.run(codeEditor);

}

void MainWindow::goToServer() {
    close();
    //Inicia el servidor y los elementos de manejo del IDE
}




*/