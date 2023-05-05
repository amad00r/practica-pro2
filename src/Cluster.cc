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

void Cluster::modificar_cluster(const string &id_procesador, int &error) {}

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