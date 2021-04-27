//
// Created by pablo on 31/3/21.
//

#ifndef PROYECTO_1_DATOS_2_CODEEDITOR_H
#define PROYECTO_1_DATOS_2_CODEEDITOR_H

#include "../../ExternalLibraries/nlohmann/json.hpp"
#include "../MainWindow.h"
#include "../../ServerSocket/Client/Client.h"
using json = nlohmann::json;
using namespace std;

//! @brief Clase encargada de manejar el editor de código, hereda de la clase Window para manejarla directamente como una ventana de gtkmm.
class CodeEditor : public Window {

public:
    CodeEditor() ;
    ~CodeEditor();

    //!  @brief Este método se utiliza para obtener el texto de la entrada de texto de código.
    //!  @return un string con el texto que hay en el cuadro de texto.
    string getCodeEntryText();

    //! @brief Se utiliza para agregar texto al stdOut del IDE.
    //! @param text debe ser un string con el texto que se desea agregar.
    void setSTDOutText(string text);

    //! @brief Agrega texto a al cuadro de texto del Logger.
    //! @param text texto en forma de string que se desea agregar al log
    void setLogText(string text);

    //! @brief Con este se agrega texto a las diferentes columnas del visualizador de memoria del IDE.
    //! @param dirText dirección de memoria a agregar en forma de string
    //! @param valueText valor de la variable en forma de string
    //! @param tagText etiqueta de la variable a agregar en forma de string
    //! @param refText conteo de referencias de la variable en forma de string
    void setRamText(string dirText, string valueText, string tagText, string refText);

private:
    Fixed screen;
    Button runButton,debugButton,stopButton,stepButton, clearAllButton;
    ScrolledWindow codeEntryScroll,stdOutScroll,logViewScroll,ramViewScroll;
    TextView codeEntry,stdOut,logView,valueRamView,dirRamView,tagRamView,refRamView;
    Grid ramView;
    Label dirRamLabel,valueRamLabel,tagRamLabel,refRamLabel;

    Client client;

    /*! @brief Método llamado por el botón Run, envía por sockets el texto que obtiene desde la entrada de texto para
     * código del IDE, como resultado obtiene inData, que es el resultado procesado por el servidor en forma de string,
     * el cual luego lo envía el método jsonInterpreter(), que toma este string y lo convierte a un json para facilitar
     * su lectura.
    */
    void run();
    //! @brief Cambia a true el valor de la variable debugMode, para poder hacer uso de este modo.
    void debug();

    /*! @brief Detiene el modo debug cambiando el valor de la variable debugMode a false, limpiando las ventanas del IDE y
    * limpiando el json del debug.
    */
    void stop();

    /*! @brief Va avanzando paso a paso las líneas del código, así se puede observar que va agregando cada línea a las
    * diferentes ventanas informativas de memoria, stdOut y log.
    */
    void step();

    /*! @brief Elimina el texto de los diferentes cuadros de texto del IDE.
    */
    void clearAll();

    /*! @brief Se encarga de interpretar el json que viene del servidor, este viene en forma de string y lo pasa a json
    * para luego ir agregando, mediante un bucle toda la información de cada línea.
    * @param inData string con el json que da como resultado el servidor.
    */
    void jsonInterpreter(string inData);

    bool debugMode = false;
    int debugLineCounter = 0;
    json jsonDebug;
};

#endif //PROYECTO_1_DATOS_2_CODEEDITOR_H
