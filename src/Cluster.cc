#include "Cluster.hh"
#include "BinTree.hh"
#include "Procesador.hh"
#include "Errores.hh"

#include <string>
#include <iostream>

using namespace std;

Cluster::Cluster() {}

void Cluster::configurar_cluster() {
    leer_procesadores(procesadores);
}

void Cluster::leer_procesadores(BinTree<Procesador>& arbol) const {
    string id_procesador;
    cin >> id_procesador;

    if (id_procesador != "*") {
        int memoria;
        cin >> memoria;
        BinTree<Procesador> aux1, aux2;
        leer_procesadores(aux1);
        leer_procesadores(aux2);
        Procesador p(id_procesador, memoria);
        arbol = BinTree<Procesador>(p, aux1, aux2);
    }

}

bool Cluster::buscar_procesador(const BinTree<Procesador>& arbol, const string& id_procesador, Procesador& procesador) const {
    if (arbol.empty()) return false;
    if (arbol.value().consultar_id() == id_procesador) {
        procesador = arbol.value();
        return true;
    }
    if (buscar_procesador(arbol.left(), id_procesador, procesador)) return true;
    return buscar_procesador(arbol.right(), id_procesador, procesador);
}

void Cluster::modificar_cluster(const string& id_procesador, int& error) {
    ;//implementar recursivamente la búsqueda del procesador comparando id con id_coincide y verificando si hay procesos activos
    //usa leer_procesadores
    //implementar errores
}

void Cluster::alta_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error) {
    Procesador procesador;
    bool encontrado = buscar_procesador(procesadores, id_procesador, procesador);
    if (not encontrado) 
        error = PROCESADOR_INEXISTENTE;
    else if (procesador.existe_id_proceso(proceso.consultar_id()))
        error = PROCESO_EXISTENTE_EN_PROCESADOR;
    else if (not procesador.colocar(proceso))
        error = PROCESO_NO_COLOCABLE;
}

void Cluster::baja_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error) {
    ;//implementar recurs.
}

void Cluster::alta_proceso(const Proceso& proceso, int& error) {
    ;//implementar recurs.
}

void Cluster::avanzar_tiempo(int t) {
    ;//implementar recurs.
}

void Cluster::imprimir_procesador(const string& id_procesador, int& error) const {
    ;//implementar recurs.
}


void Cluster::auxiliar_imprimir_procesadores_cluster(const BinTree<Procesador>& arbol) const {
    if (not arbol.empty()) {
        cout << arbol.value().consultar_id() << endl;
        auxiliar_imprimir_procesadores_cluster(arbol.left());
        auxiliar_imprimir_procesadores_cluster(arbol.right());
    }
}

void Cluster::imprimir_procesadores_cluster() const {
    auxiliar_imprimir_procesadores_cluster(procesadores);
}

void Cluster::auxiliar_imprimir_estructura_cluster(const BinTree<Procesador>& arbol) const {
    if (arbol.empty()) cout << " ";
    else {
        cout << "(" << arbol.value().consultar_id();
        auxiliar_imprimir_estructura_cluster(arbol.left());
        auxiliar_imprimir_estructura_cluster(arbol.right());
        cout << ")";
    }
}

void Cluster::imprimir_estructura_cluster() const {
    auxiliar_imprimir_estructura_cluster(procesadores);
    cout << endl;
}

void Cluster::compactar_memoria_procesador(const string& id_procesador, int& error) {
    ;//implementar recurs.
}

void Cluster::compactar_memoria_cluster() {
    ;//implementar recurs..
}