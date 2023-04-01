#include "Cluster.hh"
#include "BinTree.hh"
#include "Procesador.hh"
#include <string>

#include "Errores.hh" ///////////////////////////?¿?? hace falta

using namespace std;

Cluster::Cluster() {}

void Cluster::configurar_cluster() {
    leer_procesadores(procesadores);
}

void Cluster::leer_procesadores(BinTree<Procesador>& procesadores) {
    ;//implementar recursivamente según juego de pruebas
}

bool Cluster::modificar_cluster(const string& id_procesador, int& error) {
    ;//implementar recursivamente la búsqueda del procesador comparando id con id_coincide y verificando si hay procesos activos
    //usa leer_procesadores
    //implementar errores
}

bool Cluster::alta_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error) {
    ;//implementar recursivamente la búsqueda
}

bool Cluster::baja_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error) {
    ;//implementar recurs.
}

bool Cluster::alta_proceso(const Proceso& proceso, int& error) {
    ;//implementar recurs.
}

void Cluster::avanzar_tiempo(int t) {
    ;//implementar recurs.
}

bool Cluster::imprimir_procesador(const string& id_procesador, int& error) const {
    ;//implementar recurs.
}

void Cluster::imprimir_procesadores_cluster() const {
    ;//implementar recurs.
}

void Cluster::imprimir_estructura_cluster() const {
    ;//implementar recurs.
}

bool Cluster::compactar_memoria_procesador(const string& id_procesador, int& error) {
    ;//implementar recurs.
}

void Cluster::compactar_memoria_cluster() {
    ;//implementar recurs..
}