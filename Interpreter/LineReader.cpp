//
// Created by anthony on 1/4/21.
//

#include "LineReader.h"
#include "../ExternalLibraries/nlohmann/json.hpp"
using json = nlohmann::json;

LineReader::LineReader(MemoryLayout *mgmt, OutputManager * output) {
    this->mgmt = mgmt;
    this->current = this->mgmt->head;
    this->outmgmt = output;
    this->to_assign = new MemoryManager(0);
}

string LineReader::readLine(string line) {

    //Hacer un boolean de error como atributo de clase
    //Agregar el print

    //check basic syntax
    int count_l = 0;
    int position = 0;
    bool syntax_correct = true;
    bool only_lvl = false;
    bool void_line = true;
    cout << "Nivel del current: " << this->current->lvl << endl;
    cout << "entre aca" << endl;

    if (this->checkForStruct(line)){
        this->mgmt->structManager->addType(this->currentStructType);
    }else{
        for (int i=0; i<line.length(); i++){
            if (isalpha(line[i])){
                void_line = false;
                break;
            }
        }
        if (void_line){
            cout << "Linea vacia" << endl;
        }
        cout << "entre aca 2" << endl;
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

        cout << "entre aca 3" << endl;
        string check_at_last = "";

        if (count_l == 0 && !void_line){
            cout << "Error, falta un punto y coma" << endl;
            syntax_correct = false;

        }else if (!void_line){
            check_at_last = line.substr(position+1);
        }

        cout << "entre aca 4" << endl;
        if (!void_line) {
            for (int i = 0; i < check_at_last.length(); i++) {
                if (check_at_last[i] != ' ' && check_at_last[i] != '\n' && check_at_last[i] != '    ') {
                    cout << "Error, no debe de haber nada despues del punto y coma" << endl;
                    syntax_correct = false;
                }
            }
        }
        if (this->addingLevel(line)){
            only_lvl = true;
        }

        //type validation
        if (syntax_correct && !only_lvl && !void_line) {
            string var_dec = "";
            int first = this->searchFirst(line);
            if (first != -1) {
                //Process functions
                bool hasFunct = this->processFunction(first, line);
                //Process declaration
                if (!hasFunct){
                    int position = this->processDeclaration(first, line);
                    //Process assign
                    if (position != 0){
                        this->processAssignment(position, line);
                    }else{
                        this->processAssignment(first, line);
                    }
                }
            }
        }
    }

    string result = this->mgmt->showRam();
    cout << "------------------------" << endl;
    return result;

}

bool LineReader::checkForStruct(string cut) {
    int first = this->searchFirst(cut);
    if (first != -1 && cut.substr(first, 6) == "struct"){
        cout << "Has struct" << endl;
        this->currentStructType = this->searchIdent(first+7, cut);
        cout << "Nombre del tipo: //" << this->currentStructType << "//" << endl;
        this->intoStruct = true;
        return true;
    }
    return false;
}

bool LineReader::addingLevel(string line) {
    bool cond1 = false;
    bool cond2 = false;
    cout << "Checking adding level" << endl;
    for (int i = 0; i<line.length(); i++){
        if (line[i] != ' ' || line[i] != '  ' || line[i] != '\n'){
            if (line[i] == '{'){
                cond1 = true;
                cout << "Adding level or entering struct" << endl;
            }else if (line[i] == '}'){
                cond2 = true;
            }
            else if (cond1 || cond2 && (line[i] == '{' || line[i] == '}')){
                cout << "Error, no se permite este tipo de declaracion" << endl;
                break;
            }
        }
    }
    if (cond1 && !this->intoStruct){
        this->current = this->mgmt->addLevel();
    }else if (cond2 && !this->intoStruct){
        int cur_lvl = this->current->lvl;
        this->mgmt->deleteLevel(this->current->lvl);
        this->mgmt->delete_refs(cur_lvl);
        this->current = this->mgmt->getLevel(cur_lvl-1);
    }else if (cond2 && this->intoStruct){
        this->intoStruct = false;
    }
    return cond1||cond2;
}

