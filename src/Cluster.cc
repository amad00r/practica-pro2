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

bool Cluster::consultar_procesador(
    const BinTree<Procesador>& arbol,
    const string& id_procesador,
    Procesador& procesador_consultado
) const {
    if (arbol.empty()) return false;
    if (arbol.value().consultar_id() == id_procesador) {
        procesador_consultado = arbol.value();
        return true;
    }
    if (consultar_procesador(arbol.left(), id_procesador, procesador_consultado))
        return true;
    return consultar_procesador(arbol.right(), id_procesador, procesador_consultado);
}

void Cluster::modificar_cluster(const string& id_procesador, int& error) {
    ;//implementar recursivamente la búsqueda del procesador comparando id con id_coincide y verificando si hay procesos activos
    //usa leer_procesadores
    //implementar errores
}

bool Cluster::sustituir_procesador_modificado(BinTree<Procesador>& arbol, const Procesador& procesador) {
    if (arbol.empty()) return false;
    if (arbol.value().consultar_id() == procesador.consultar_id()) {
        arbol = BinTree<Procesador>(procesador, arbol.left(), arbol.right());
        return true;
    }       
    BinTree<Procesador> izquierdo = arbol.left();
    if (sustituir_procesador_modificado(izquierdo, procesador)) {
        arbol = BinTree<Procesador>(arbol.value(), izquierdo, arbol.right());
        return true;
    }
    BinTree<Procesador> derecho = arbol.right();
    bool encontrado = sustituir_procesador_modificado(derecho, procesador);
    arbol = BinTree<Procesador>(arbol.value(), izquierdo, derecho);
    return encontrado;
}

void Cluster::alta_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error) {
    Procesador procesador_consultado;
    if (consultar_procesador(procesadores, id_procesador, procesador_consultado)) {
        if (procesador_consultado.existe_id_proceso(proceso.consultar_id()))
            error = PROCESO_EXISTENTE_EN_PROCESADOR;
        else {
            if (procesador_consultado.colocar(proceso))
                sustituir_procesador_modificado(procesadores, procesador_consultado);
            else
                error = PROCESO_NO_COLOCABLE;
        }
    }
    else error = PROCESADOR_INEXISTENTE;
}

void Cluster::baja_proceso_procesador(int id_proceso, const string& id_procesador, int& error) {
    Procesador procesador_consultado;
    if (consultar_procesador(procesadores, id_procesador, procesador_consultado)) {
        if (procesador_consultado.quitar(id_proceso))
            sustituir_procesador_modificado(procesadores, procesador_consultado);
        else
            error = PROCESO_INEXISTENTE_EN_PROCESADOR;
    }
    else error = PROCESADOR_INEXISTENTE;
}

void Cluster::alta_proceso(const Proceso& proceso, int& error) {
    ;//implementar recurs.
}

void Cluster::avanzar_tiempo(int t) {
    ;//implementar recurs.
}


bool Cluster::auxiliar_imprimir_procesador(const BinTree<Procesador>& arbol, const string& id_procesador) const {
    if (arbol.empty()) return false;
    if (arbol.value().consultar_id() == id_procesador) {
        if (arbol.value().hay_procesos()) arbol.value().imprimir();
        else cout << endl;
        return true;
    }
    if (auxiliar_imprimir_procesador(arbol.left(), id_procesador)) return true;
    return auxiliar_imprimir_procesador(arbol.right(), id_procesador);
}

void Cluster::imprimir_procesador(const string& id_procesador, int& error) const {
    if (not auxiliar_imprimir_procesador(procesadores, id_procesador))
        error = PROCESADOR_INEXISTENTE;
}


void Cluster::auxiliar_imprimir_procesadores_cluster(const BinTree<Procesador>& arbol) const {
    if (not arbol.empty()) {
        cout << arbol.value().consultar_id() << endl;
        arbol.value().imprimir();
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