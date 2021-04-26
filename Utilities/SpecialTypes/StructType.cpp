//
// Created by anthony on 17/4/21.
//

#include "StructType.h"

StructType::StructType() {
    this->head = NULL;
}


void StructType::addType(string ident) {

    if (this->head == NULL){
        this->head = new Struct();
        this->head->type_ident = ident;
    }else{
        Struct * tmp = this->head;
        while (tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = new Struct();
        tmp->type_ident = ident;
    }
    cout << "Agregado nuevo struct: " << ident << endl;
}

void StructType::addToType(string idType, string varType, string varName) {
    Struct * tmp = this->head;
    cout << tmp->type_ident << " Ident head" << endl;
    cout << idType << " Ident recibido" << endl;

    while (tmp != NULL){
        if (tmp->type_ident == idType){
            cout << "Agregando un nuevo parametro" << endl;
            tmp->scheme->add(varName, varType, false);
            break;
        }
        tmp = tmp->next;
    }
    cout << "Agregando un nuevo parametro 2" << endl;
}

bool StructType::isIn(string idType) {
    Struct * tmp = this->head;
    bool result = false;
    while (tmp != NULL){
        if (tmp->type_ident == idType){
            result = true;
            break;
        }
        tmp = tmp->next;
    }
    return result;
}

void StructType::createInstance(string idT,string instName ,MemoryManager * manager) {
    Struct * tmp = this->head;
    this->showValues(idT);
    while (tmp != NULL){
        if (tmp->type_ident == idT){
            Node<string> * tmp_i = tmp->scheme->head;
            if (tmp_i->data == "int"){
                cout << "paso 1" << endl;
                int ref = 0;
                manager->addVar(instName, ref, true);
                cout << "paso 2" << endl;
            }else if (tmp_i->data == "float"){
                float ref = 0.0;
                manager->addVar(instName, ref, true);
            }else if (tmp_i->data == "char"){
                char ref = '0';
                manager->addVar(instName, ref, true);
            }else if (tmp_i->data == "long") {
                long ref = 0;
                manager->addVar(instName, ref, true);
            }else if (tmp_i->data == "double"){
                double ref = 0.0;
                manager->addVar(instName, ref, true);
            }
            manager->add_reference(instName, manager->getLvL());

            while (tmp_i != NULL){
                if (tmp_i->data == "int"){
                    cout << "Int found to struct" << endl;
                    int ref = 0;
                    manager->addVar(instName+"."+tmp_i->identifier, ref, false);
                    manager->add_reference(instName+"."+tmp_i->identifier, manager->getLvL());
                }else if (tmp_i->data == "float"){
                    float ref = 0.0;
                    manager->addVar(instName+"."+tmp_i->identifier, ref, false);
                    manager->add_reference(instName+"."+tmp_i->identifier, manager->getLvL());
                }else if (tmp_i->data == "char"){
                    char ref = '0';
                    manager->addVar(instName+"."+tmp_i->identifier, ref, false);
                    manager->add_reference(instName+"."+tmp_i->identifier, manager->getLvL());
                }else if (tmp_i->data == "long") {
                    long ref = 0;
                    manager->addVar(instName+"."+tmp_i->identifier, ref, false);
                    manager->add_reference(instName+"."+tmp_i->identifier, manager->getLvL());
                }else if (tmp_i->data == "double"){
                    double ref = 0.0;
                    manager->addVar(instName+"."+tmp_i->identifier, ref, false);
                    manager->add_reference(instName+"."+tmp_i->identifier, manager->getLvL());
                }
                tmp_i = tmp_i->next;
            }

        }
        tmp = tmp->next;
    }
}

void StructType::showValues(string idT) {
    Struct * tmp = this->head;
    while (tmp != NULL) {
        if (tmp->type_ident == idT) {
            Node<string> *tmp_i = tmp->scheme->head;
            while (tmp_i != NULL){
                cout << "Type: "<< tmp_i->data << "Identifier: "<< tmp_i->identifier << endl;
                tmp_i = tmp_i->next;
            }
        }
        tmp = tmp->next;
    }
}