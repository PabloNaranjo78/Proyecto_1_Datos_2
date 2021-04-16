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
    set_icon_from_file("../Images/Ico.png");

//    cout<<codeEntry.get_buffer()->get_text(); así se le saca el texto

    runButton.add_pixlabel("info.xpm","Run");
    debugButton.add_pixlabel("info.xpm","Debug");
    stopButton.add_pixlabel("info.xpm","Stop");
    stepButton.add_pixlabel("info.xpm","Step");

    runButton.signal_clicked().connect([this]{this->run();});
    debugButton.signal_clicked().connect([this]{this->debug();});
    stopButton.signal_clicked().connect([this]{this->stop();});
    stepButton.signal_clicked().connect([this]{this->step();});

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

    ramView.attach(dirRamView, 0, 1);
    ramView.attach(dirRamLabel, 0, 0);

    ramView.attach(valueRamView, 1, 1);
    ramView.attach(valueRamLabel,1,0);

    ramView.attach(tagRamView,2,1);
    ramView.attach(tagRamLabel,2,0);

    ramView.attach(refRamView,3,1);
    ramView.attach(refRamLabel,3,0);

    valueRamView.set_size_request(112, 400);
    dirRamView.set_size_request(112,400);
    tagRamView.set_size_request(112, 400);
    refRamView.set_size_request(112,400);

    valueRamView.set_editable(false);
    dirRamView.set_editable(false);
    tagRamView.set_editable(false);
    refRamView.set_editable(false);

    valueRamLabel.set_text("Valor");
    dirRamLabel.set_text("Dirección");
    tagRamLabel.set_text("Etiqueta");
    refRamLabel.set_text("Referencias");

    ramView.set_size_request(450, 420);
    ramViewScroll.set_size_request(450,420);
    ramViewScroll.property_vscrollbar_policy();

    ramViewScroll.add(ramView);
    screen.put(ramViewScroll,910,21);

    stdOut.get_buffer()->set_text(">> ");
    codeEntry.get_buffer()->set_text("Un poco de código......");

    setRamText("0x7ffc736300d8","500","num","2");
    setRamText("0x7ffc736300d8","500","num","2");

    logView.get_buffer()->set_text("<Log>");

    show_all_children();

}

CodeEditor::~CodeEditor() {
}

string CodeEditor::getCodeEntryText() {
    return codeEntry.get_buffer()->get_text();
}

void CodeEditor::setSTDOutText(string text) {
    string temp;
    temp = stdOut.get_buffer()->get_text();
    if (stdOut.get_buffer()->get_text() == ">>"){
        temp+= text+"\n";
        stdOut.get_buffer()->set_text(temp);
    }else{
        temp+=">> "+text+"\n";
        stdOut.get_buffer()->set_text(temp);
    }
}

void CodeEditor::setLogText(string text) {
    string temp;
    temp = logView.get_buffer()->get_text();
    if (logView.get_buffer()->get_text() == "<Log>"){
        temp+= " "+text+"\n";
        logView.get_buffer()->set_text(temp);
    }else{
        temp+=">> "+text+"\n";
        logView.get_buffer()->set_text(temp);
    }
}

void CodeEditor::setRamText(string dirText, string valueText, string tagText, string refText) {


    dirRamView.get_buffer()->set_text(dirRamView.get_buffer()->get_text()+"\n"+dirText);
    valueRamView.get_buffer()->set_text(valueRamView.get_buffer()->get_text()+"\n"+valueText);
    tagRamView.get_buffer()->set_text(tagRamView.get_buffer()->get_text()+"\n"+tagText);
    refRamView.get_buffer()->set_text(refRamView.get_buffer()->get_text()+"\n"+refText);

}

void CodeEditor::run() {

}

void CodeEditor::debug() {

}

void CodeEditor::stop() {

}

void CodeEditor::step() {

}
