/** @file Proceso.hh
    @brief Especificación de la clase Proceso.
*/

using namespace std;

/** @class Proceso
    @brief Representa una proceso computacional que puede ser ejecutado en un procesador.

    ...
*/
class Proceso {
    private:
        int id, memoria, tiempo_ejecucion;

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al declarar un Proceso.
            \pre cierto.
            \post El resultado es un Proceso no inicializado.
        */
        Proceso();

        /** @brief Constructora inicializadora de identificador, memoria y tiempo de ejecución.
            \pre id >= 0, memoria > 0, tiempo_ejecucion > 0
            \post El resultado es un Proceso inicializado con identificador, memoria y tiempo de ejecución.
        */  
        Proceso(int id, int memoria, int tiempo_ejecucion);

        // CONSULTORAS ########################################################
        
        /** @brief Consulta el identificador del parámetro implícito.
            \pre El parámetro implícito está inicializado.
            \post El resultado es el identificador del parámetro implícito.
        */
        int consultar_id() const;

        /** @brief Consulta si un identificador coincide con el del parámetro implícito.
            \pre El parámetro implícito está inicializado. id_proceso >= 0.
            \post El resultado indica si el id del parámetro implícito coincide con id_proceso.
        */
        bool id_coincide(int id_proceso) const;

        /** @brief Consulta si tiempo_ejecucion es mayor que t.
            \pre El parámetro implícito está inicializado. t >= 0.
            \post El resultado indica si tiempo_ejecucion del parámetro implícito es mayor que t.
        */
        bool queda_tiempo_ejecucion(int t) const;
        
        
        // MODIFICADORAS ######################################################

        /** @brief Avanza el tiempo que ha transcurrido en la simulación del proceso.
            \pre tiempo_ejecucion > t >= 0.
            \post tiempo_ejecucion -= t.
        */
        void avanzar_tiempo(int t);


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime el parámetro implícito por el canal de salida estándar.
            \pre El parámetro implícito está inicializado.
            \post Quedan escritos en el canal de salida estándar el identificador, la memoria, y el tiempo que queda de ejecución del parámetro implícito.
        */
        void imprimir() const;
};