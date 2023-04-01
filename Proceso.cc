#include "Proceso.hh"
#include "Errores.hh" ///////////////////////////?¿?? hace falta

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

bool Proceso::id_coincide(int id_proceso) const {
    return id == id_proceso;
}

bool Proceso::avanzar_tiempo(int t) {
    tiempo_estimado -= t;
    return tiempo_estimado > 0;
}

void Proceso::imprimir() const {
    cout << id << " " << memoria << " " << tiempo_estimado << endl;
}