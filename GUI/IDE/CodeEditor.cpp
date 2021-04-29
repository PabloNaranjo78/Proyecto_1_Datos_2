//
// Created by pablo on 31/3/21.
//

#include <iostream>
#include "CodeEditor.h"
#include "../../ExternalLibraries/nlohmann/json.hpp"


using json = nlohmann::json;

using namespace std;
/***
 * @brief Genera la ventana del IDE, en esta se muestran diferentes campos de texto, el principal es la entrada de código
 * luego se encuentra un visualizador de memoria, un logger y una ventana para las impresiones del programa.
 */
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
    clearAllButton.add_pixlabel("info.xpm","Limpiar");

    runButton.signal_clicked().connect([this]{this->run();});
    debugButton.signal_clicked().connect([this]{this->debug();});
    stopButton.signal_clicked().connect([this]{this->stop();});
    stepButton.signal_clicked().connect([this]{this->step();});
    clearAllButton.signal_clicked().connect([this]{this->clearAll();});

    screen.put(runButton, 0, 0);
    screen.put(debugButton, 100, 0);
    screen.put(stopButton,180,0);
    screen.put(stepButton,245,0);
    screen.put(clearAllButton,345,0);

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


    logView.get_buffer()->set_text("<Log> ");

    show_all_children();

}

CodeEditor::~CodeEditor() {
    client.sendData("$#");
}

/***
 * Este método se utiliza para obtener el texto de la entrada de texto de código.
 * @return un string con el texto que hay en el cuadro de texto.
 */
string CodeEditor::getCodeEntryText() {
    return codeEntry.get_buffer()->get_text();
}

/***
 * Se utiliza para agregar texto al stdOut del IDE.
 * @param text debe ser un string con el texto que se desea agregar.
 */
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

/***
 * Agrega texto a al cuadro de texto del Logger.
 * @param text texto en forma de string que se desea agregar al log
 */
void CodeEditor::setLogText(string text) {
    string temp;
    temp = logView.get_buffer()->get_text();
    if (logView.get_buffer()->get_text() == "<Log>"){
        temp+= " "+text+"\n";
        logView.get_buffer()->set_text(temp);
    }else{
        temp+="<Log> "+text+"\n";
        logView.get_buffer()->set_text(temp);
    }
}
/***
 * Con este se agrega texto a las diferentes columnas del visualizador de memoria del IDE.
 * @param dirText dirección de memoria a agregar en forma de string
 * @param valueText valor de la variable en forma de string
 * @param tagText etiqueta de la variable a agregar en forma de string
 * @param refText conteo de referencias de la variable en forma de string
 */
void CodeEditor::setRamText(string dirText, string valueText, string tagText, string refText) {


    dirRamView.get_buffer()->set_text(dirRamView.get_buffer()->get_text()+"\n"+dirText);
    valueRamView.get_buffer()->set_text(valueRamView.get_buffer()->get_text()+"\n"+valueText);
    tagRamView.get_buffer()->set_text(tagRamView.get_buffer()->get_text()+"\n"+tagText);
    refRamView.get_buffer()->set_text(refRamView.get_buffer()->get_text()+"\n"+refText);

}

/***
 * Método llamado por el botón Run, envía por sockets el texto que obtiene desde la entrada de texto para
 * código del IDE, como resultado obtiene inData, que es el resultado procesado por el servidor en forma de string,
 * el cual luego lo envía el método jsonInterpreter(), que toma este string y lo convierte a un json para facilitar
 * su lectura.
 */
void CodeEditor::run() {
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    if (this->getCodeEntryText() != ""){
        string inData = client.sendData(this->getCodeEntryText());
        cout<<inData<<endl;
        jsonInterpreter(inData);
    }

}

/***
 * Cambia a true el valor de la variable debugMode, para poder hacer uso de este modo.
 */
void CodeEditor::debug() {
    debugMode = true;
    string inData = client.sendData(this->getCodeEntryText());
    jsonDebug = json::parse(inData);
}

/***
 * Detiene el modo debug cambiando el valor de la variable debugMode a false, limpiando las ventanas del IDE y
 * limpiando el json del debug.
 */
void CodeEditor::stop() {
    debugMode = false;
    clearAll();
    jsonDebug.clear();
    debugLineCounter = 0;
}

/***
 * Va avanzando paso a paso las líneas del código, así se puede observar que va agregando cada línea a las
 * diferentes ventanas informativas de memoria, stdOut y log.
 */
void CodeEditor::step() {
    if (debugMode and debugLineCounter <= jsonDebug.size()-1){

        dirRamView.get_buffer()->set_text(" ");
        valueRamView.get_buffer()->set_text(" ");
        tagRamView.get_buffer()->set_text(" ");
        refRamView.get_buffer()->set_text(" ");

        string inDataJsonString = jsonDebug[debugLineCounter];
        json inDataJson = json::parse(inDataJsonString);
        int counter= inDataJson["lineCounter"];
        for (int i = 0; i < counter;i++){

            setRamText(inDataJson["ramDir"][i],inDataJson["ramValue"][i],inDataJson["ramTag"][i],inDataJson["ramRef"][i]);
            setLogText(inDataJson["logText"][i]);
            setSTDOutText(inDataJson["stdOutText"][i]);

        }
       debugLineCounter++;
    }else{
        debugMode = false;
        debugLineCounter = 0;
    }
}

void CodeEditor::jsonInterpreter(string inData) {

    json inDataJsonAll = json::parse(inData);
    string inDataJsonString = inDataJsonAll[inDataJsonAll.size()-1];
    json inDataJson = json::parse(inDataJsonString);
    cout<<"eeee"<<endl;
    int counter= inDataJson["lineCounter"];

    dirRamView.get_buffer()->set_text(" ");
    valueRamView.get_buffer()->set_text(" ");
    tagRamView.get_buffer()->set_text(" ");
    refRamView.get_buffer()->set_text(" ");

    for (int i = 0; i < counter;i++){

        setRamText(inDataJson["ramDir"][i],inDataJson["ramValue"][i],inDataJson["ramTag"][i],inDataJson["ramRef"][i]);
        setLogText(inDataJson["logText"][i]);
        setSTDOutText(inDataJson["stdOutText"][i]);

    }

}

void CodeEditor::clearAll() {
    dirRamView.get_buffer()->set_text(" ");
    valueRamView.get_buffer()->set_text(" ");
    tagRamView.get_buffer()->set_text(" ");
    refRamView.get_buffer()->set_text(" ");
    stdOut.get_buffer()->set_text(">> ");
    logView.get_buffer()->set_text("<Log> ");

}
