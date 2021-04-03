//
// Created by anthony on 1/4/21.
//

#include "LineReader.h"


string LineReader::readLine(string line, MemoryManager memMgmt) {
    //check basic syntax
    int count_l = 0;
    int position = 0;
    bool syntax_correct = true;
    for (int i=0; i<line.length(); i++){
        if (line[i] == ';'){
            count_l++;
            position = i;
            if (count_l > 1){
                cout << "Error, no puede haber mas de un punto y coma por linea" << endl;
                syntax_correct = false;
                break;
            }
        }
    }
    string check_at_last = "";
    if (count_l == 0){
        cout << "Error, falta un punto y coma" << endl;
        syntax_correct = false;

    }else{
        check_at_last = line.substr(position);
    }

    for (int i=0; i<check_at_last.length(); i++){
        if (check_at_last[i] != ' ' && check_at_last[i] != '\n' && check_at_last[i] != '    '){
            cout << "Error, no debe de haber nada despues del punto y coma" << endl;
            syntax_correct = false;
        }
    }


    //type validation
    if (syntax_correct) {
        string var_dec = "";
        int first = this->searchFirst(line);
        if (this->processDeclaration(first, line, memMgmt)){

        }
    }

}


int LineReader::searchFirst(string cut) {
    int first = 0;
    for (int i = 0; i < cut.length(); i++) {
        if (cut[i] != '    ' && cut[i] != ';' && cut[i] != '\n' && vut[i] != ' ') {
            first = i;
            break;
        }
    }
    return first;

}

bool LineReader::processDeclaration(int first, string line, MemoryManager mgmt) {
    string ident = "";
    bool found = false;
    string type_found = "";
    if (line.substr(first, 3) == "int"){
        found = true;
        int first = this->searchFirst(line.substr(3));
        ident = this->searchIdent(first, line);
        type_found = "int";

    }else if (line.substr(first, 5) == "float" ){
        found = true;
        int first = this->searchFirst(line.substr(5));
        ident = this->searchIdent(first, line);
        type_found = "float";

    }else if (line.substr(first, 4) == "char" || line.substr(first, 4) == "long"){
        found = true;
        int first = this->searchFirst(line.substr(4));
        ident = this->searchIdent(first, line);
        type_found = line.substr(first, 4);

    }else if (line.substr(first, 6) == "double"){
        found = true;
        int first = this->searchFirst(line.substr(6));
        ident = this->searchIdent(first, line);
        type_found = "double";
    }

    if (found){
        if (mgmt.isInMemory(ident)){
            cout << "Error, el identificador ya esta asociado a una variable" << endl;
        }else{
            if (type_found == "int"){
                mgmt.addVar(ident, 0);
            }else if (type_found == "float"){
                mgmt.addVar(ident, 0.0);
            }else if (type_found == "char") {
                mgmt.addVar(ident, '0');
            }else if (type_found == "long") {
                mgmt.addVar(ident, 0);
            }else if (type_found == "double"){
                mgmt.addVar(ident, 0.00);
            }
        }
    }

    return found;

}

string LineReader::searchIdent(int first, string line) {
    string to_check = line.substr(first);
    int end_id = 0;
    for (int i=0; i<to_check.length(); i++){
        if (to_check[i] == ' ' || to_check[i] == '=' || to_check[i] == '    '){
            end_id = i;
        }
    }
    return to_check.substr(0, end_id);
}