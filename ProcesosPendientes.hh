/** @file ProcesosPendientes.hh
    @brief Especificación de la clase ProcesosPendientes.
*/

#include "Proceso.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <queue>
#include <string>
#include <map>
#endif

using namespace std;

/** @class ProcesosPendientes
    @brief Representa una sala de espera de procesos pendientes a ejecutarse.

    En cada momento puede contener un número variable de procesos pendientes con diferentes prioridades.
*/
class ProcesosPendientes {
    private:
    
        struct Prioridad {
            queue<Proceso> procesos;
            int procesos_colocados = 0;
            int procesos_rechazados = 0;
        };
        map<string, Prioridad> mapa_prioridades;


        // CONSULTORAS ########################################################

        /** @brief Consulta si existe una determinada prioridad en el parámetro implícito.
            \pre id_prioridad contiene únicamente letras y números.
            \post El resultado indica si existe una prioridad con identificador igual a id_prioridad en el parámetro implícito.
        */
        bool existe_prioridad(const string& id_prioridad) const;

        /** @brief Consulta si existe un determinado Proceso con una determinada prioridad en el parámetro implícito.
            \pre id_proceso >= 0. Existe una prioridad con identificador igual a id_prioridad en el parámetro implícito. 
            \post El resultado indica si existe el Proceso con identificador igual a id_proceso en la prioridad con identificador igual a id_prioridad en el parámetro implícito.
        */
        bool existe_proceso_en_prioridad(int id_proceso, const string& id_prioridad) const;

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al declarar un ProcesosPendientes.
            \pre Cierto.
            \post El resultado es un ProcesosPendientes sin prioridades ni procesos pendientes.
        */
        ProcesosPendientes();


        // MODIFICADORAS ######################################################

        /** @brief Da de alta una prioridad en el parámetro implícito.
            \pre id_prioridad contiene únicamente letras y números, y no existe una prioridad con identificador igual a id_prioridad en el parámetro implícito.
            \post Existe una prioridad con identificador igual a id_prioridad y sin procesos pendientes en el parámetro implícito.
        */
        void alta_prioridad(const string& id_prioridad, int& error);

        /** @brief Da de baja una prioridad del parámetro implícito.
            \pre Existe una prioridad con identificador igual a id_prioridad, y no tiene procesos pendientes.
            \post No existe una prioridad con identificador igual a id_prioridad en el parámetro implícito.
        */
        void baja_prioridad(const string& id_prioridad, int& error);

        /** @brief Da de alta un proceso en una prioridad del parámetro implícito.
            \pre Existe una prioridad con identificador igual a id_prioridad en el parámetro implícito, y dicha prioridad no tiene asignada ningún Proceso igual a proceso.
            \post La prioridad con identificador igual a id_prioridad del parámetro implícito tiene asignada un Proceso igual a proceso.
        */
        void alta_proceso_espera(const Proceso& proceso, const string& id_prioridad, int& error);

        /** @brief Envía n procesos pendientes a un determinado Cluster para que sean ejecutados.
            \pre n >= 0. cluster está inicializado con almenos un Procesador.
            \post Se han enviado entre 0 y n procesos con éxito en orden de prioridad y antigüedad a cluster. Quedan registradas la cantidad de éxitos y la de fracasos en la prioridad correspondiente del parámetro implícito. Los procesos colocados en cluster abandonan la prioridad en la que estaban, y los rechazados vuelven a ella como si fueran nuevos.
        */
        void enviar_procesos_cluster(int n, const Cluster& cluster);
        

        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime una determinada prioridad del parámetro implícito por el canal de salida estándar.
            \pre Existe una prioridad con identificador igual a id_prioridad en el parámetro implícito.
            \post Quedan escritos en el canal de salida estándar los procesos pendientes de la prioridad con identificador igual a id_prioridad del parámetro implícito en orden decreciente de antigüedad, y el número de procesos colocados y rechazados de dicha prioridad.
        */
        void imprimir_prioridad(const string& id_prioridad, int& error) const;

        /** @brief Imprime todas las prioridades del parámetro implícito por el canal de salida estándar.
            \pre Cierto.
            \post Quedan escritos en el canal de salida estándar los procesos pendientes de todas las prioridades del parámetro implícito en orden decreciente de antigüedad, y el número de procesos colocados y rechazados de cada una de ellas.
        */
        void imprimir_area_espera() const;
};