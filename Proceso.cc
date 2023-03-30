#include "Proceso.hh"

using namespace std;

Proceso::Proceso() {}

Proceso::Proceso(unsigned int id, unsigned int memoria, unsigned int tiempo_ejecucion) {
    this->id = id;
    this->memoria = memoria;
    this->tiempo_ejecucion = tiempo_ejecucion;
}

unsigned int Proceso::consultar_id() const {
    return id;
}

bool Proceso::id_coincide(unsigned int id_proceso) const {
    return id == id_proceso;
}

bool Proceso::queda_tiempo_ejecucion(unsigned int t) const {
    return tiempo_ejecucion > t;
}

void Proceso::avanzar_tiempo(unsigned int t) {
    tiempo_ejecucion -= t;
}

void Proceso::imprimir() const {
    cout << id << " " << memoria << " " << tiempo_ejecucion << endl;
}