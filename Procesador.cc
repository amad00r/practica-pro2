#include "Procesador.hh"
#include "Proceso.hh"
#include <string>
#include <list>

#include "Errores.hh" ///////////////////////////?¿?? hace falta

using namespace std;

Procesador::Procesador() {}

Procesador::Procesador(const string& id_procesador, int memoria) {
    this->id_procesador = id_procesador;
    this->memoria = memoria;
}

bool Procesador::id_coincide(const string& id_procesador) {
    return id == id_procesador;
}

bool Procesador::existe_id_proceso(int id_proceso) {
    for (list<Proceso>::const_iterator it = procesos_memoria.begin(); it != procesos_memoria.end(); ++it)
        if (it->id_coincide(id_proceso)) return true;
    return false;
}

bool Procesador::hay_procesos() {
    return procesos_memoria.empty();
}

bool Procesador::se_puede_colocar(const Proceso& proceso) {
    ; //implementar
}

void Procesador::avanzar_tiempo(int t) {
    list<Proceso>::const_iterator it = procesos_memoria.begin();
    while (it != procesos_memoria.end()) {
        if (it->second.avanzar_tiempo(t)) ++it;
        else it = procesos_memoria.erase(it);
    }
}

void Procesador::imprimir() const {
    for (list<Proceso>::const_iterator it = procesos_memoria.begin(); it != procesos_memoria.end(); ++it) {
        it->second.imprimir();
        cout << " " << it->first << ", ";
    }
    cout << endl;
}

void Procesador::compactar_memoria() {
    ;// implementar. tiene q ser muy eficiente.
}