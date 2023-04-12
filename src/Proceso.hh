#pragma once

/** @file Proceso.hh
    @brief Especificación de la clase Proceso.
*/


/** @class Proceso
    @brief Representa una proceso computacional que puede ser ejecutado en un Procesador.

    Ocupa un determinado espacio en memoria y tiene un determinado tiempo estimado de ejecución.
*/
class Proceso {
    private:
        int id, memoria, tiempo_estimado;

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al
                   declarar un Proceso sin pasar parámetros.

            \pre Cierto.

            \post El resultado es un Proceso no inicializado.
        */
        Proceso();

        /** @brief Constructora inicializadora de identificador, memoria y
                   tiempo de ejecución estimado.

            \pre id >= 0, memoria > 0, tiempo_estimado > 0.

            \post El resultado es un Proceso inicializado con identificador,
                  memoria y tiempo de ejecución estimado.
        */  
        Proceso(int id, int memoria, int tiempo_estimado);


        // CONSULTORAS ########################################################
        
        /** @brief Consulta el identificador del parámetro implícito.

            \pre El parámetro implícito está inicializado.

            \post El resultado es el identificador del parámetro implícito.
        */
        int consultar_id() const;

        /** @brief Consulta si un determinado identificador coincide con el del
                   parámetro implícito.

            \pre El parámetro implícito está inicializado. id_proceso >= 0.

            \post El resultado indica si el identificador del parámetro
                  implícito coincide con id_proceso.
        */
        bool id_coincide(int id_proceso) const;

        int consultar_memoria() const;
        
        
        // MODIFICADORAS ######################################################

        /** @brief Avanza el tiempo que ha transcurrido en la ejecución del
                   parámetro implícito.

            \pre t >= 0.

            \post tiempo_estimado = tiempo_estimado - t. El resultado indica si
                  tiempo_estimado > 0.
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