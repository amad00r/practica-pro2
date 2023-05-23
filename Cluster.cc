/** @file Cluster.cc
    @brief implementación de la clase Cluster.
*/

#include "Cluster.hh"
#include "BinTree.hh"
#include "Procesador.hh"
#include "Errores.hh"

using namespace std;

Cluster::Cluster() {
    // No llamo a configurar_cluster porque así me ahorro limpiar
    // mapa_procesadores cuando aún no está inicializado.
    leer_procesadores(arbol_procesadores);
}

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
            // Inserto una pareja (identificador, procesador) en mapa_procesadores,
            // y aprovecho que devuelve una pareja (iterador, bool) para insertar
            // el iterador en el value del árbol.
            mapa_procesadores.insert(make_pair(id_procesador, Procesador(memoria))).first,
            aux1,
            aux2
        );
    }
}

void Cluster::consumir_cluster_input() {
    string id_procesador;
    cin >> id_procesador;

    if (id_procesador != "*") {
        int memoria;
        cin >> memoria;
        consumir_cluster_input();
        consumir_cluster_input();
    }

    // Acaba la función y memoria e id_procesador serán
    // desechados sin haber sido utilizados
}

bool Cluster::auxiliar_modificar_cluster(
    BinTree<map<string, Procesador>::iterator> &arbol,
    const string &id_procesador,
    int &error
) {
    // Si error != OK, ya se ha encontrado el procesador con identificador
    // igual a id_procesador pero no se ha podido modificar.
    if (arbol.empty() or error != OK) return false;

    if (arbol.value()->first == id_procesador) {
        if (arbol.value()->second.hay_procesos())
            error = PROCESOS_EN_EJECUCION;
        else if (not arbol.left().empty() or not arbol.right().empty())
            error = TIENE_PROCESADORES_AUXILIARES;
        else {
            mapa_procesadores.erase(arbol.value());
            leer_procesadores(arbol);
        }
        return true;
    }

    BinTree<map<string, Procesador>::iterator> aux1 = arbol.left();
    // Si encontramos el procesador en el subárbol izquierdo dejamos de buscar.
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
    else if (error != OK) consumir_cluster_input();

    // El clúster de la entrada estándar se debe desperdiciar si, y solo si,
    // no se ha encontrado o no se ha podido modificar el procesador. 
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

bool Cluster::procesador_preferido(
    const map<string, Procesador>::iterator &preferido,
    int hueco_min_preferido,
    int profundidad_preferido,
    const map<string, Procesador>::iterator &it,
    int hueco_min_it,
    int profundidad,
    const Proceso &proceso
) {
    bool candidato_it = (hueco_min_it != 0 and not it->second.existe_id_proceso(proceso.consultar_id()));

    // Si aún no hay ningún preferido, solo es necesario que el procesador apuntado
    // por it sea candidato para ejecutar proceso para que preferido sea actualizado.
    if (hueco_min_preferido == 0) return not candidato_it;

    // Si el segundo no es candidato para ejecutar proceso, directamente no se actualiza preferido.
    if (not candidato_it) return true;

    if (hueco_min_preferido < hueco_min_it) return true;
    if (hueco_min_preferido > hueco_min_it) return false;

    int memoria_disponible_preferido = preferido->second.consultar_memoria_disponible();
    int memoria_disponible_it = it->second.consultar_memoria_disponible();
    if (memoria_disponible_preferido > memoria_disponible_it) return true;
    if (memoria_disponible_preferido < memoria_disponible_it) return false;

    if (profundidad_preferido < profundidad) return true;
    if (profundidad_preferido > profundidad) return false;

    // Si no se puede determinar el preferido con las condiciones anteriores, preferido
    // no se actualiza porque sabemos que es el que se encuentra más a la izquierda en
    // el árbol debido a que lo recorremos en preorden empezando por el subárbol izquierdo.
    return true;
}

void Cluster::auxiliar_alta_proceso(
    map<string, Procesador>::iterator &preferido,
    int &hueco_min_preferido,
    int &profundidad_preferido,
    const BinTree<map<string, Procesador>::iterator> &arbol,
    int profundidad,
    const Proceso &proceso
) {
    if (not arbol.empty()) {
        int hueco_min_it = arbol.value()->second.consultar_espacio_hueco_minimo(proceso.consultar_memoria());
        if (not procesador_preferido(
            preferido,
            hueco_min_preferido,
            profundidad_preferido,
            arbol.value(),
            hueco_min_it,
            profundidad,
            proceso
        )) {
            preferido = arbol.value();
            hueco_min_preferido = hueco_min_it;
            profundidad_preferido = profundidad;
        }
        auxiliar_alta_proceso(preferido, hueco_min_preferido, profundidad_preferido, arbol.left(), profundidad + 1, proceso);
        auxiliar_alta_proceso(preferido, hueco_min_preferido, profundidad_preferido, arbol.right(), profundidad + 1, proceso);
    }
}

bool Cluster::alta_proceso(const Proceso &proceso) {
    map<string, Procesador>::iterator preferido;
    // Un hueco nunca puede tener tamaño 0, por tanto puedo utilizar 0 como centinela
    // para determinar que no se ha encontrado un procesador preferido.
    int hueco_min_preferido = 0;
    int profundidad_preferido;

    auxiliar_alta_proceso(preferido, hueco_min_preferido, profundidad_preferido, arbol_procesadores, 0, proceso);
    if (hueco_min_preferido == 0) return false;
    preferido->second.colocar(proceso);
    return true;
}

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

void Cluster::auxiliar_imprimir_estructura_cluster(const BinTree<map<string, Procesador>::iterator> &arbol) {
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

void Cluster::compactar_memoria_procesador(const string& id_procesador, int& error) {
    map<string, Procesador>::iterator it = mapa_procesadores.find(id_procesador);
    if (it == mapa_procesadores.end()) error = PROCESADOR_INEXISTENTE;
    else it->second.compactar_memoria();
}

void Cluster::compactar_memoria_cluster() {
    for (
        map<string, Procesador>::iterator it = mapa_procesadores.begin();
        it != mapa_procesadores.end();
        ++it
    ) it->second.compactar_memoria();
}