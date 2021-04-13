//
// Created by anthony on 1/4/21.
//

#include "LineReader.h"

LineReader::LineReader(MemoryLayout *mgmt, OutputManager * output) {
    this->mgmt = mgmt;
    this->current = this->mgmt->head;
    this->outmgmt = output;
}

bool LineReader::readLine(string line) {

    ///Hacer un boolean de error como atributo de clase
    ////Agregar el print

    //check basic syntax
    int count_l = 0;
    int position = 0;
    bool syntax_correct = true;
    bool only_lvl = false;
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
        check_at_last = line.substr(position+1);
    }

    for (int i=0; i<check_at_last.length(); i++){
        if (check_at_last[i] != ' ' && check_at_last[i] != '\n' && check_at_last[i] != '    '){
            cout << "Error, no debe de haber nada despues del punto y coma" << endl;
            syntax_correct = false;
        }
    }

    if (this->addingLevel(line)){
        only_lvl = true;
    }

    //type validation
    if (syntax_correct && !only_lvl) {
        string var_dec = "";
        int first = this->searchFirst(line);
        if (first != -1) {
            //Process declaration
            int position = this->processDeclaration(first, line);
            //Process assign
            this->processAssignment(position, line);
        }
    }

    this->mgmt->showRam();
    cout << "------------------------" << endl;

}

bool LineReader::addingLevel(string line) {
    bool cond1 = false;
    bool cond2 = false;
    for (int i = 0; i<line.length(); i++){
        if (line[i] != ' ' || line[i] != '  ' || line[i] != '\n'){
            if (line[i] == '{'){
                cond1 = true;
            }else if (line[i] == '}'){
                cond2 = true;
            }
            else if (cond1 || cond2 && (line[i] == '{' || line[i] == '}')){
                cout << "Error, no se permite este tipo de declaracion" << endl;
                break;
            }
        }
    }
    if (cond1){
        this->current = this->mgmt->addLevel();
    }else if (cond2){
        int cur_lvl = this->current->lvl;
        this->mgmt->deleteLevel(this->current->lvl);
        this->current = this->mgmt->getLevel(cur_lvl-1);
    }
    return cond1||cond2;
}


int LineReader::searchFirst(string cut) {
    int first = -1;
    for (int i = 0; i < cut.length(); i++) {
        if (cut[i] != '    ' && cut[i] != ';' && cut[i] != '\n' && cut[i] != ' ' && isalpha(cut[i]) ) {
            first = i;
            break;
        }
    }
    cout << "Primer caracter en: " << first << endl;
    return first;

}

int LineReader::processDeclaration(int first, string line) {

    string ident = "";
    bool found = false;
    int end_of_var = 0;
    string type_found = "";

    if (line.substr(first, 3) == "int"){
        found = true;
        cout << "Int encontrado! " << endl;
        end_of_var = this->searchFirst(line.substr(first+4));
        cout << "resto de la linea: " << line.substr(first+4) << endl;
        ident = this->searchIdent(0, line.substr(first+4));
        type_found = "int";

    }else if (line.substr(first, 5) == "float" ){
        found = true;
        end_of_var = this->searchFirst(line.substr(6));
        ident = this->searchIdent(end_of_var, line);
        type_found = "float";

    }else if (line.substr(first, 4) == "char" || line.substr(first, 4) == "long"){
        found = true;
        end_of_var = this->searchFirst(line.substr(5));
        ident = this->searchIdent(end_of_var, line);
        type_found = line.substr(first, 4);

    }else if (line.substr(first, 6) == "double"){
        found = true;
        end_of_var = this->searchFirst(line.substr(7));
        ident = this->searchIdent(end_of_var, line);
        type_found = "double";
    }

    if (found){
        cout << "into declaration" << endl;
        cout << "level: " << this->current->getLvL() << endl;
        int check_on_lvl = this->mgmt->checkOnLevel(this->current->getLvL(), ident);
        cout << "Valor de check: " << check_on_lvl << endl;
        if (check_on_lvl != -1){
            cout << "Error, el identificador ya esta asociado a una variable" << endl;
            return 0;
        }
        else{
            int spaces = 0;
            if (type_found == "int"){
                spaces = 4;
                int ref = 0;
                this->current->addVar(ident, ref);
                cout << "Int encontrado2 ! " << endl;
            }else if (type_found == "float"){
                spaces = 6;
                float ref = 0.0;
                this->current->addVar(ident, ref);
            }else if (type_found == "char") {
                spaces = 5;
                char ref = '0';
                this->current->addVar(ident, ref);
            }else if (type_found == "long") {
                spaces = 5;
                long ref = 0;
                this->current->addVar(ident, ref);
            }else if (type_found == "double"){
                spaces = 7;
                double ref = 0.0;
                this->current->addVar(ident, ref);
            }
            this->mgmt->showRam();
            return spaces+first;
        }

    }else{
        return 0;
    }


}

