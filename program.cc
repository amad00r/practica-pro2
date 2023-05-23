/** @mainpage Simulación del rendimiento de procesadores interconectados. 
    Amadeu Moya Sardà, grupo 12. Cuatrimestre Primavera 2023. FIB UPC.

    @file program.cc

    @brief Programa principal de la práctica de PRO2 (Simulación del rendimiento de procesadores interconectados).
*/

#include "ProcesosPendientes.hh"
#include "Cluster.hh"
#include "Proceso.hh"
#include "Errores.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#endif

using namespace std;

int main() {
    Cluster cluster;
    ProcesosPendientes pendientes;

    string comando;
    cin >> comando;

    while (comando != "fin") {

        int error = OK;

        if (comando == "configurar_cluster" or comando == "cc") {
            cout << "#" << comando << endl;
            cluster.configurar_cluster();
        }

        else if (comando == "modificar_cluster" or comando == "mc") {
            string id_procesador;
            cin >> id_procesador;
            cout << "#" << comando << " " << id_procesador << endl;

            cluster.modificar_cluster(id_procesador, error);

            if      (error == PROCESADOR_INEXISTENTE)        cout << "error: no existe procesador"      << endl;
            else if (error == PROCESOS_EN_EJECUCION)         cout << "error: procesador con procesos"   << endl;
            else if (error == TIENE_PROCESADORES_AUXILIARES) cout << "error: procesador con auxiliares" << endl;
        }

        else if (comando == "alta_prioridad" or comando == "ap") {
            string id_prioridad;
            cin >> id_prioridad;
            cout << "#" << comando << " " << id_prioridad << endl;

            pendientes.alta_prioridad(id_prioridad, error);

            if (error == PRIORIDAD_EXISTENTE) cout << "error: ya existe prioridad" << endl;
        }

        else if (comando == "baja_prioridad" or comando == "bp") {
            string id_prioridad;
            cin >> id_prioridad;
            cout << "#" << comando << " " << id_prioridad << endl;

            pendientes.baja_prioridad(id_prioridad, error);

            if      (error == PRIORIDAD_INEXISTENTE)             cout << "error: no existe prioridad"    << endl;
            else if (error == PRIORIDAD_CON_PROCESOS_PENDIENTES) cout << "error: prioridad con procesos" << endl;
        }

        else if (comando == "alta_proceso_espera" or comando == "ape") {
            string id_prioridad;
            int id_proceso, memoria, tiempo_estimado;
            cin >> id_prioridad >> id_proceso >> memoria >> tiempo_estimado;
            cout << "#" << comando << " " << id_prioridad << " " << id_proceso << endl;

            Proceso proceso(id_proceso, memoria, tiempo_estimado);
            pendientes.alta_proceso_espera(proceso, id_prioridad, error);

            if      (error == PRIORIDAD_INEXISTENTE)          cout << "error: no existe prioridad" << endl;
            else if (error == PROCESO_EXISTENTE_EN_PRIORIDAD) cout << "error: ya existe proceso"   << endl;
        }

        else if (comando == "alta_proceso_procesador" or comando == "app") {
            string id_procesador;
            int id_proceso, memoria, tiempo_estimado;
            cin >> id_procesador >> id_proceso >> memoria >> tiempo_estimado;
            cout << "#" << comando << " " << id_procesador << " " << id_proceso << endl;

            Proceso proceso(id_proceso, memoria, tiempo_estimado);
            cluster.alta_proceso_procesador(proceso, id_procesador, error);

            if      (error == PROCESADOR_INEXISTENTE)          cout << "error: no existe procesador" << endl;
            else if (error == PROCESO_EXISTENTE_EN_PROCESADOR) cout << "error: ya existe proceso"    << endl;
            else if (error == PROCESO_NO_COLOCABLE)            cout << "error: no cabe proceso"      << endl;
        }

        else if (comando == "baja_proceso_procesador" or comando == "bpp") {
            string id_procesador;
            int id_proceso;
            cin >> id_procesador >> id_proceso;
            cout << "#" << comando << " " << id_procesador << " " << id_proceso << endl;

            cluster.baja_proceso_procesador(id_proceso, id_procesador, error);

            if      (error == PROCESADOR_INEXISTENTE)            cout << "error: no existe procesador" << endl;
            else if (error == PROCESO_INEXISTENTE_EN_PROCESADOR) cout << "error: no existe proceso"    << endl;
        }

        else if (comando == "enviar_procesos_cluster" or comando == "epc") {
            int n;
            cin >> n;
            cout << "#" << comando << " " << n << endl;

            pendientes.enviar_procesos_cluster(n, cluster);
        }

        else if (comando == "avanzar_tiempo" or comando == "at") {
            int t;
            cin >> t;
            cout << "#" << comando << " " << t << endl;

            cluster.avanzar_tiempo(t);
        }

        else if (comando == "imprimir_prioridad" or comando == "ipri") {
            string id_prioridad;
            cin >> id_prioridad;
            cout << "#" << comando << " " << id_prioridad << endl;

            pendientes.imprimir_prioridad(id_prioridad, error);

            if (error == PRIORIDAD_INEXISTENTE) cout << "error: no existe prioridad" << endl;
        }

        else if (comando == "imprimir_area_espera" or comando == "iae") {
            cout << "#" << comando << endl;
            pendientes.imprimir_area_espera();
        }

        else if (comando == "imprimir_procesador" or comando == "ipro") {
            string id_procesador;
            cin >> id_procesador;
            cout << "#" << comando << " " << id_procesador << endl;

            cluster.imprimir_procesador(id_procesador, error);

            if (error == PROCESADOR_INEXISTENTE) cout << "error: no existe procesador" << endl;
        }

        else if (comando == "imprimir_procesadores_cluster" or comando == "ipc") {
            cout << "#" << comando << endl;
            cluster.imprimir_procesadores_cluster();
        }

        else if (comando == "imprimir_estructura_cluster" or comando == "iec") {
            cout << "#" << comando << endl;
            cluster.imprimir_estructura_cluster();
        }

        else if (comando == "compactar_memoria_procesador" or comando == "cmp") {
            string id_procesador;
            cin >> id_procesador;
            cout << "#" << comando << " " << id_procesador << endl;

            cluster.compactar_memoria_procesador(id_procesador, error);

            if (error == PROCESADOR_INEXISTENTE) cout << "error: no existe procesador" << endl;
        }
        
        else if (comando == "compactar_memoria_cluster" or comando == "cmc") {
            cout << "#" << comando << endl;
            cluster.compactar_memoria_cluster();
        }

        cin >> comando;
    }
}
