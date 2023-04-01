#include "Cluster.hh"
#include "ProcesosPendientes.hh"
#include "Proceso.hh"

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

        if (comando == "configurar_cluster" or comando == "cc") {
            // Se garantiza que los identificadores de los procesadores no están repetidos
            cluster.configurar_cluster();
        }

        else if (comando == "modificar_cluster" or comando == "mc") {
            //tener en cuenta el caso en que te entre un arbol vacío, borrar el procesador, maybe a ver como es el juego de pruebas
            //implementar errores en modificar_cluster para cuando no se cumple la pre
            string p;
            cin >> p;
            cluster.modificar_cluster(p);
        }

        else if (comando == "alta_prioridad" or comando == "ap") {
            string id_prioridad;
            cin >> id_prioridad;
            pendientes.alta_prioridad(id_prioridad);
        }

        else if (comando == "baja_prioridad" or comando == "bp") {
            string id_prioridad;
            cin >> id_prioridad;
            pendientes.baja_prioridad(id_prioridad);
        }

        else if (comando == "alta_proceso_espera" or comando == "ape") {
            int id_proceso, memoria, tiempo_ejecucion;
            string id_prioridad;
            cin >> id_proceso >> memoria >> tiempo_ejecucion >> id_prioridad;
            pendientes.alta_proceso_espera(Proceso(id_proceso, memoria, tiempo_ejecucion), id_prioridad);
        }

        else if (comando == "alta_proceso_procesador" or comando == "apendientes") {
            string id_procesador;
            int id_proceso, memoria, tiempo_ejecucion;
            cin >> id_procesador >> id_proceso >> memoria >> tiempo_ejecucion;
            cluster.alta_proceso_procesador(Proceso(id_proceso, memoria, tiempo_ejecucion), id_procesador);
        }

        else if (comando == "baja_proceso_procesador" or comando == "bpendientes") {
            string id_procesador;
            int id_proceso, memoria, tiempo_ejecucion;
            cin >> id_procesador >> id_proceso >> memoria >> tiempo_ejecucion;
            cluster.baja_proceso_procesador(Proceso(id_proceso, memoria, tiempo_ejecucion), id_procesador);
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
            pendientes.imprimir_prioridad(id_prioridad);
        }

        else if (comando == "imprimir_area_espera" or comando == "iae") {
            pendientes.imprimir_area_espera();
        }

        else if (comando == "imprimir_procesador" or comando == "ipro") {
            string id_procesador;
            cin >> id_procesador;
            cluster.imprimir_procesador(id_procesador);
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
            cluster.compactar_memoria_procesador(id_procesador);
        }
        
        else if (comando == "compactar_memoria_cluster" or comando == "cmc") {
            cluster.compactar_memoria_cluster();
        }

        cin >> comando;
    }
}
