#include "Procesador.hh"
#include "Proceso.hh"

#include <string>
#include <list>
#include <iostream>

using namespace std;

Procesador::Procesador() {}

Procesador::Procesador(const string& id_procesador, int memoria) {
    this->id = id_procesador;
    this->memoria = memoria;
}

string Procesador::consultar_id() const {
    return id;
}

bool Procesador::id_coincide(const string& id_procesador) const {
    return id == id_procesador;
}

bool Procesador::existe_id_proceso(int id_proceso) const {
    for (list<pair<int, Proceso>>::const_iterator it = procesos_memoria.begin(); it != procesos_memoria.end(); ++it)
        if (it->second.id_coincide(id_proceso)) return true;
    return false;
}

bool Procesador::hay_procesos() const {
    return procesos_memoria.empty();
}

bool Procesador::se_puede_colocar(const Proceso& proceso) const {
    return false; //implementar
}

void Procesador::avanzar_tiempo(int t) {
    list<pair<int, Proceso>>::iterator it = procesos_memoria.begin();
    while (it != procesos_memoria.end()) {
        if (it->second.avanzar_tiempo(t)) ++it;
        else it = procesos_memoria.erase(it);
    }
}

void Procesador::imprimir() const {
    for (list<pair<int, Proceso>>::const_iterator it = procesos_memoria.begin(); it != procesos_memoria.end(); ++it) {
        it->second.imprimir();
        cout << " " << it->first << ", ";
    }
    cout << endl;
}

void Procesador::compactar_memoria() {
    ;// implementar. tiene q ser muy eficiente.
}