#include "ProcesosPendientes.hh"
#include "Proceso.hh"
#include "Cluster.hh"
#include "Errores.hh"

#include <iostream>
#include <string>
#include <queue>
#include <list>

using namespace std;

ProcesosPendientes::ProcesosPendientes() {}

/* bool ProcesosPendientes::existe_prioridad(const string& id_prioridad) const {
    return mapa_prioridades.find(id_prioridad) != mapa_prioridades.end();
} */

void ProcesosPendientes::alta_prioridad(const string& id_prioridad, int& error) {
    map<string, Prioridad>::iterator it_prioridad = mapa_prioridades.find(id_prioridad);
    if (it_prioridad == mapa_prioridades.end()) mapa_prioridades.insert(make_pair(id_prioridad, Prioridad()));
    else error = PRIORIDAD_EXISTENTE;
}

void ProcesosPendientes::baja_prioridad(const string& id_prioridad, int& error) {
    map<string, Prioridad>::iterator it_prioridad = mapa_prioridades.find(id_prioridad);

    if (it_prioridad == mapa_prioridades.end())
        error = PRIORIDAD_INEXISTENTE;
    else if (not it_prioridad->second.procesos.empty())
        error = PRIORIDAD_CON_PROCESOS_PENDIENTES;
    else
        mapa_prioridades.erase(it_prioridad);
}

bool ProcesosPendientes::existe_proceso_en_prioridad(
    int id_proceso,
    const map<string, Prioridad>::const_iterator& it_prioridad
) const {
    list<Proceso>::const_iterator it = it_prioridad->second.procesos.begin();
    while (it != it_prioridad->second.procesos.end()) {
        if (it->id_coincide(id_proceso)) return true;
        ++it;
    }
    return false;
}

void ProcesosPendientes::alta_proceso_espera(const Proceso& proceso, const string& id_prioridad, int& error) {
    map<string, Prioridad>::iterator it_prioridad = mapa_prioridades.find(id_prioridad);

    if (it_prioridad == mapa_prioridades.end())
        error = PRIORIDAD_INEXISTENTE;
    else if (existe_proceso_en_prioridad(proceso.consultar_id(), it_prioridad))
        error = PROCESO_EXISTENTE_EN_PRIORIDAD;
    else
        it_prioridad->second.procesos.push_back(proceso);
}

void ProcesosPendientes::enviar_procesos_cluster(int n, const Cluster& cluster) {
    ;//implementar
}

void ProcesosPendientes::auxiliar_imprimir_prioridad(
    const map<string, Prioridad>::const_iterator &it_prioridad
) const {
    list<Proceso>::const_iterator it = it_prioridad->second.procesos.begin();
    while (it != it_prioridad->second.procesos.end()) {
        it->imprimir();
        ++it;
    }
    cout << it_prioridad->second.procesos_colocados << " "
         << it_prioridad->second.procesos_rechazados << endl;
}

void ProcesosPendientes::imprimir_prioridad(const string& id_prioridad, int& error) const {
    map<string, Prioridad>::const_iterator it_prioridad = mapa_prioridades.find(id_prioridad);

    if (it_prioridad == mapa_prioridades.end())
        error = PRIORIDAD_INEXISTENTE;
    else
        auxiliar_imprimir_prioridad(it_prioridad);
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