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
        unsigned int id, memoria, tiempo_ejecucion;

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al declarar un Proceso.
            \pre cierto.
            \post El resultado es un Proceso no inicializado.
        */
        Proceso();

        /** @brief Constructora inicializadora de identificador, memoria y tiempo de ejecución.
            \pre cierto.
            \post El resultado es un Proceso inicializado con identificador, memoria y tiempo de ejecución.
        */  
        Proceso(unsigned int id, unsigned int memoria, unsigned int tiempo_ejecucion);

        // CONSULTORAS ########################################################
        
        /** @brief Consulta el identificador del parámetro implícito.
            \pre El parámetro implícito está inicializado.
            \post El resultado es el identificador del parámetro implícito.
        */
        unsigned int consultar_id() const;

        /** @brief Consulta si un identificador coincide con el del parámetro implícito.
            \pre El parámetro implícito está inicializado.
            \post El resultado indica si el id del parámetro implícito coincide con id_proceso.
        */
        bool id_coincide(unsigned int id_proceso) const;

        /** @brief Consulta si tiempo_ejecucion es mayor que t.
            \pre El parámetro implícito está inicializado.
            \post El resultado indica si tiempo_ejecucion del parámetro implícito es mayor que t.
        */
        bool queda_tiempo_ejecucion(unsigned int t) const;
        
        
        // MODIFICADORAS ######################################################

        /** @brief Avanza el tiempo que ha transcurrido en la simulación del proceso.
            \pre tiempo_ejecucion > t.
            \post tiempo_ejecucion -= t.
        */
        void avanzar_tiempo(unsigned int t);


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime el parámetro implícito por el canal de salida estándar.
            \pre El parámetro implícito está inicializado.
            \post Quedan escritos en el canal de salida estándar el identificador, la memoria, y el tiempo que queda de ejecución del parámetro implícito.
        */
        void imprimir() const;
};