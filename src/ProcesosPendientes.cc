#include "ProcesosPendientes.hh"
#include "Proceso.hh"
#include "Cluster.hh"
#include "Errores.hh"

#include <iostream>
#include <string>
#include <queue>

using namespace std;

ProcesosPendientes::ProcesosPendientes() {}

bool ProcesosPendientes::existe_prioridad(const string& id_prioridad) const {
    return mapa_prioridades.find(id_prioridad) != mapa_prioridades.end();
}

void ProcesosPendientes::alta_prioridad(const string& id_prioridad, int& error) {
    if (existe_prioridad(id_prioridad)) error = PRIORIDAD_EXISTENTE;
    else mapa_prioridades[id_prioridad];
}

void ProcesosPendientes::baja_prioridad(const string& id_prioridad, int& error) {
    if (
        existe_prioridad(id_prioridad) and 
        mapa_prioridades[id_prioridad].procesos.empty()
    ) mapa_prioridades.erase(id_prioridad);
    //else cout << "error" << endl; //imprimir error
}

bool ProcesosPendientes::existe_proceso_en_prioridad(
    int id_proceso,
    const map<string, Prioridad>::const_iterator& it_prioridad
) const {
    queue<Proceso> cola_procesos = queue<Proceso>(it_prioridad->second.procesos);
    while (not cola_procesos.empty()) {
        if (cola_procesos.front().id_coincide(id_proceso)) return true;
        cola_procesos.pop();
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
        it_prioridad->second.procesos.push(proceso);
}

void ProcesosPendientes::enviar_procesos_cluster(int n, const Cluster& cluster) {
    ;//implementar
}

void ProcesosPendientes::imprimir_prioridad(const string& id_prioridad, int& error) const {
    map<string, Prioridad>::const_iterator it_prioridad = mapa_prioridades.find(id_prioridad);

    if (it_prioridad == mapa_prioridades.end())
        error = PRIORIDAD_INEXISTENTE;
    else {
        queue<Proceso> cola_procesos = queue<Proceso>(it_prioridad->second.procesos);
        while (not cola_procesos.empty()) {
            cola_procesos.front().imprimir();
            cola_procesos.pop();
        }
        cout << it_prioridad->second.procesos_colocados << " "
             << it_prioridad->second.procesos_rechazados << endl;
    }
}

void ProcesosPendientes::imprimir_area_espera() const {
    for (
        map<string, Prioridad>::const_iterator it = mapa_prioridades.begin();
        it != mapa_prioridades.end();
        ++it
    ) {
        cout << it->first << endl;
        int error;
        imprimir_prioridad(it->first, error);
    }
}