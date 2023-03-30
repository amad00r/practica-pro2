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
            unsigned int procesos_colocados = 0;
            unsigned int procesos_rechazados = 0;
        };
        map<string, Prioridad> mapa_prioridades;

        // CONSULTORAS ########################################################

        /** @brief Consulta si existe una cierta prioridad en el parámetro implícito.
            \pre Cierto.
            \post El resultado indica si existe una Prioridad con llave igual a id_prioridad en mapa_prioridades del parámetro implícito.
        */
        bool existe_prioridad(const string& id_prioridad) const;

        /** @brief Consulta si existe un cierto proceso en una cierta prioridad del parámetro implícito
            \pre Existe una llave en mapa_prioridades igual a id_prioridad.
            \post El resultado indica si existe el proceso con id = id_proceso en la Prioridad con llave igual a id_prioridad en el mapa_prioridades del parámetro implícito.
        */
        bool existe_proceso_en_prioridad(unsigned int id_proceso, const string& id_prioridad) const;

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al declarar un ProcesosPendientes.
            \pre cierto.
            \post El resultado es un ProcesosPendientes con mapa_prioridades vacío.
        */
        ProcesosPendientes();


        // MODIFICADORAS ######################################################

        /** @brief Da de alta una nueva prioridad en el parámetro implícito.
            \pre No existe una llave en mapa_prioridades igual a id_prioridad.
            \post Existe una llave en mapa_prioridades igual a id_prioridad con valor sin inicializar.
        */
        void alta_prioridad(const string& id_prioridad);

        /** @brief Da de baja una prioridad del parámetro implícito.
            \pre Existe una llave en mapa_prioridades igual a id_prioridad, y dicha llave corresponde a una Prioridad sin procesos.
            \post No existe una llave en mapa_prioridades igual a id_prioridad.
        */
        void baja_prioridad(const string& id_prioridad);

        /** @brief Da de alta un proceso en una prioridad del parámetro implícito.
            \pre Existe una llave en mapa_prioridades igual a id_prioridad, y dicha llave corresponde a una Prioridad sin que no contiene procesos iguales a proceso.
            \post proceso está en la cola de la Prioridad con llave igual a id_prioridad de mapa_prioridades del parámetro implícito.
        */
        void alta_proceso_espera(const Proceso& proceso, const string& id_prioridad);

        /** @brief Envía n procesos en espera para que se ejecuten en un clúster.
            \pre cierto.
            \post Se han enviado entre 0 y n procesos con éxito al procesador en orden de prioridad y antigüedad. Quedan registradas la cantidad de éxitos y la de fracasos en procesos_colocados y procesos_rechazados de la Prioridad con llave igual a id_prioridad. Los procesos colocados abandonan la Prioridad en la que estaban, y los rechazados vuelven a ella como si fueran nuevos.
        */
        void enviar_procesos_cluster(unsigned int n, Cluster& cluster);
        

        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime una cierta Prioridad por el canal de salida estándar.
            \pre Existe una llave en mapa_prioridades igual a id_prioridad.
            \post Quedan escritos los procesos pendientes de la Prioridad con llave igual a id_prioridad por orden decreciente de antigüedad, y el número de procesos colocados y rechazados por un clúster de dicha Prioridad.
        */
        void imprimir_prioridad(const string& id_prioridad) const;

        /** @brief Imprime todas las prioridades por el canal de salida estándar.
            \pre cierto.
            \post Quedan escritos los procesos pendientes de la todas las prioridades por orden decreciente de antigüedad, y el número de procesos colocados y rechazados por un clúster de cada una.
        */
        void imprimir_area_espera() const;
};