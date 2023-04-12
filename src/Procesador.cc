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


// IMPORTANTE EFICIENCIA
bool Procesador::colocar(const Proceso& proceso) {
    list<pair<int, Proceso>>::iterator it_insert;
    int posicion_min_hueco, espacio_min_hueco;
    bool encontrado = false;

    if (procesos_memoria.empty()) {
        it_insert = procesos_memoria.begin();
        posicion_min_hueco = 0;
        encontrado = true;
    }
    else {
        int posicion_hueco;
        int espacio_hueco = procesos_memoria.begin()->first;

        if (espacio_hueco >= proceso.consultar_memoria()) {
            it_insert = procesos_memoria.begin();
            posicion_min_hueco = 0;
            espacio_min_hueco = espacio_hueco;
            encontrado = true;
        }

        list<pair<int, Proceso>>::const_iterator it = procesos_memoria.begin();
        while (it < procesos_memoria.end() - 1) {
            posicion_hueco = it->first + it->second.consultar_memoria();
            espacio_hueco = *(it + 1)->first - posicion_hueco;

            else if (espacio_hueco >= proceso.consultar_memoria()) {
                it_insert = it + 1;
                posicion_min_hueco = posicion_hueco;
                espacio_min_hueco = espacio_hueco;
                encontrado = true;
            }
            ++it;
        }

        posicion_hueco = it->first + it->second.consultar_memoria();
        if (memoria - posicion_hueco >= proceso.consultar_memoria()) {
            it_insert = procesos_memoria.end();
            posicion_min_hueco = posicion_hueco;
            encontrado = true;
        }
    }
    

    if (encontrado)
        procesos_memoria.insert(it_insert, make_pair(posicion_min_hueco, proceso));
        
    return encontrado;
}


void Procesador::imprimir() const {
    for (
        list<pair<int, Proceso>>::const_iterator it = procesos_memoria.begin();
        it != procesos_memoria.end();
        ++it
    ) {
        it->second.imprimir();
        cout << " " << it->first << ", ";
    }
    cout << endl;
}

void Procesador::compactar_memoria() {
    ;// implementar. tiene q ser muy eficiente.
}