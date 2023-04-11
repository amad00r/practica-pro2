#include "Cluster.hh"
#include "BinTree.hh"
#include "Procesador.hh"
#include "Errores.hh" ///////////////////////////?¿?? hace falta

#include <string>
#include <iostream>

using namespace std;

Cluster::Cluster() {}

void Cluster::configurar_cluster() {
    leer_procesadores(procesadores);
}

void Cluster::leer_procesadores(BinTree<Procesador>& arbol) {
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

void Cluster::modificar_cluster(const string& id_procesador, int& error) {
    ;//implementar recursivamente la búsqueda del procesador comparando id con id_coincide y verificando si hay procesos activos
    //usa leer_procesadores
    //implementar errores
}

void Cluster::alta_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error) {
    ;//implementar recursivamente la búsqueda
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

void Cluster::imprimir_procesadores_cluster() const {
    ;//implementar recurs.
}

void Cluster::imprimir_arbol_procesadores(const BinTree<Procesador>& arbol) const {
    if (arbol.empty()) cout << " ";
    else {
        cout << "(" << arbol.value().consultar_id();
        imprimir_arbol_procesadores(arbol.left());
        imprimir_arbol_procesadores(arbol.right());
        cout << ")";
    }
}

void Cluster::imprimir_estructura_cluster() const {
    imprimir_arbol_procesadores(procesadores);
    cout << endl;
}

void Cluster::compactar_memoria_procesador(const string& id_procesador, int& error) {
    ;//implementar recurs.
}

void Cluster::compactar_memoria_cluster() {
    ;//implementar recurs..
}