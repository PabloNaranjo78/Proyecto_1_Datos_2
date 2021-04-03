//
// Created by pablo on 31/3/21.
//

#ifndef PROYECTO_1_DATOS_2_CODEEDITOR_H
#define PROYECTO_1_DATOS_2_CODEEDITOR_H


#include "../MainWindow.h"
using namespace std;

class CodeEditor : public Window {

public:
    CodeEditor() ;
    ~CodeEditor();

    string getCodeEntryText();
    void setSTDOutText(string text);
    void setLogText(string text);
    void setRamText(string dirText, string valueText, string tagText, string refText);

private:
    Fixed screen;
    Button runButton,debugButton,stopButton,stepButton;
    ScrolledWindow codeEntryScroll,stdOutScroll,logViewScroll,ramViewScroll;
    TextView codeEntry,stdOut,logView,valueRamView,dirRamView,tagRamView,refRamView;
    Grid ramView;
    Label dirRamLabel,valueRamLabel,tagRamLabel,refRamLabel;

    void run();
    void debug();
    void stop();
    void step();
};


#endif //PROYECTO_1_DATOS_2_CODEEDITOR_H
