/** @file Procesador.hh
    @brief Especificación de la clase Procesador.
*/

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <string>
#endif

using namespace std;


/** @class Procesador
    @brief Representa un procesador que puede ejecutar múltiples Proceso
           simultáneamente.
*/
class Procesador {
    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al
                   declarar un Procesador.

            \pre Cierto.

            \post El resultado es un Procesador no inicializado.
        */  
        Procesador();

        /** @brief Constructora inicializadora de identificador y memoria.

            \pre id_procesador contiene únicamente letras y números.
                 memoria > 0.

            \post El resultado es un Procesador inicializado con identificador
                  y memoria.
        */  
        Procesador(const string& id_procesador, int memoria);


        // CONSULTORAS ########################################################

        /** @brief Consulta si un determinado identificador coincide con el del
                   parámetro implícito.

            \pre El parámetro implícito está inicializado. id_procesador
                 contiene únicamente letras y números.

            \post El resultado indica si el identificador del parámetro
                  implícito coincide con id_procesador.
        */
        bool id_coincide(const string& id_procesador) const;

        /** @brief Consulta si un determinado Proceso se encuentra ejecutándose
                   en el parámetro implícito.

            \pre El parámetro implícito está inicializado. id_proceso >= 0.

            \post El resultado indica si existe un Proceso con identificador
                  igual a id_proceso ejecutándose en el parámetro implícito.
        */
        bool existe_id_proceso(int id_proceso) const;

        /** @brief Consulta si existe algún Proceso activo en el parámetro
                   implícito.

            \pre El parámetro implícito está inicializado.

            \post El resultado indica si existe algún Proceso ejecutándose en
                  el parámetro implícito.
        */
        bool hay_procesos() const;

        /** @brief Consulta si un determinado Proceso se puede colocar en la
                   memoria del parámetro implícito.

            \pre El parámetro implícito está inicializado.

            \post El resultado indica si proceso se puede colocar en la memoria
                  del parámetro implícito.
        */
        bool se_puede_colocar(const Proceso& proceso) const;


        // MODIFICADORAS ######################################################

        /** @brief Avanza el tiempo que ha transcurrido en la ejecución de los
                   Proceso del parámetro implícito.

            \pre El parámetro implícito está inicializado. t >= 0.

            \post El tiempo estimado de los Proceso del parámetro implícito se
                  ha visto decrementado en t. Si un Proceso tenía un tiempo
                  estimado menor que t se ha liberado de la memoria.
        */
        void avanzar_tiempo(int t);

        /** @brief Compacta los Proceso en memoria del parámetro implícito.
         
            \pre Cierto.

            \post Los Proceso en memoria del parámetro implícito quedan
                  compactados hacia el comienzo de la memoria sin dejar huecos,
                  sin solaparse, y respetando el orden inicial.
        */
        void compactar_memoria();


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime el parámetro implícito por el canal de salida
                   estándar.

            \pre El parámetro implícito está inicializado.

            \post Quedan escritos en el canal de salida estándar los Proceso
                  del parámetro implícito en orden creciente de primera
                  posición de memoria, incluyendo dicha posición.
        */
        void imprimir() const;
};