bool LineReader::processFunction(int first, string line) {

    cout << "Procesando funcion" << endl;

    if (line.substr(first, 6) == "print("){
        string to_analize = line.substr(first+6);
        string to_print = "";
        bool correct_syntax = false;
        for (int i=0; i<to_analize.length(); i++){
            if (to_analize[i] == ')'){
                correct_syntax = true;
                break;
            }else{
                to_print += to_analize[i];
            }
        }
        cout << to_print << " Variable" << endl;
        if (correct_syntax){
            if (mgmt->checkOnLevel(this->current->getLvL(), to_print) != -1){
                int lvl_at = mgmt->checkOnLevel(this->current->getLvL(), to_print);
                MemoryManager * m_level = this->mgmt->getLevel(lvl_at);
                if (!m_level->isInit(to_print)){
                    cout << "Identificador: " << to_print << " Variable no inicializada" << endl;
                }else{
                    if (m_level->getType(to_print) == "int") {
                        cout << "Identificador: " << to_print << " Valor: " << m_level->getValue<int>(to_print) << endl;
                        //Llamar al output manager
                    }else if(m_level->getType(to_print) == "float") {
                        cout << "Identificador: " << to_print << " Valor: " << m_level->getValue<float>(to_print) << endl;
                    }else if(m_level->getType(to_print) == "char") {
                        cout << "Identificador: " << to_print << " Valor: " << m_level->getValue<char>(to_print) << endl;
                    }else if(m_level->getType(to_print) == "long") {
                        cout << "Identificador: " << to_print << " Valor: " << m_level->getValue<long>(to_print) << endl;
                    }else if(m_level->getType(to_print) == "double") {
                        cout << "Identificador: " << to_print << " Valor: " << m_level->getValue<double>(to_print) << endl;
                    }
                }
            }else{
                cout << to_print << endl;
            }
            return true;
        }else{
            cout << "Error, la sintaxis no es correcta" << endl;
        }

    }else if(line.substr(first, 11) == "getAddress("){

        string to_analize = line.substr(first+11);
        string to_address = "";
        bool correct_syntax = false;
        for (int i=0; i<to_analize.length(); i++){
            if (to_analize[i] == ')'){
                correct_syntax = true;
                break;
            }else{
                to_address += to_analize[i];
            }
        }
        cout << to_address << " Variable" << endl;
        if (correct_syntax){
            this->operation = false;
            if (mgmt->checkOnLevel(this->current->getLvL(), to_address) != -1){
                cout << "Se procesa obtener la direccion" << endl;
                int lvl_at = mgmt->checkOnLevel(this->current->getLvL(), to_address);
                MemoryManager * m_level = this->mgmt->getLevel(lvl_at);
                this->isRef = false;
                this->id_assign = to_address;
                cout << "Identificador: " << to_address << " Direccion: " << m_level->getAddress<int>(to_address) << endl;
                return true;

            }else{
                cout << "Error, no se encuentra el identificador" << endl;
            }
        }else{
            cout << "Error, la sintaxis no es correcta" << endl;
        }

    }else if(line.substr(first, 9) == "getValue("){
        string to_analize = line.substr(first+9);
        string to_value = "";
        bool correct_syntax = false;
        for (int i=0; i<to_analize.length(); i++){
            if (to_analize[i] == ')'){
                correct_syntax = true;
                break;
            }else{
                to_value += to_analize[i];
            }
        }
        cout << to_value << " Variable" << endl;
        if (correct_syntax){
            this->operation = true;
            if (mgmt->checkOnLevel(this->current->getLvL(), to_value) != -1){
                int lvl_at = mgmt->checkOnLevel(this->current->getLvL(), to_value);
                MemoryManager * m_level = this->mgmt->getLevel(lvl_at);
                if (m_level->isRef(to_value)) {
                    this->isRef = true;
                    this->id_assign = to_value;
                    cout << "Identificador: " << to_value << " Valor: " << m_level->getValue<int>(to_value) << endl;
                    return true;
                }else{
                    this->isRef = false;
                    this->id_assign = to_value;
                    cout << "Identificador: " << to_value << " Valor: " << m_level->getValue<int>(to_value) << endl;
                    return true;
                }
            }else{
                cout << "Error, no se encuentra el identificador" << endl;
            }
        }else{
            cout << "Error, la sintaxis no es correcta" << endl;
        }
    }else{
        return false;
    }
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
    string type_dec = "";
    int counter = 0;
    bool isRef = false;

    if (line.substr(first, 3) == "int"){
        found = true;
        cout << "Int encontrado! " << endl;
        end_of_var = this->searchFirst(line.substr(first+4));
        //cout << "resto de la linea: " << line.substr(first+4) << endl;
        ident = this->searchIdent(0, line.substr(first+4));
        type_found = "int";

    }else if (line.substr(first, 5) == "float" ){
        cout << "Float encontradp" << endl;
        found = true;
        ident = this->searchIdent(0, line.substr(first+6));
        type_found = "float";

    }else if (line.substr(first, 4) == "char" || line.substr(first, 4) == "long"){
        cout << "char/long encontradp" << endl;
        found = true;
        ident = this->searchIdent(0, line.substr(first+5));
        type_found = line.substr(first, 4);

    }else if (line.substr(first, 6) == "double"){
        cout << "double found" << endl;
        found = true;
        ident = this->searchIdent(0, line.substr(first+7));
        type_found = "double";
    }
    else if (line.substr(first, 9) == "reference"){
        cout << "reference found" << endl;
        if (line[first+9] == '<'){
            bool checking_type = false;
            string to_check = line.substr(first+10);
            string typeD = "";
            for (int i=0; i<to_check.length(); i++){
                if (to_check[i] == '>'){
                    type_dec = typeD;
                    checking_type = true;
                    break;
                }else {
                    counter++;
                    typeD += to_check[i];
                }
            }
            found = checking_type;
            isRef = true;
            cout << "type declare" << type_dec << endl;
            cout << "Identificador::::" << line.substr(first+12+counter) << endl;
            ident = this->searchIdent(0, line.substr(first+12+counter));
            type_found = type_dec;
        }
    }else{
        type_found = this->searchIdent(0, line);
        cout << "Struct type: //" << type_found << "//" << endl;
        if (this->mgmt->structManager->isIn(type_found)){
            found = true;
        }
        ident = this->searchIdent(0, line.substr(first+type_found.length()+1));
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
        else {
            cout << "HERE" << endl;
            int spaces = 0;
            if (type_found == "int") {
                cout << "Int inicializando" << endl;
                spaces = 4;
                int ref = 0;
                cout << "Nivel" << this->current->getLvL() << endl;
                if (!this->intoStruct){
                    this->current->addVar(ident, ref, isRef);
                    this->mgmt->count_reference(ident, this->current->getLvL());
                    cout << "Int encontrado2 ! " << endl;
                }else{
                    cout << "Agregando variable int a: " <<  this->currentStructType << endl;
                    this->mgmt->structManager->addToType(this->currentStructType, "int", ident);
                }

            } else if (type_found == "float") {
                spaces = 6;
                float ref = 0.0;
                if (!this->intoStruct){
                    this->current->addVar(ident, ref, isRef);
                    this->mgmt->count_reference(ident, this->current->getLvL());
                }else{
                    this->mgmt->structManager->addToType(this->currentStructType, "float", ident);
                }
            } else if (type_found == "char") {
                spaces = 5;
                char ref = '0';
                if (!this->intoStruct){
                    this->current->addVar(ident, ref, isRef);
                    this->mgmt->count_reference(ident, this->current->getLvL());
                }else{
                    this->mgmt->structManager->addToType(this->currentStructType, "char", ident);
                }
            } else if (type_found == "long") {
                spaces = 5;
                long ref = 0;
                if (!this->intoStruct){
                    this->current->addVar(ident, ref, isRef);
                    this->mgmt->count_reference(ident, this->current->getLvL());
                }else{
                    this->mgmt->structManager->addToType(this->currentStructType, "long", ident);
                }
            } else if (type_found == "double") {
                spaces = 7;
                double ref = 0.0;
                if (!this->intoStruct){
                    this->current->addVar(ident, ref, isRef);
                    this->mgmt->count_reference(ident, this->current->getLvL());
                }else{
                    this->mgmt->structManager->addToType(this->currentStructType, "double", ident);
                }

            } else if (this->mgmt->structManager->isIn(type_found)) {
                cout << "Found struct related type" << endl;
                spaces = type_found.length() + 1;
                this->mgmt->structManager->createInstance(type_found, ident, this->current);
            }
            this->mgmt->showRam();
            if (!isRef){
                return spaces + first;
            }else{
                return 12 + first + counter;
            }
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
        if ((!isalpha(to_check[i]) && !isdigit(to_check[i])) && found_first && !(to_check[i] == '.')){
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
        }else if(start && (isalpha(line[i]) || line[i] == '.' || isdigit(line[i])) || line[i] == '(' || line[i] == ')' || line[i] == '+' || line[i] == '-' || line[i] == '/' || line[i] == '*'){
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

int LineReader::checkOperation(string cut) {
    int hasOp = -1;
    for (int i=0; i<cut.length(); i++){
        if (cut[i] == '+' || cut[i] == '*' || cut[i] == '/' || cut[i] == '-'){
            hasOp = i;
            break;
        }
    }
    return hasOp;
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
            if (this->processFunction(0, assign_obj)){
                cout << "Operacion encontrada" << endl;
                if (c_level->isRef(ident)) {
                    cout << ident <<" Es referencia" << endl;
                }else{
                    cout << ident << " No es referencia" << endl;
                }
                if (c_level->isRef(ident) && !this->operation && !this->isRef){
                    cout << "Found getAddress" << endl;
                    if (c_level->getType(ident) == this->mgmt->getType(this->id_assign)){
                        if (c_level->getType(ident) == "int"){
                            int * dir = c_level->getAddress<int>(this->id_assign);
                            c_level->updateVar(ident, dir);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "long"){
                            long * dir = c_level->getAddress<long>(this->id_assign);
                            c_level->updateVar(ident, dir);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "char"){
                            char * dir = c_level->getAddress<char>(this->id_assign);
                            c_level->updateVar(ident, dir);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "double"){
                            double * dir = c_level->getAddress<double>(this->id_assign);
                            c_level->updateVar(ident, dir);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "float") {
                            float *dir = c_level->getAddress<float>(this->id_assign);
                            c_level->updateVar(ident, dir);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                    }else{
                        cout << "Error, no son del mismo tipo" <<endl;
                    }
                }else if (!c_level->isRef(ident) && this->operation && this->isRef){
                    if (c_level->getType(ident) == this->mgmt->getType(this->id_assign)){
                        if (c_level->getType(ident) == "int"){
                            int * value = c_level->getAddPoint<int>(this->id_assign);
                            c_level->updateVar(ident, value);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "long"){
                            long * value = c_level->getAddPoint<long>(this->id_assign);
                            c_level->updateVar(ident, value);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "char"){
                            char * value = c_level->getAddPoint<char>(this->id_assign);
                            c_level->updateVar(ident, value);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "double"){
                            double * value = c_level->getAddPoint<double>(this->id_assign);
                            c_level->updateVar(ident, value);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "float") {
                            float * value = c_level->getAddPoint<float>(this->id_assign);
                            c_level->updateVar(ident, value);
                            this->mgmt->count_reference(this->id_assign, this->current->getLvL());
                        }
                    }else{
                        cout << "Error, no son del mismo tipo" <<endl;
                    }
                }else{
                    cout << "Error, no es posible la operacion" << endl;
                }
            }
            else if (this->checkOperation(assign_obj) != -1){
                string assign_objs[2] = {assign_obj.substr(0,this->checkOperation(assign_obj)), assign_obj.substr(this->checkOperation(assign_obj)+1)};
                char operation = assign_obj[this->checkOperation(assign_obj)];
                cout << "Objeto de asignacion 1: //" << assign_objs[0] << "//" << endl;
                cout << "Objeto de asignacion 2: //" << assign_objs[1] << "//" << endl;
                bool isIdent[2] = {false, false};
                int levels_at[2] = {0,0};
                MemoryManager * ob1 = NULL;
                MemoryManager * ob2 = NULL;
                for (int i=0; i<2; i++){
                    if (this->mgmt->checkOnLevel(this->current->lvl, assign_objs[i]) != -1){
                        isIdent[i] = true;
                        levels_at[i] = this->mgmt->checkOnLevel(this->current->lvl, assign_objs[i]);
                        cout << "FOUND IN LVL " << levels_at[i]<<"posicion"<< i << endl;
                    }
                }
                if (isIdent[0]){
                    ob1 = this->mgmt->getLevel(levels_at[0]);
                    //ob1->showRAM();
                }
                if (isIdent[1]){
                    ob2 = this->mgmt->getLevel(levels_at[1]);
                    //ob1->showRAM();
                }

                if (c_level->getType(ident) == "int") {
                    cout << "Realizando operacion" << endl;
                    int result = 0;
                    if (operation == '+') {
                        cout << "Realizando suma" << endl;
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<int>(assign_objs[0]) + ob2->getValue<int>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<int>(assign_objs[0]) + stoi(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stoi(assign_objs[0]) + ob2->getValue<int>(assign_objs[1]);
                        } else {
                            result = stoi(assign_objs[0]) + stoi(assign_objs[1]);
                        }
                    } else if (operation == '-') {
                        cout << "Realizando resta" << endl;
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<int>(assign_objs[0]) - ob2->getValue<int>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            cout << "CASO 2 resta" << endl;
                            result = ob1->getValue<int>(assign_objs[0]) - stoi(assign_objs[1]);
                            cout << "resultado obtenido" << endl;
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stoi(assign_objs[0]) - ob2->getValue<int>(assign_objs[1]);
                        } else {
                            result = stoi(assign_objs[0]) - stoi(assign_objs[1]);
                        }
                    } else if (operation == '*') {
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<int>(assign_objs[0]) * ob2->getValue<int>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<int>(assign_objs[0]) * stoi(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stoi(assign_objs[0]) * ob2->getValue<int>(assign_objs[1]);
                        } else {
                            result = stoi(assign_objs[0]) * stoi(assign_objs[1]);
                        }
                    } else if (operation == '/') {
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<int>(assign_objs[0]) / ob2->getValue<int>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<int>(assign_objs[0]) / stoi(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stoi(assign_objs[0]) / ob2->getValue<int>(assign_objs[1]);
                        } else {
                            result = stoi(assign_objs[0]) / stoi(assign_objs[1]);
                        }
                    }
                    c_level->updateVar(ident, &result);
                }
                else if (c_level->getType(ident) == "float") {
                    float result = 0;
                    if (operation == '+') {
                        cout << "Realizando suma" << endl;
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<float>(assign_objs[0]) + ob2->getValue<float>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<float>(assign_objs[0]) + stof(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stof(assign_objs[0]) + ob2->getValue<float>(assign_objs[1]);
                        } else {
                            result = stof(assign_objs[0]) + stof(assign_objs[1]);
                        }
                    } else if (operation == '-') {
                        cout << "Realizando resta" << endl;
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<float>(assign_objs[0]) - ob2->getValue<float>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            cout << "CASO 2 resta" << endl;
                            result = ob1->getValue<float>(assign_objs[0]) - stof(assign_objs[1]);
                            cout << "resultado obtenido" << endl;
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stof(assign_objs[0]) - ob2->getValue<float>(assign_objs[1]);
                        } else {
                            result = stof(assign_objs[0]) - stof(assign_objs[1]);
                        }
                    } else if (operation == '*') {
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<float>(assign_objs[0]) * ob2->getValue<float>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<float>(assign_objs[0]) * stof(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stof(assign_objs[0]) * ob2->getValue<float>(assign_objs[1]);
                        } else {
                            result = stof(assign_objs[0]) * stof(assign_objs[1]);
                        }
                    } else if (operation == '/') {
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<float>(assign_objs[0]) / ob2->getValue<float>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<float>(assign_objs[0]) / stof(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stof(assign_objs[0]) / ob2->getValue<float>(assign_objs[1]);
                        } else {
                            result = stof(assign_objs[0]) / stof(assign_objs[1]);
                        }
                    }
                    c_level->updateVar(ident, &result);
                }
                else if (c_level->getType(ident) == "long") {
                    long result = 0;
                    if (operation == '+') {
                        cout << "Realizando suma" << endl;
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<long>(assign_objs[0]) + ob2->getValue<long>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<long>(assign_objs[0]) + stol(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stol(assign_objs[0]) + ob2->getValue<long>(assign_objs[1]);
                        } else {
                            result = stol(assign_objs[0]) + stol(assign_objs[1]);
                        }
                    } else if (operation == '-') {
                        cout << "Realizando resta" << endl;
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<long>(assign_objs[0]) - ob2->getValue<long>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            cout << "CASO 2 resta" << endl;
                            result = ob1->getValue<long>(assign_objs[0]) - stol(assign_objs[1]);
                            cout << "resultado obtenido" << endl;
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stol(assign_objs[0]) - ob2->getValue<long>(assign_objs[1]);
                        } else {
                            result = stol(assign_objs[0]) - stol(assign_objs[1]);
                        }
                    } else if (operation == '*') {
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<long>(assign_objs[0]) * ob2->getValue<long>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<long>(assign_objs[0]) * stol(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stol(assign_objs[0]) * ob2->getValue<long>(assign_objs[1]);
                        } else {
                            result = stol(assign_objs[0]) * stol(assign_objs[1]);
                        }
                    } else if (operation == '/') {
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<long>(assign_objs[0]) / ob2->getValue<long>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<long>(assign_objs[0]) / stol(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stol(assign_objs[0]) / ob2->getValue<long>(assign_objs[1]);
                        } else {
                            result = stol(assign_objs[0]) / stol(assign_objs[1]);
                        }
                    }
                    c_level->updateVar(ident, &result);
                }
                else if (c_level->getType(ident) == "double") {
                    double result = 0;
                    if (operation == '+') {
                        cout << "Realizando suma" << endl;
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<double>(assign_objs[0]) + ob2->getValue<double>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<double>(assign_objs[0]) + stod(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stod(assign_objs[0]) + ob2->getValue<double>(assign_objs[1]);
                        } else {
                            result = stod(assign_objs[0]) + stod(assign_objs[1]);
                        }
                    } else if (operation == '-') {
                        cout << "Realizando resta" << endl;
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<double>(assign_objs[0]) - ob2->getValue<double>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            cout << "CASO 2 resta" << endl;
                            result = ob1->getValue<double>(assign_objs[0]) - stod(assign_objs[1]);
                            cout << "resultado obtenido" << endl;
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stod(assign_objs[0]) - ob2->getValue<double>(assign_objs[1]);
                        } else {
                            result = stod(assign_objs[0]) - stod(assign_objs[1]);
                        }
                    } else if (operation == '*') {
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<double>(assign_objs[0]) * ob2->getValue<double>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<double>(assign_objs[0]) * stod(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stod(assign_objs[0]) * ob2->getValue<double>(assign_objs[1]);
                        } else {
                            result = stod(assign_objs[0]) * stod(assign_objs[1]);
                        }
                    } else if (operation == '/') {
                        if (isIdent[0] && isIdent[1]) {
                            result = ob1->getValue<double>(assign_objs[0]) / ob2->getValue<double>(assign_objs[1]);
                        } else if (isIdent[0] && !isIdent[1]) {
                            result = ob1->getValue<double>(assign_objs[0]) / stod(assign_objs[1]);
                        } else if (!isIdent[0] && isIdent[1]) {
                            result = stod(assign_objs[0]) / ob2->getValue<double>(assign_objs[1]);
                        } else {
                            result = stod(assign_objs[0]) / stod(assign_objs[1]);
                        }
                    }
                    c_level->updateVar(ident, &result);
                }
            }
            else if (this->mgmt->checkOnLevel(this->current->lvl, assign_obj) != -1){
                cout << "Paso 1" << endl;
                int level_found = this->mgmt->checkOnLevel(this->current->lvl, assign_obj);
                cout << "Paso 2" << endl;
                MemoryManager * m_level = this->mgmt->getLevel(level_found);
                cout << "Paso 3" << endl;

                if (c_level->getType(ident) == m_level->getType(assign_obj)){
                    try{
                        if (c_level->getType(ident) == "int"){
                            cout << "Paso 5: "<< assign_obj << endl;
                            int data = m_level->getValue<int>(assign_obj);
                            cout << "Paso 6" << endl;
                            cout << "Data: "<< data << endl;
                            c_level->updateVar(ident,&data);
                            this->mgmt->count_reference(assign_obj, this->current->getLvL());

                        }
                        else if (c_level->getType(ident) == "float"){
                            float data = m_level->getValue<float>(assign_obj);
                            c_level->updateVar(ident, &data);
                            this->mgmt->count_reference(assign_obj, this->current->getLvL());
                        }
                        else if(c_level->getType(ident) == "long"){
                            long data = m_level->getValue<long>(assign_obj);
                            c_level->updateVar(ident, &data);
                            this->mgmt->count_reference(assign_obj, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "char"){
                            char data = m_level->getValue<char>(assign_obj);
                            c_level->updateVar(ident, &data);
                            this->mgmt->count_reference(assign_obj, this->current->getLvL());
                        }
                        else if (c_level->getType(ident) == "double"){
                            double data = m_level->getValue<double>(assign_obj);
                            c_level->updateVar(ident, &data);
                            this->mgmt->count_reference(assign_obj, this->current->getLvL());
                        }
                    }catch (const std::exception &e){
                        cout << "Error, asignacion erronea" << endl;
                    }

                }else{
                    cout << "Error, las variables no son del mismo tipo" << endl;
                }
            }else {
                string type = c_level->getType(ident);
                try {
                    if (type == "int") {
                        cout << "" << endl;
                        if (typeid(int) == typeid(stoi(assign_obj))) {
                            int result = stoi(assign_obj);
                            c_level->updateVar(ident, &result);
                        } else {
                            cout << "Error, tipo de dato erroneo" << endl;
                        }
                    } else if (type == "float") {
                        if (typeid(float) == typeid(stof(assign_obj))) {
                            float result = stof(assign_obj);
                            c_level->updateVar(ident, &result);
                        } else {
                            cout << "Error, tipo de dato erroneo" << endl;
                        }
                    } else if (type == "long") {
                        if (typeid(long) == typeid(stol(assign_obj))) {
                            long result = stol(assign_obj);
                            c_level->updateVar(ident, &result);
                        } else {
                            cout << "Error, tipo de dato erroneo" << endl;
                        }
                    } else if (type == "double") {
                        if (typeid(double) == typeid(stod(assign_obj))) {
                            double result = stod(assign_obj);
                            c_level->updateVar(ident, &result);
                        } else {
                            cout << "Error, tipo de dato erroneo" << endl;
                        }
                    } else if (type == "char") {
                        if (typeid(char) == typeid(assign_obj[0])) {
                            char result = assign_obj[0];
                            c_level->updateVar(ident, &result);
                        } else {
                            cout << "Error, tipo de dato erroneo" << endl;
                        }
                    }
                } catch (const std::exception &e) {
                    cout << "Error, asignacion incorrecta" << endl;
                }
            }
        }else{
            cout << "No existe una asignacion" << endl;
        }
    }
}