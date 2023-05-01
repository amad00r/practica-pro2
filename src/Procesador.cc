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
    huecos.insert(huecos.begin(), make_pair(memoria, set<int>{ 0 }));
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
    if (
        memoria_disponible < proceso.consultar_memoria() or
        huecos.begin()->first < proceso.consultar_memoria()
    ) return false;

    int pos_hueco = *(huecos.begin()->second.begin());

    posiciones_procesos.insert(make_pair(proceso.consultar_id(), pos_hueco));
    procesos_memoria.insert(make_pair(pos_hueco, proceso));
    memoria_disponible -= proceso.consultar_memoria();

    if (huecos.begin()->first != proceso.consultar_memoria())
        huecos[huecos.begin()->first - proceso.consultar_memoria()].insert(pos_hueco + proceso.consultar_memoria());

    if (huecos.begin()->second.size() == 1) huecos.erase(huecos.begin());
    else huecos.begin()->second.erase(huecos.begin()->second.begin());
        
    return true;
}

bool Procesador::quitar(int id_proceso) {
    map<int, int>::iterator it = posiciones_procesos.find(id_proceso);
    if (it == posiciones_procesos.end()) return false;
    int pos_proceso = it->second;
    int mem_proceso = procesos_memoria[pos_proceso].consultar_memoria();

    memoria_disponible += mem_proceso;
    procesos_memoria.erase(pos_proceso);
    posiciones_procesos.erase(it);
    
    int posicion_nuevo_hueco;
    it = posiciones_procesos.lower_bound(id_proceso);
    if (it == posiciones_procesos.end()) {
        posicion_nuevo_hueco = 0;
        if (pos_proceso != 0) {
            if (huecos[pos_proceso].size() == 1) huecos.erase(pos_proceso);
            else huecos[pos_proceso].erase(0);
        }
        it = posiciones_procesos.upper_bound(id_proceso);
    }
    else {
        posicion_nuevo_hueco = it->second + procesos_memoria[it->second].consultar_memoria();
        if (posicion_nuevo_hueco < pos_proceso) {
            int espacio_hueco = pos_proceso - posicion_nuevo_hueco;
            if (huecos[espacio_hueco].size() == 1) huecos.erase(espacio_hueco);
            else huecos[espacio_hueco].erase(posicion_nuevo_hueco);
        }
        ++it;
    }

    int espacio_nuevo_hueco;
    if (it == posiciones_procesos.end()) {
        espacio_nuevo_hueco = memoria - posicion_nuevo_hueco;
        int espacio_hueco = memoria - pos_proceso - mem_proceso;
        if (espacio_hueco != 0) {
            if (huecos[espacio_hueco].size() == 1) huecos.erase(espacio_hueco);
            else huecos[espacio_hueco].erase(pos_proceso + mem_proceso);
        }
    }
    else {
        espacio_nuevo_hueco = it->second - posicion_nuevo_hueco;
        if (it->second > pos_proceso + mem_proceso) {
            int espacio_hueco = pos_proceso - it->second - procesos_memoria[it->second].consultar_memoria();
            if (huecos[espacio_hueco].size() == 1) huecos.erase(espacio_hueco);
            else huecos[espacio_hueco].erase(it->second + procesos_memoria[it->second].consultar_memoria());
        }
    }

    huecos[espacio_nuevo_hueco].insert(posicion_nuevo_hueco);
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