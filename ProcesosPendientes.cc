#include "ProcesosPendientes.hh"
#include "Proceso.hh"
#include "Cluster.hh"
#include <string>
#include <queue>

using namespace std;

ProcesosPendientes::ProcesosPendientes() {}

bool ProcesosPendientes::existe_prioridad(const string& id_prioridad) {
    return mapa_prioridades.count(id_prioridad) == 1;
}

void ProcesosPendientes::alta_prioridad(const string& id_prioridad) {
    if (not existe_prioridad(id_prioridad)) mapa_prioridades[id_prioridad];
    else cout << "error" << endl; //imprimir mensaje error si ya existe la llave
}

void ProcesosPendientes::baja_prioridad(const string& id_prioridad) {
    if (
        existe_prioridad(id_prioridad) and 
        mapa_prioridades[id_prioridad].procesos.empty()
    ) mapa_prioridades.erase(id_prioridad);
    else cout << "error" << endl; //imprimir error
}

bool ProcesosPendientes::existe_proceso_en_prioridad(unsigned int id_proceso, const string& id_prioridad) {
    queue<Proceso> cola_procesos = queue<Proceso>(mapa_prioridades[id_prioridad].procesos);
    while (not cola_procesos.empty()) {
        if (cola_procesos.front().id_coincide(id_proceso)) return true;
        cola_procesos.pop_front();
    }
    return false;
}

void ProcesosPendientes::alta_proceso_espera(const Proceso& proceso, const string& id_prioridad) {
    if (
        existe_prioridad(id_prioridad) and 
        not existe_proceso_en_prioridad(proceso.consultar_id(), id_prioridad)
    ) mapa_prioridades[id_prioridad].procesos.push_back(proceso);
    else cout << "error" << endl;
}

void ProcesosPendientes::enviar_procesos_cluster(unsigned int n, Cluster& cluster) {
    ;//implementar
}

void ProcesosPendientes::imprimir_prioridad(const string& id_prioridad) const {
    queue<Proceso> cola_procesos = queue<Proceso>(mapa_prioridades[id_prioridad].procesos);
    while (not cola_procesos.empty()) {
        cout << cola_procesos.front().consultar_id() << " ";
    }
    cout << endl;
    cout << mapa_prioridades[id_prioridad].procesos_colocados << " "
         << mapa_prioridades[id_prioridad].procesos_rechazados << endl;
}

void ProcesosPendientes::imprimir_area_espera() const {
    for (map<string, Prioridad>::iterator it = mapa_prioridades.begin(); it != mapa_prioridades.end(); ++it) {
        imprimir_prioridad(it->first);
    }
}