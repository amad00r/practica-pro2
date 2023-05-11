#include "Cluster.hh"
#include "BinTree.hh"
#include "Procesador.hh"
#include "Errores.hh"

#include <string>
#include <iostream>
#include <map>

using namespace std;

Cluster::Cluster() {}

void Cluster::configurar_cluster() {
    mapa_procesadores.clear();
    leer_procesadores(arbol_procesadores);
}

void Cluster::leer_procesadores(BinTree<map<string, Procesador>::iterator> &arbol) {
    string id_procesador;
    cin >> id_procesador;

    if (id_procesador != "*") {
        int memoria;
        cin >> memoria;
        BinTree<map<string, Procesador>::iterator> aux1, aux2;
        leer_procesadores(aux1);
        leer_procesadores(aux2);
        arbol = BinTree<map<string, Procesador>::iterator>(
            mapa_procesadores.insert(make_pair(id_procesador, Procesador(id_procesador, memoria))).first,
            aux1,
            aux2
        );
    }
}

void Cluster::consumir_cluster_input() const {
    string id_procesador;
    cin >> id_procesador;

    if (id_procesador != "*") {
        int memoria;
        cin >> memoria;
        consumir_cluster_input();
        consumir_cluster_input();
    }
}

bool Cluster::auxiliar_modificar_cluster(
    BinTree<map<string, Procesador>::iterator> &arbol,
    const string &id_procesador,
    int &error
) {
    if (arbol.empty() or error != NO_HAY_ERROR) return false;
    if (arbol.value()->first == id_procesador) {
        if      (arbol.value()->second.hay_procesos())                  error = PROCESOS_EN_EJECUCION;
        else if (not arbol.left().empty() or not arbol.right().empty()) error = TIENE_PROCESADORES_AUXILIARES;
        else {
            mapa_procesadores.erase(arbol.value());
            leer_procesadores(arbol);
        }
        return true;
    }

    BinTree<map<string, Procesador>::iterator> aux1 = arbol.left();
    if (auxiliar_modificar_cluster(aux1, id_procesador, error)) {
        arbol = BinTree<map<string, Procesador>::iterator>(arbol.value(), aux1, arbol.right());
        return true;
    }
    BinTree<map<string, Procesador>::iterator> aux2 = arbol.right();
    bool found = auxiliar_modificar_cluster(aux2, id_procesador, error);
    arbol = BinTree<map<string, Procesador>::iterator>(arbol.value(), aux1, aux2);
    return found;
}

void Cluster::modificar_cluster(const string &id_procesador, int &error) {
    if (not auxiliar_modificar_cluster(arbol_procesadores, id_procesador, error)) {
        error = PROCESADOR_INEXISTENTE;
        consumir_cluster_input();
    }
    else if (error != NO_HAY_ERROR) consumir_cluster_input();
}

void Cluster::alta_proceso_procesador(const Proceso &proceso, const string &id_procesador, int &error) {
    map<string, Procesador>::iterator it = mapa_procesadores.find(id_procesador);

    if      (it == mapa_procesadores.end())                        error = PROCESADOR_INEXISTENTE;
    else if (it->second.existe_id_proceso(proceso.consultar_id())) error = PROCESO_EXISTENTE_EN_PROCESADOR;
    else if (not it->second.colocar(proceso))                      error = PROCESO_NO_COLOCABLE;
}

void Cluster::baja_proceso_procesador(int id_proceso, const string &id_procesador, int &error) {
    map<string, Procesador>::iterator it = mapa_procesadores.find(id_procesador);

    if      (it == mapa_procesadores.end())     error = PROCESADOR_INEXISTENTE;
    else if (not it->second.quitar(id_proceso)) error = PROCESO_INEXISTENTE_EN_PROCESADOR;
}

void Cluster::alta_proceso(const Proceso& proceso, int& error) {}

void Cluster::avanzar_tiempo(int t) {
    for (
        map<string, Procesador>::iterator it = mapa_procesadores.begin();
        it != mapa_procesadores.end();
        ++it
    ) it->second.avanzar_tiempo(t);
}

void Cluster::imprimir_procesador(const string &id_procesador, int &error) const {
    map<string, Procesador>::const_iterator it = mapa_procesadores.find(id_procesador);

    if (it == mapa_procesadores.end()) error = PROCESADOR_INEXISTENTE;
    else it->second.imprimir();
}

void Cluster::imprimir_procesadores_cluster() const {
    for (
        map<string, Procesador>::const_iterator it = mapa_procesadores.begin();
        it != mapa_procesadores.end();
        ++it
    ) {
        cout << it->first << endl;
        it->second.imprimir();
    }
}

void Cluster::auxiliar_imprimir_estructura_cluster(const BinTree<map<string, Procesador>::iterator> &arbol) const {
    if (arbol.empty()) cout << " ";
    else {
        cout << "(" << arbol.value()->first;
        auxiliar_imprimir_estructura_cluster(arbol.left());
        auxiliar_imprimir_estructura_cluster(arbol.right());
        cout << ")";
    }
}

void Cluster::imprimir_estructura_cluster() const {
    auxiliar_imprimir_estructura_cluster(arbol_procesadores);
    cout << endl;
}

void Cluster::compactar_memoria_procesador(const string& id_procesador, int& error) {}
void Cluster::compactar_memoria_cluster() {}