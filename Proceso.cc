/** @file Proceso.cc
    @brief implementación de la clase Proceso.
*/

#include "Proceso.hh"

using namespace std;

Proceso::Proceso() {}

Proceso::Proceso(int id, int memoria, int tiempo_estimado) {
    this->id = id;
    this->memoria = memoria;
    this->tiempo_estimado = tiempo_estimado;
}

int Proceso::consultar_id() const {
    return id;
}

int Proceso::consultar_memoria() const {
    return memoria;
}

bool Proceso::avanzar_tiempo(int t) {
    tiempo_estimado -= t;
    return tiempo_estimado > 0;
}

void Proceso::imprimir() const {
    cout << id << " " << memoria << " " << tiempo_estimado << endl;
}