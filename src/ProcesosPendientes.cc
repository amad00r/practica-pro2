#include "ProcesosPendientes.hh"
#include "Proceso.hh"
#include "Cluster.hh"
#include "Errores.hh"

#include <iostream>
#include <string>
#include <list>

using namespace std;

ProcesosPendientes::ProcesosPendientes() {}

void ProcesosPendientes::alta_prioridad(const string &id_prioridad, int &error) {
    map<string, Prioridad>::iterator it = mapa_prioridades.find(id_prioridad);

    if (it == mapa_prioridades.end()) mapa_prioridades.insert(make_pair(id_prioridad, Prioridad()));
    else                              error = PRIORIDAD_EXISTENTE;
}

void ProcesosPendientes::baja_prioridad(const string &id_prioridad, int &error) {
    map<string, Prioridad>::iterator it = mapa_prioridades.find(id_prioridad);

    if      (it == mapa_prioridades.end())             error = PRIORIDAD_INEXISTENTE;
    else if (not it->second.conjunto_procesos.empty()) error = PRIORIDAD_CON_PROCESOS_PENDIENTES;
    else                                               mapa_prioridades.erase(it);
}

void ProcesosPendientes::alta_proceso_espera(const Proceso &proceso, const string &id_prioridad, int &error) {
    map<string, Prioridad>::iterator it = mapa_prioridades.find(id_prioridad);

    if      (it == mapa_prioridades.end())                                       error = PRIORIDAD_INEXISTENTE;
    else if (it->second.conjunto_procesos.insert(proceso.consultar_id()).second) it->second.lista_procesos.push_back(proceso);
    else                                                                         error = PROCESO_EXISTENTE_EN_PRIORIDAD;
}

void ProcesosPendientes::enviar_procesos_cluster(int n, Cluster &cluster) {
    for (
        map<string, Prioridad>::iterator it = mapa_prioridades.begin();
        n != 0 and it != mapa_prioridades.end();
        ++it
    ) {
        for (int i = it->second.lista_procesos.size(); n != 0 and i > 0; --i) {
            if (cluster.alta_proceso(it->second.lista_procesos.front())) {
                --n;
                ++it->second.procesos_colocados;
                it->second.conjunto_procesos.erase(it->second.lista_procesos.front().consultar_id());
            }
            else {
                ++it->second.procesos_rechazados;
                it->second.lista_procesos.push_back(it->second.lista_procesos.front());
            }
            it->second.lista_procesos.pop_front();
        }
    }
}

void ProcesosPendientes::auxiliar_imprimir_prioridad(
    const map<string, Prioridad>::const_iterator &it_prioridad
) const {
    list<Proceso>::const_iterator it = it_prioridad->second.lista_procesos.begin();
    while (it != it_prioridad->second.lista_procesos.end()) {
        it->imprimir();
        ++it;
    }
    cout << it_prioridad->second.procesos_colocados << " "
         << it_prioridad->second.procesos_rechazados << endl;
}

void ProcesosPendientes::imprimir_prioridad(const string &id_prioridad, int &error) const {
    map<string, Prioridad>::const_iterator it = mapa_prioridades.find(id_prioridad);

    if (it == mapa_prioridades.end()) error = PRIORIDAD_INEXISTENTE;
    else                              auxiliar_imprimir_prioridad(it);
}

void ProcesosPendientes::imprimir_area_espera() const {
    for (
        map<string, Prioridad>::const_iterator it = mapa_prioridades.begin();
        it != mapa_prioridades.end();
        ++it
    ) {
        cout << it->first << endl;
        auxiliar_imprimir_prioridad(it);
    }
}