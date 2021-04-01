//
// Created by pablo on 31/3/21.
//

#ifndef PROYECTO_1_DATOS_2_CODEEDITOR_H
#define PROYECTO_1_DATOS_2_CODEEDITOR_H


#include "../MainWindow.h"

class CodeEditor : public Window {

public:
    CodeEditor() ;
    ~CodeEditor();
    void codeEditorWindow();

private:
    Fixed screen;

    Button runButton;
    Button debugButton;
    Button stopButton;
    Button stepButton;

    ScrolledWindow codeEntryScroll;
    ScrolledWindow stdOutScroll;
    ScrolledWindow logViewScroll;
    ScrolledWindow ramViewScroll;

    TextView codeEntry;
    TextView stdOut;
    TextView logView;
    TextView ramView;
};


#endif //PROYECTO_1_DATOS_2_CODEEDITOR_H
