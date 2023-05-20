/** @file Proceso.hh
    @brief Especificación de la clase Proceso.
*/

#ifndef PROCESO_HH
#define PROCESO_HH

/** @class Proceso
    @brief Representa una proceso computacional que puede ser ejecutado en un
           procesador.

           Ocupa un cierto espacio en memoria y tiene un cierto tiempo estimado
           de ejecución.
*/
class Proceso {

    private:

        /** @brief Identificador del proceso. */
        int id;

        /** @brief Memoria que ocupa el proceso en un procesador. */
        int memoria;

        /** @brief Tiempo estimado restante de ejecución. */
        int tiempo_estimado;

    public:

        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al
                   declarar un proceso sin pasar parámetros.

            \pre Cierto.

            \post El resultado es un proceso no inicializado.
        */
        Proceso();

        /** @brief Constructora inicializadora.

            \pre id >= 0, memoria > 0, tiempo_estimado > 0.

            \post El resultado es un proceso inicializado con identificador,
                  memoria y tiempo de ejecución estimado.
        */  
        Proceso(int id, int memoria, int tiempo_estimado);

        // CONSULTORAS ########################################################
        
        /** @brief Consultora del identificador.

            \pre El parámetro implícito está inicializado.

            \post El resultado es el identificador del parámetro implícito.
        */
        int consultar_id() const;

        /** @brief Consulta si un cierto identificador coincide con el del
                   parámetro implícito.

            \pre El parámetro implícito está inicializado.

            \post El resultado indica si el identificador del parámetro
                  implícito coincide con id_proceso.
        */
        bool id_coincide(int id_proceso) const;

        /** @brief Consultora de memoria.
            
            \pre El parámetro implícito está inicializado.

            \post El resultado es la memoria del proceso.
        */
        int consultar_memoria() const;
        
        // MODIFICADORAS ######################################################

        /** @brief Avanza el tiempo de ejecución.

            \pre t >= 0.

            \post tiempo_estimado = tiempo_estimado - t.
                  El resultado indica si tiempo_estimado > 0.
        */
        bool avanzar_tiempo(int t);


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime el parámetro implícito por el canal de salida
                   estándar.

            \pre El parámetro implícito está inicializado.

            \post Quedan escritos en el canal de salida estándar el
                  identificador, la memoria, y el tiempo restante estimado de
                  ejecución del parámetro implícito.
        */
        void imprimir() const;
};

#endif