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
    memoria_disponible = memoria;
}

string Procesador::consultar_id() const {
    return id;
}

bool Procesador::id_coincide(const string& id_procesador) const {
    return id == id_procesador;
}

bool Procesador::existe_id_proceso(int id_proceso) const {
    for (map<int, Proceso>::const_iterator it = procesos_memoria.begin(); it != procesos_memoria.end(); ++it)
        if (it->second.id_coincide(id_proceso)) return true;
    return false;
}

bool Procesador::hay_procesos() const {
    return not procesos_memoria.empty();
}

void Procesador::avanzar_tiempo(int t) {
    map<int, Proceso>::iterator it = procesos_memoria.begin();
    while (it != procesos_memoria.end()) {
        if (it->second.avanzar_tiempo(t)) ++it;
        else it = procesos_memoria.erase(it);
    }
}


/*
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

        list<pair<int, Proceso>>::iterator it = procesos_memoria.begin();
        list<pair<int, Proceso>>::iterator it_next = next(it);
        while (it_next != procesos_memoria.end()) {
            posicion_hueco = it->first + it->second.consultar_memoria();
            espacio_hueco = it_next->first - posicion_hueco;

            if (espacio_hueco >= proceso.consultar_memoria() and espacio_hueco < espacio_min_hueco) {
                it_insert = it_next;
                posicion_min_hueco = posicion_hueco;
                espacio_min_hueco = espacio_hueco;
                encontrado = true;
            }
            ++it;
            ++it_next;
        }

        posicion_hueco = it->first + it->second.consultar_memoria();
        if (memoria - posicion_hueco >= proceso.consultar_memoria() and espacio_hueco < espacio_min_hueco) {
            it_insert = procesos_memoria.end();
            posicion_min_hueco = posicion_hueco;
            encontrado = true;
        }
    }
    

    if (encontrado)
        procesos_memoria.insert(it_insert, { posicion_min_hueco, proceso });
        
    return encontrado;
}
*/

bool Procesador::colocar(const Proceso& proceso) {
    if (memoria_disponible < proceso.consultar_memoria()) return false;

    if (procesos_memoria.empty()) {
        procesos_memoria.insert(procesos_memoria.begin(), { 0, proceso });
        memoria_disponible -= proceso.consultar_memoria();
        return true;
    }   

    map<int, Proceso>::const_iterator it = procesos_memoria.begin();
    map<int, Proceso>::const_iterator it_insert;
    int posicion_min_hueco, espacio_min_hueco;
    int espacio_hueco = it->first;
    bool encontrado = false;

    if (espacio_hueco >= proceso.consultar_memoria()) {
        it_insert = it;
        posicion_min_hueco = 0;
        espacio_min_hueco = espacio_hueco;
        encontrado = true;
    }

    map<int, Proceso>::const_iterator it_next = next(it);
    int posicion_hueco;

    while (it_next != procesos_memoria.end()) {
        posicion_hueco = it->first + it->second.consultar_memoria();
        espacio_hueco = it_next->first - posicion_hueco;

        if (
            espacio_hueco >= proceso.consultar_memoria() and 
            (encontrado or espacio_hueco < espacio_min_hueco)
        ) {
            it_insert = it_next;
            posicion_min_hueco = posicion_hueco;
            espacio_min_hueco = espacio_hueco;
            encontrado = true;
        }
        ++it;
        ++it_next;
    }

    posicion_hueco = it->first + it->second.consultar_memoria();
    if (memoria - posicion_hueco >= proceso.consultar_memoria() and espacio_hueco < espacio_min_hueco) {
        it_insert = procesos_memoria.end();
        posicion_min_hueco = posicion_hueco;
        encontrado = true;
    }


    if (encontrado) {
        procesos_memoria.insert(it_insert, { posicion_min_hueco, proceso });
        memoria_disponible -= proceso.consultar_memoria();
    }
        
    return encontrado;
}


void Procesador::imprimir() const {
    for (
        map<int, Proceso>::const_iterator it = procesos_memoria.begin();
        it != procesos_memoria.end();
        ++it
    ) {
        cout << it->first << " ";
        it->second.imprimir();
    }
}

void Procesador::compactar_memoria() {
    ;// implementar. tiene q ser muy eficiente.
}