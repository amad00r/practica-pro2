#include "Cluster.hh"
#include "BinTree.hh"
#include "Procesador.hh"
#include "Errores.hh"

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

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

bool Cluster::auxiliar_alta_proceso_procesador(
    const BinTree<Procesador>& arbol,
    const string& id_procesador,
    const Proceso& proceso,
    int &error
) {
    if (arbol.empty()) return false;
    if (arbol.value().consultar_id() == id_procesador) {
        if (arbol.value().existe_id_proceso(proceso.consultar_id()))
            error = PROCESO_EXISTENTE_EN_PROCESADOR;
        else {
            Procesador procesador_modificado = Procesador(arbol.value());
            if (procesador_modificado.colocar(proceso))
                sustituir_procesador_modificado(procesadores, procesador_modificado);
            else
                error = PROCESO_NO_COLOCABLE;
        }
        return true;
    }
    if (auxiliar_alta_proceso_procesador(arbol.left(), id_procesador, proceso, error)) return true;
    return auxiliar_alta_proceso_procesador(arbol.right(), id_procesador, proceso, error);
}

void Cluster::alta_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error) {
    if (not auxiliar_alta_proceso_procesador(procesadores, id_procesador, proceso, error))
        error = PROCESADOR_INEXISTENTE;
}

bool Cluster::auxiliar_baja_proceso_procesador(
    const BinTree<Procesador>& arbol,
    const string& id_procesador,
    int id_proceso,
    int &error
) {
    if (arbol.empty()) return false;
    if (arbol.value().consultar_id() == id_procesador) {
        Procesador procesador_modificado = Procesador(arbol.value());
        if (procesador_modificado.quitar(id_proceso))
            sustituir_procesador_modificado(procesadores, procesador_modificado);
        else
            error = PROCESO_INEXISTENTE_EN_PROCESADOR;
        return true;
    }
    if (auxiliar_baja_proceso_procesador(arbol.left(), id_procesador, id_proceso, error)) return true;
    return auxiliar_baja_proceso_procesador(arbol.right(), id_procesador, id_proceso, error);
}

void Cluster::baja_proceso_procesador(int id_proceso, const string& id_procesador, int& error) {
    if (not auxiliar_baja_proceso_procesador(procesadores, id_procesador, id_proceso, error))
        error = PROCESADOR_INEXISTENTE;
}

void Cluster::alta_proceso(const Proceso& proceso, int& error) {
    ;//implementar recurs.
}

void Cluster::auxiliar_avanzar_tiempo(BinTree<Procesador>& arbol, int t) {
    if (not arbol.empty()) {
        BinTree<Procesador> izquierdo = arbol.left();
        auxiliar_avanzar_tiempo(izquierdo, t);
        BinTree<Procesador> derecho = arbol.right();
        auxiliar_avanzar_tiempo(derecho, t);

        Procesador procesador = arbol.value();
        procesador.avanzar_tiempo(t);

        arbol = BinTree<Procesador>(procesador, izquierdo, derecho);
    }
}

void Cluster::avanzar_tiempo(int t) {
    auxiliar_avanzar_tiempo(procesadores, t);
}


bool Cluster::auxiliar_imprimir_procesador(const BinTree<Procesador>& arbol, const string& id_procesador) const {
    if (arbol.empty()) return false;
    if (arbol.value().consultar_id() == id_procesador) {
        arbol.value().imprimir();
        return true;
    }
    if (auxiliar_imprimir_procesador(arbol.left(), id_procesador)) return true;
    return auxiliar_imprimir_procesador(arbol.right(), id_procesador);
}

void Cluster::imprimir_procesador(const string& id_procesador, int& error) const {
    if (not auxiliar_imprimir_procesador(procesadores, id_procesador))
        error = PROCESADOR_INEXISTENTE;
}

void Cluster::auxiliar_imprimir_procesadores_cluster(const BinTree<Procesador>& arbol, vector<Procesador> &p) const {
    if (not arbol.empty()) {
        p.push_back(Procesador(arbol.value()));
        auxiliar_imprimir_procesadores_cluster(arbol.left(), p);
        auxiliar_imprimir_procesadores_cluster(arbol.right(), p);
    }
}

bool id_order(const Procesador &p1, const Procesador &p2) {
    if (p1.consultar_id() < p2.consultar_id()) return true;
    return false;
}

void Cluster::imprimir_procesadores_cluster() const {
    vector<Procesador> p;
    auxiliar_imprimir_procesadores_cluster(procesadores, p);
    sort(p.begin(), p.end(), id_order);
    for (int i = 0; i < p.size(); ++i) {
        cout << p[i].consultar_id() << endl;
        p[i].imprimir();
    }
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