/** @file Procesador.hh
    @brief Especificación de la clase Procesador.
*/

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <list>
#endif

using namespace std;


/** @class Procesador
    @brief Representa un procesador que puede ejecutar procesos simultáneamente.

    ...
*/
class Procesador {
    private:
        string id;
        unsigned int memoria;
        list< pair<unsigned int, Proceso> > procesos_memoria;

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al declarar un Procesador.
            \pre cierto.
            \post El resultado es un Procesador no inicializado.
        */  
        Procesador();

        /** @brief Constructora inicializadora de identificador y memoria.
            \pre cierto.
            \post El resultado es un Procesador inicializado con identificador y memoria.
        */  
        Procesador(const string& id_procesador, unsigned int memoria);


        // CONSULTORAS ########################################################

        /** @brief Consulta si un identificador coincide con el del parámetro implícito.
            \pre El parámetro implícito está inicializado.
            \post El resultado indica si el id del parámetro implícito coincide con id_procesador.
        */
        ////////se podria hacer una sobrecarga de ==
        bool id_coincide(const string& id_procesador) const;

        /** @brief Consulta si un cierto Proceso en el parámetro implícito.
            \pre El parámetro implícito está inicializado.
            \post El resultado indica si existe un Proceso con id = id_proceso ejecutándose en el parámetro implícito.
        */
        bool existe_id_proceso(const string& id_proceso) const;

        /** @brief Consulta si existen procesos activos en el parámetro implícito.
            \pre El parámetro implícito está inicializado.
            \post El resultado indica si hay procesos ejecutándose en el parámetro implícito.
        */
        bool hay_procesos() const;

        /** @brief Consulta si un cierto proceso se puede colocar en la memoria del parámetro implícito.
            \pre El parámetro implícito está inicializado.
            \post El resultado indica si proceso se puede colocar en la memoria del parámetro implícito.
        */
        bool se_puede_colocar(const Proceso& proceso) const;


        // MODIFICADORAS ######################################################

        /** @brief Avanza el tiempo que ha transcurrido en la simulación de los procesos del parámetro implícito.
            \pre El parámetro implícito está inicializado.
            \post Todos los procesos del parámetro implícito incrementan en t unidades de tiempo el tiempo que llevan ejecutándose.
        */
        void avanzar_tiempo(unsigned int t);

        /** @brief Compacta los procesos en memoria del parámetro implícito.
            \pre cierto.
            \post Los procesos en memoria del parámetro implícito quedan compactados hacia el comienzo de la memoria sin dejar huecos, sin solaparse, y respetando el orden inicial.
        */
        void compactar_memoria();


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime el parámetro implícito por el canal de salida estándar.
            \pre El parámetro implícito está inicializado.
            \post Quedan escritos en el canal de salida estándar los procesos del parámetro implícito en orden creciente de primera posición de memoria, incluyendo dicha posición.
        */
        void imprimir() const;
};