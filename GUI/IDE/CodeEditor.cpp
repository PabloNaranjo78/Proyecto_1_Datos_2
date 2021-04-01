//
// Created by pablo on 31/3/21.
//

#include <iostream>
#include "CodeEditor.h"
using namespace std;

CodeEditor::CodeEditor() {
    set_default_size(1360,700);
    set_title("C! IDE");
    set_resizable(false);
    add(screen);


//    cout<<codeEntry.get_buffer()->get_text(); así se le saca el texto

    runButton.add_pixlabel("info.xpm","Run");
    debugButton.add_pixlabel("info.xpm","Debug");
    stopButton.add_pixlabel("info.xpm","Stop");
    stepButton.add_pixlabel("info.xpm","Step");

    screen.put(runButton, 0, 0);
    screen.put(debugButton, 100, 0);
    screen.put(stopButton,180,0);
    screen.put(stepButton,245,0);

    codeEntry.set_size_request(900,400);
    codeEntry.set_resize_mode(RESIZE_IMMEDIATE);
    codeEntryScroll.set_size_request(900,400);
    codeEntryScroll.add(codeEntry);
    screen.put(codeEntryScroll, 5, 40);


    stdOut.set_size_request(900,100);
    stdOut.set_resize_mode(RESIZE_IMMEDIATE);
    stdOut.set_editable(false);
    stdOutScroll.set_size_request(900,100);
    stdOutScroll.add(stdOut);
    screen.put(stdOutScroll,5,445);


    logView.set_size_request(900,125);
    logView.set_resize_mode(RESIZE_IMMEDIATE);
    logView.set_editable(false);
    logViewScroll.set_size_request(900,125);
    logViewScroll.add(logView);
    screen.put(logViewScroll,5,550);

    ramView.set_size_request(450,400);
    ramView.set_resize_mode(RESIZE_IMMEDIATE);
  //  ramView.set_editable(false);
    ramViewScroll.set_size_request(450,400);
    ramViewScroll.add(ramView);
    screen.put(ramViewScroll,910,40);


    stdOut.get_buffer()->set_text(">>");
    codeEntry.get_buffer()->set_text("Code");
    ramView.get_buffer()->set_text("Ram");
    logView.get_buffer()->set_text("log->");
   show_all_children();


}



CodeEditor::~CodeEditor() {
}



