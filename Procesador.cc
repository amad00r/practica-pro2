/** @file Procesador.cc
    @brief implementación de la clase Procesador.
*/

#include "Procesador.hh"
#include "Proceso.hh"

#include <string>
#include <list>
#include <map>
#include <set>
#include <iostream>

using namespace std;

Procesador::Procesador() {}

Procesador::Procesador(int mem) {
    memoria = mem;
    memoria_disponible = mem;
    // Inicializo huecos_memoria con un único hueco que ocupa toda la memoria.
    huecos_memoria.insert(huecos_memoria.begin(), make_pair(mem, set<int>{ 0 }));
}

int Procesador::consultar_memoria_disponible() const {
    return memoria_disponible;
}

bool Procesador::existe_id_proceso(int id_proceso) const {
    return posiciones_procesos.find(id_proceso) != posiciones_procesos.end();
}

bool Procesador::hay_procesos() const {
    return not posiciones_procesos.empty();
}

int Procesador::consultar_espacio_hueco_minimo(int proceso_mem) const {
    if (memoria_disponible < proceso_mem) return 0;
    // Encuentra el primer hueco con tamaño igual o mayor que proceso_mem.
    map<int, set<int>>::const_iterator hueco_minimo = huecos_memoria.lower_bound(proceso_mem);
    if (hueco_minimo == huecos_memoria.end()) return 0;
    return hueco_minimo->first;
}

void Procesador::avanzar_tiempo(int t) {
    map<int, Proceso>::iterator it = procesos_memoria.begin();

    bool recalcular = false;
    while (it != procesos_memoria.end()) {
        if (it->second.avanzar_tiempo(t)) ++it;
        else {
            recalcular = true;
            memoria_disponible += it->second.consultar_memoria();
            posiciones_procesos.erase(it->second.consultar_id());
            it = procesos_memoria.erase(it);
        }
    }
    if (recalcular) recalcular_huecos();
}

bool Procesador::colocar(const Proceso& proceso) {
    if (memoria_disponible < proceso.consultar_memoria()) return false;

    map<int, set<int>>::iterator hueco_minimo = huecos_memoria.lower_bound(proceso.consultar_memoria());
    if (hueco_minimo == huecos_memoria.end()) return false;

    int pos_hueco = *(hueco_minimo->second.begin());

    posiciones_procesos[proceso.consultar_id()] = pos_hueco;
    procesos_memoria[pos_hueco] = proceso;
    memoria_disponible -= proceso.consultar_memoria();

    // Si el proceso tiene tamaño menor que el tamaño del hueco dónde se coloca,
    // se genera un nuevo hueco de tamaño igual a (tamaño hueco antiguo - tamaño proceso). 
    if (hueco_minimo->first != proceso.consultar_memoria())
        huecos_memoria[hueco_minimo->first - proceso.consultar_memoria()].insert(pos_hueco + proceso.consultar_memoria());

    // Si el proceso que queremos borrar es el único con ese tamaño, borramos el tamaño de huecos_memoria.
    if (hueco_minimo->second.size() == 1) huecos_memoria.erase(hueco_minimo);
    // De otro modo, solo borramos la posicion en memoria del hueco.
    else hueco_minimo->second.erase(hueco_minimo->second.begin());
        
    return true;
}

void Procesador::recalcular_huecos() {
    huecos_memoria.clear();

    // Si no hay procesos ejecutándose hay un solo hueco que ocupa toda la memoria.
    if (procesos_memoria.empty())
        huecos_memoria.insert(huecos_memoria.begin(), make_pair(memoria, set<int>{ 0 }));
    else {
        map<int, Proceso>::const_iterator it = procesos_memoria.begin();

        // Trato como un caso especial el hueco que hay del principio
        // de la memoria hasta el primer proceso.
        if (it->first != 0)
            huecos_memoria.insert(huecos_memoria.begin(), make_pair(it->first, set<int>{ 0 }));

        // Almaceno la posicion dónde acaba el proceso actual para saber dónde empieza
        // el próximo proceso.
        int tmp = it->first + it->second.consultar_memoria();
        
        ++it;
        while (it != procesos_memoria.end()) {
            if (tmp != it->first) huecos_memoria[it->first - tmp].insert(tmp);
            tmp = it->first + it->second.consultar_memoria();
            ++it;
        }

        // Trato como un caso especial el hueco que hay desde el último
        // proceso hasta el final de la memoria.
        if (tmp != memoria) huecos_memoria[memoria - tmp].insert(tmp);
    }
}

bool Procesador::quitar(int id_proceso) {
    map<int, int>::iterator it = posiciones_procesos.find(id_proceso);
    if (it == posiciones_procesos.end()) return false;

    map<int, Proceso>::iterator it_aux = procesos_memoria.find(it->second);
    memoria_disponible += it_aux->second.consultar_memoria();
    procesos_memoria.erase(it_aux);
    posiciones_procesos.erase(it);

    recalcular_huecos();

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
    map<int, Proceso>::iterator it = procesos_memoria.begin();
    if (it == procesos_memoria.end()) return;

    // tmp representa la posición en memoria dónde debería estar el proceso actual
    // para estar compacto hacia la izquierda de la memoria.
    int tmp = 0;
    while (it != procesos_memoria.end()) {
        if (it->first != tmp) {
            // Inserto un proceso igual al actual en la posición compactada.
            procesos_memoria.insert(it, make_pair(tmp, it->second));

            map<int, int>::iterator it_aux = posiciones_procesos.find(it->second.consultar_id());
            // Corrijo la posición del proceso en el otro mapa.
            posiciones_procesos[it->second.consultar_id()] = tmp;

            tmp += it->second.consultar_memoria();
            // Elimino el proceso con la posición no rectificada.
            it = procesos_memoria.erase(it);
        }
        else {
            tmp += it->second.consultar_memoria();
            ++it;
        }
    }
    
    // Como todos los procesos se encuentran compactados hacia la izquierda,
    // puedo borrar los huecos y crear uno nuevo que empieza dónde acaba el
    // último proceso, y acaba en el final de la memoria.
    huecos_memoria.clear();
    if (tmp != memoria)
        huecos_memoria.insert(huecos_memoria.begin(), make_pair(memoria - tmp, set<int>{ tmp }));
}
