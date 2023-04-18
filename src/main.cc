/** @mainpage Simulación del rendimiento de procesadores interconectados. 
    Amadeu Moya Sardà, grupo 12. Cuatrimestre Primavera 2023. FIB UPC.

    @file main.cc
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

/** @brief Programa principal de la práctica de PRO2 (Simulación del rendimiento de procesadores interconectados).
*/
int main() {
    Cluster cluster;
    ProcesosPendientes pendientes;

    cluster.configurar_cluster();
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int error;
        string id_prioridad;
        cin >> id_prioridad;
        pendientes.alta_prioridad(id_prioridad, error);
    }

    string comando;
    cin >> comando;

    while (comando != "fin") {

        int error = NO_HAY_ERROR; // se pasa como parámetro por referencia de salida para determinar los posibles casos de error de la función.

        if (comando == "configurar_cluster" or comando == "cc") {
            // Se garantiza que los identificadores de los procesadores no están repetidos
            cluster.configurar_cluster();
        }

        else if (comando == "modificar_cluster" or comando == "mc") {
            //tener en cuenta el caso en que te entre un arbol vacío, borrar el procesador, maybe a ver como es el juego de pruebas
            //implementar errores en modificar_cluster para cuando no se cumple la pre
            string p;
            cin >> p;
            cluster.modificar_cluster(p, error);

            if (error == PROCESADOR_INEXISTENTE) cout << "pendiente del juego de pruebas" << endl;
            else if (error == PROCESOS_EN_EJECUCION) cout << "pendiente del juego de pruebas" << endl;
            else if (error == TIENE_PROCESADORES_AUXILIARES) cout << "pendiente del juego de pruebas" << endl;
        }

        else if (comando == "alta_prioridad" or comando == "ap") {
            string id_prioridad;
            cin >> id_prioridad;
            pendientes.alta_prioridad(id_prioridad, error);

            if (error == PRIORIDAD_EXISTENTE) cout << "pendiente del juego de pruebas" << endl;
        }

        else if (comando == "baja_prioridad" or comando == "bp") {
            string id_prioridad;
            cin >> id_prioridad;
            pendientes.baja_prioridad(id_prioridad, error);

            if (error == PRIORIDAD_INEXISTENTE) cout << "pendiente del juego de pruebas" << endl;
            else if (error == PRIORIDAD_CON_PROCESOS_PENDIENTES) cout << "pendiente del juego de pruebas" << endl;
        }

        else if (comando == "alta_proceso_espera" or comando == "ape") {
            int id_proceso, memoria, tiempo_estimado;
            string id_prioridad;
            cin >> id_proceso >> memoria >> tiempo_estimado >> id_prioridad;
            Proceso proceso(id_proceso, memoria, tiempo_estimado);
            pendientes.alta_proceso_espera(proceso, id_prioridad, error);

            if (error == PRIORIDAD_INEXISTENTE) cout << "pendiente del juego de pruebas" << endl;
            else if (error == PROCESO_EXISTENTE_EN_PRIORIDAD) cout << "pendiente del juego de pruebas" << endl;
        }

        else if (comando == "alta_proceso_procesador" or comando == "app") {
            string id_procesador;
            int id_proceso, memoria, tiempo_estimado;
            cin >> id_procesador >> id_proceso >> memoria >> tiempo_estimado;
            Proceso proceso(id_proceso, memoria, tiempo_estimado);
            cluster.alta_proceso_procesador(proceso, id_procesador, error);

            if (error == PROCESADOR_INEXISTENTE) cout << "error: no existe procesador" << endl;
            else if (error == PROCESO_EXISTENTE_EN_PROCESADOR) cout << "error: ya existe proceso" << endl;
            else if (error == PROCESO_NO_COLOCABLE) cout << "error: no cabe proceso" << endl;
        }

        else if (comando == "baja_proceso_procesador" or comando == "bpp") {
            string id_procesador;
            int id_proceso;
            cin >> id_procesador >> id_proceso;
            cluster.baja_proceso_procesador(id_proceso, id_procesador, error);

            if (error == PROCESADOR_INEXISTENTE) cout << "error: no existe procesador" << endl;
            else if (error == PROCESO_INEXISTENTE_EN_PROCESADOR) cout << "error: no existe proceso" << endl;
        }

        else if (comando == "enviar_procesos_cluster" or comando == "epc") {
            int n;
            cin >> n;
            pendientes.enviar_procesos_cluster(n, cluster);
        }

        else if (comando == "avanzar_tiempo" or comando == "at") {
            int t;
            cin >> t;
            cluster.avanzar_tiempo(t);
        }

        else if (comando == "imprimir_prioridad" or comando == "ipri") {
            string id_prioridad;
            cin >> id_prioridad;
            pendientes.imprimir_prioridad(id_prioridad, error);

            if (error == PRIORIDAD_INEXISTENTE) cout << "pendiente del juego de pruebas" << endl;
        }

        else if (comando == "imprimir_area_espera" or comando == "iae") {
            pendientes.imprimir_area_espera();
        }

        else if (comando == "imprimir_procesador" or comando == "ipro") {
            string id_procesador;
            cin >> id_procesador;
            cluster.imprimir_procesador(id_procesador, error);

            if (error == PROCESADOR_INEXISTENTE) cout << "error: no existe procesador" << endl;
        }

        else if (comando == "imprimir_procesadores_cluster" or comando == "ipc") {
            cluster.imprimir_procesadores_cluster();
        }

        else if (comando == "imprimir_estructura_cluster" or comando == "iec") {
            cluster.imprimir_estructura_cluster();
        }

        else if (comando == "compactar_memoria_procesador" or comando == "cmp") {
            string id_procesador;
            cin >> id_procesador;
            cluster.compactar_memoria_procesador(id_procesador, error);

            if (error == PROCESADOR_INEXISTENTE) cout << "pendiente del juego de pruebas" << endl;
        }
        
        else if (comando == "compactar_memoria_cluster" or comando == "cmc") {
            cluster.compactar_memoria_cluster();
        }

        cin >> comando;
    }
}
