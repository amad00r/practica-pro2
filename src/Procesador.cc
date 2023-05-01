#include "Procesador.hh"
#include "Proceso.hh"

#include <string>
#include <list>
#include <map>
#include <set>
#include <iostream>

using namespace std;

Procesador::Procesador() {}

Procesador::Procesador(const string& id_procesador, int memoria) {
    this->id = id_procesador;
    this->memoria = memoria;
    memoria_disponible = memoria;
    huecos_memoria.insert(huecos_memoria.begin(), make_pair(memoria, set<int>{ 0 }));
}

string Procesador::consultar_id() const { return id; }
bool Procesador::id_coincide(const string& id_procesador) const { return id == id_procesador; }
bool Procesador::existe_id_proceso(int id_proceso) const {
    return posiciones_procesos.find(id_proceso) != posiciones_procesos.end();
}
bool Procesador::hay_procesos() const { return not posiciones_procesos.empty(); }

void Procesador::avanzar_tiempo(int t) {
    map<int, Proceso>::iterator it = procesos_memoria.begin();
    while (it != procesos_memoria.end()) {
        if (it->second.avanzar_tiempo(t)) ++it;
        else {
            quitar(it->second.consultar_id());
            // implementar quitar directamente con iterador
        }
    }
}

bool Procesador::colocar(const Proceso& proceso) {
    map<int, set<int>>::iterator hueco_minimo = huecos_memoria.lower_bound(proceso.consultar_memoria());
    if (hueco_minimo == huecos_memoria.end()) return false;

    int pos_hueco = *(hueco_minimo->second.begin());

    posiciones_procesos.insert(make_pair(proceso.consultar_id(), pos_hueco));
    procesos_memoria.insert(make_pair(pos_hueco, proceso));
    memoria_disponible -= proceso.consultar_memoria();

    if (hueco_minimo->first != proceso.consultar_memoria())
        huecos_memoria[hueco_minimo->first - proceso.consultar_memoria()].insert(pos_hueco + proceso.consultar_memoria());

    if (hueco_minimo->second.size() == 1) huecos_memoria.erase(hueco_minimo);
    else hueco_minimo->second.erase(hueco_minimo->second.begin());
        
    return true;
}

void Procesador::recalcular_huecos() {
    map<int, Procesador>
}

bool Procesador::quitar(int id_proceso) {
    map<int, int>::iterator it = posiciones_procesos.find(id_proceso);
    if (it == posiciones_procesos.end()) return false;
    int pos_proceso = it->second;
    int mem_proceso = procesos_memoria[pos_proceso].consultar_memoria();

    memoria_disponible += mem_proceso;

    map<int, Proceso>::iterator it_aux;
    map<int, Proceso>::iterator next_it_aux = procesos_memoria.begin();
    while (next_it_aux->first != pos_proceso) {
        it_aux = next_it_aux;
        ++next_it_aux;
    }
    posiciones_procesos.erase(it);

    int pos_inicial_hueco;
    if (it_aux == procesos_memoria.begin()) {
        pos_inicial_hueco = 0;
        if (pos_proceso != 0) {
            if (huecos_memoria[pos_proceso].size() == 1) huecos_memoria.erase(pos_proceso);
            else huecos_memoria[pos_proceso].erase(0);
        }
    }
    else {
        pos_inicial_hueco = it_aux->first + it_aux->second.consultar_memoria();
        int espacio_hueco = pos_proceso - pos_inicial_hueco;
        if (espacio_hueco != 0) {
            if (huecos_memoria[espacio_hueco].size() == 1) huecos_memoria.erase(espacio_hueco);
            else huecos_memoria[espacio_hueco].erase(pos_inicial_hueco);
        }
    }

    ++it_aux;
    it_aux = procesos_memoria.erase(it_aux);

    int pos_final_hueco;
    if (it_aux == procesos_memoria.end()) {
        pos_final_hueco = memoria;
        int espacio_hueco = memoria - pos_proceso - mem_proceso;
        if (espacio_hueco != 0) {
            if (huecos_memoria[espacio_hueco].size() == 1) huecos_memoria.erase(espacio_hueco);
            else huecos_memoria[espacio_hueco].erase(pos_proceso + mem_proceso);
        }
    }
    else {
        pos_final_hueco = it_aux->first;
        int espacio_hueco = it_aux->first - pos_proceso - mem_proceso;
        if (espacio_hueco != 0) {
            if (huecos_memoria[espacio_hueco].size() == 1) huecos_memoria.erase(espacio_hueco);
            else huecos_memoria[espacio_hueco].erase(pos_proceso + mem_proceso);
        }
    }

    huecos_memoria[pos_final_hueco - pos_inicial_hueco].insert(pos_inicial_hueco);
    return true;
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