string LineReader::searchIdent(int first, string line) {
    string to_check = line;
    int end_id = 0;
    bool found_first = false;
    for (int i=0; i<to_check.length(); i++){
        if ((!isalpha(to_check[i]) && !isdigit(to_check[i])) && found_first){
            end_id = i;
            break;
        }else if(isalpha(to_check[i]) && !found_first){
            found_first = true;
        }
    }
    cout << "Identificador: ///" << to_check.substr(first, end_id) << "////" << endl;
    return to_check.substr(first, end_id);
}

string LineReader::searchAssign(string line) {
    bool start = false, got_first = false;
    string assign_value = "";
    for (int i=0; i<line.length(); i++){
        if (line[i] == '=' && !start){
            start = true;
        }else if(start && line[i] == '='){
            cout << "Error, no se permite esta operacion" << endl;
        }else if(start && (isalpha(line[i]) || line[i] == '.' || isdigit(line[i]))){
            if (!got_first){
                got_first = true;
            }
            assign_value += line[i];
        }
        else if(start && got_first && line[i] == ' ' && line[i] == '   '){
            start = false;
        }
        else if(!start && got_first && (isalpha(line[i]) || line[i] == '.' || isdigit(line[i]))){
            cout << "Error, no deberia de separar esa seccion" << endl;
        }

    }
    cout << "Valor de asignacion: " << assign_value << endl;
    return assign_value;
}

void LineReader::processAssignment(int first, string line) {
    cout << "Asignacion\nLinea evaluada: " << line << endl;
    cout << "Evaluada desde: " << line[first] << endl;
    string ident = this->searchIdent(0, line.substr(first));
    if (this->mgmt->checkOnLevel(this->current->lvl, ident) != -1){

        int lvl_found = this->mgmt->checkOnLevel(this->current->lvl, ident);
        string assign_obj = this->searchAssign(line);
        MemoryManager * c_level = this->mgmt->getLevel(lvl_found);
        cout << "Objeto de asignacion: " << assign_obj << endl;
        if (assign_obj != ""){

            if (this->mgmt->checkOnLevel(this->current->lvl, assign_obj) != -1){
                cout << "Paso 1" << endl;

                int level_found = this->mgmt->checkOnLevel(this->current->lvl, assign_obj);
                cout << "Paso 2" << endl;
                MemoryManager * m_level = this->mgmt->getLevel(level_found);
                cout << "Paso 3" << endl;

                if (c_level->getType(ident) == m_level->getType(assign_obj)){
                    if (c_level->getType(ident) == "int"){
                        cout << "paso 5"<< endl;
                        int * data = m_level->getValue<int>(assign_obj);
                        cout << "paso 6";
                        c_level->updateVar(ident, &data);

                    }
                    else if (c_level->getType(ident) == "float"){
                        c_level->updateVar(ident, m_level->getValue<float>(assign_obj));
                    }
                    else if(c_level->getType(ident) == "long"){
                        c_level->updateVar(ident, m_level->getValue<long>(assign_obj));
                    }
                    else if (c_level->getType(ident) == "char"){
                        c_level->updateVar(ident, m_level->getValue<char>(assign_obj));
                    }
                    else if (c_level->getType(ident) == "double"){
                        c_level->updateVar(ident, m_level->getValue<double>(assign_obj));
                    }
                }else{
                    cout << "Error, las variables no son del mismo tipo" << endl;
                }
            }else{
                string type = c_level->getType(ident);
                if (type == "int"){
                    if (typeid(int) == typeid(stoi(assign_obj))){
                        int result = stoi(assign_obj);
                        c_level->updateVar(ident, &result);
                    }else{
                        cout << "Error, tipo de dato erroneo" << endl;
                    }
                }else if (type == "float"){
                    if (typeid(float ) == typeid(stof(assign_obj))){
                        float result = stof(assign_obj);
                        c_level->updateVar(ident, &result);
                    }else{
                        cout << "Error, tipo de dato erroneo" << endl;
                    }
                }else if (type == "long"){
                    if (typeid(long) == typeid(stol(assign_obj))){
                        long result = stol(assign_obj);
                        c_level->updateVar(ident, &result);
                    }else{
                        cout << "Error, tipo de dato erroneo" << endl;
                    }
                }else if (type == "double"){
                    if (typeid(double ) == typeid(stod(assign_obj))){
                        double result = stod(assign_obj);
                        c_level->updateVar(ident, &result);
                    }else{
                        cout << "Error, tipo de dato erroneo" << endl;
                    }
                }else if (type == "char"){
                    if (typeid(char ) == typeid(assign_obj[0])){
                        char result = assign_obj[0];
                        c_level->updateVar(ident, &result);
                    }else{
                        cout << "Error, tipo de dato erroneo" << endl;
                    }
                }
            }
        }else{
            cout << "Error, no existe una asignacion" << endl;
        }
    }

}