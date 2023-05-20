/** @file Procesador.hh
    @brief Especificación de la clase Procesador.
*/

#ifndef PROCESADOR_HH
#define PROCESADOR_HH

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <map>
#include <set>
#endif

using namespace std;

/** @class Procesador
    @brief Representa un procesador que puede ejecutar múltiples Proceso
           simultáneamente.
*/
class Procesador {

    private:
        /** @brief Capacidad total de la memoria del procesador. */
        int memoria;

        /** @brief Memoria disponible (no usada por un proceso). */
        int memoria_disponible;

        /** @brief Posiciones de memoria relacionadas con el proceso que en
                   ellas se encuentran ejecutándose.
         */
        map<int, Proceso> procesos_memoria;

        /** @brief Identificadores de procesos relacionados con la posiciones
                   en memoria dónde se encuentran ejecutándose.
        */
        map<int, int> posiciones_procesos;
        
        /** @brief Tamaños de huecos relacionados con la colección de
                   posiciones en memoria dónde se encuentran todos los huecos
                   con dicho tamaño.
         */
        map<int, set<int>> huecos_memoria;

        // MODIFICADORAS ######################################################

        /** @brief Recalcula los huecos existentes en la memoria.

            \pre Cierto.

            \post huecos_memoria contiene los huecos que existen entre los
                  procesos de procesos_memoria.
        */  
        void recalcular_huecos();

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al
                   declarar un procesador sin pasar parámetros.

            \pre Cierto.

            \post El resultado es un procesador no inicializado.
        */  
        Procesador();

        /** @brief Constructora inicializadora.

            \pre memoria > 0.

            \post El resultado es un procesador inicializado con
                  memoria_disponible=memoria, sin procesos y con un único hueco
                  que ocupa toda la memoria.
        */  
        Procesador(int memoria);


        // CONSULTORAS ########################################################

        /** @brief Consultora del tamaño de hueco más ajustado para una cierta
                   cantidad de memoria.

            \pre memoria > 0.
                 El parámetro implícito está inicializado.

            \post El resultado es el tamaño del hueco del parámetro implícito
                  con tamaño >= proceso_mem más ajustado.
        */  
        int consultar_espacio_hueco_minimo(int proceso_mem) const;

        /** @brief Consultora de la memoria disponible.
            
            \pre El parámetro implícito está inicializado.

            \post El resultado es la cantidad de memoria disponible del
                  parámetro implícito.
         */
        int consultar_memoria_disponible() const;

        /** @brief Consultora de la existecia de un cierto proceso.

            \pre id_proceso >= 0.

            \post El resultado indica si existe un proceso con identificador
                  igual a id_proceso ejecutándose en el parámetro implícito.
        */
        bool existe_id_proceso(int id_proceso) const;

        /** @brief Consultora de la existencia de procesos activos.

            \pre Cierto.

            \post El resultado indica si existe algún proceso ejecutándose en
                  el parámetro implícito.
        */
        bool hay_procesos() const;

        // MODIFICADORAS ######################################################

        /** @brief Avanza el tiempo que ha transcurrido en la ejecución de los
                   procesos.

            \pre t >= 0.

            \post El tiempo estimado de los Proceso del parámetro implícito se
                  ha visto decrementado en t. Si un Proceso tenía un tiempo
                  estimado menor que t se ha liberado de la memoria.
        */
        void avanzar_tiempo(int t);

        /** @brief Da de alta un cierto proceso.
           
            \pre proceso y el parámetro implícito están inicializados.

            \post El resultado es true si el proceso ha sido colocado en el
                  parámetro implícito con éxito. proceso se ha colocado en la
                  posición de memoria más pequeña del parámetro implícito que
                  deja el hueco más ajustado posible.
                  El resultado es false de otra manera.
        */
        bool colocar(const Proceso& proceso);

        /** @brief Da de baja un cierto proceso.
        
            \pre Cierto.

            \post Si el parámetro implícito contiene un proceso con
                  identificador igual a id_proceso, el resultado es true.
                  De otro modo, el resultado es false.
                  No se ejecuta en el parámetro implícito ningún proceso con
                  identificador igual a id_proceso.
        */
        bool quitar(int id_proceso);

        /** @brief Compacta los procesos en memoria.
         
            \pre Cierto.

            \post Los procesos en memoria del parámetro implícito quedan
                  compactados hacia el comienzo de la memoria sin dejar huecos,
                  sin solaparse, y respetando el orden inicial.
        */
        void compactar_memoria();


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime el parámetro implícito por el canal de salida
                   estándar.

            \pre Cierto.

            \post Quedan escritos en el canal de salida estándar los procesos
                  del parámetro implícito en orden creciente de primera
                  posición de memoria, incluyendo dicha posición.
        */
        void imprimir() const;
};

#endif