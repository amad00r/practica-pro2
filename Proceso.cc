#include "Proceso.hh"

using namespace std;

Proceso::Proceso() {}

Proceso::Proceso(int id, int memoria, int tiempo_ejecucion) {
    this->id = id;
    this->memoria = memoria;
    this->tiempo_ejecucion = tiempo_ejecucion;
}

int Proceso::consultar_id() const {
    return id;
}

bool Proceso::id_coincide(int id_proceso) const {
    return id == id_proceso;
}

bool Proceso::queda_tiempo_ejecucion(int t) const {
    return tiempo_ejecucion > t;
}

void Proceso::avanzar_tiempo(int t) {
    tiempo_ejecucion -= t;
}

void Proceso::imprimir() const {
    cout << id << " " << memoria << " " << tiempo_ejecucion << endl;
}