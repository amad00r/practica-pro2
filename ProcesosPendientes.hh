/** @file ProcesosPendientes.hh
    @brief Especificación de la clase ProcesosPendientes.
*/

#ifndef PROCESOSPENDIENTES_HH
#define PROCESOSPENDIENTES_HH

#include "Proceso.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <list>
#include <map>
#endif

using namespace std;

/** @class ProcesosPendientes
    @brief Representa una sala de espera de procesos pendientes a ejecutarse.

    En cada momento puede contener un número variable de Proceso pendientes
    con diferentes prioridades.
*/
class ProcesosPendientes {
    private:
    
        struct Prioridad {
            list<Proceso> lista_procesos;
            set<int>      conjunto_procesos;
            int           procesos_colocados;
            int           procesos_rechazados;
        };

        map<string, Prioridad> mapa_prioridades;


        // CONSULTORAS ########################################################

        /** @brief Consulta si existe una determinada prioridad en el parámetro
                   implícito.

            \pre id_prioridad contiene únicamente letras y números.

            \post El resultado indica si existe una prioridad con identificador
                  igual a id_prioridad en el parámetro implícito.
        */
        bool existe_prioridad(const string &id_prioridad) const;
        void auxiliar_imprimir_prioridad(const map<string, Prioridad>::const_iterator &it_prioridad) const;


    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al
                   declarar un ProcesosPendientes.

            \pre Cierto.

            \post El resultado es un ProcesosPendientes sin prioridades ni
                  procesos pendientes.
        */
        ProcesosPendientes();


        // MODIFICADORAS ######################################################

        /** @brief Da de alta una prioridad en el parámetro implícito.

            \pre id_prioridad contiene únicamente letras y números.

            \post Si existe una prioridad con identificador igual a
                  id_prioridad en el parámetro implícito, error vale
                  PRIORIDAD_EXISTENTE.
                  Si no existe, se crea en el parámetro implícito dicha
                  prioridad sin procesos pendientes.
        */
        void alta_prioridad(const string& id_prioridad, int& error);

        /** @brief Da de baja una prioridad del parámetro implícito.

            \pre Cierto.

            \post Si no existe una prioridad con identificador igual a
                  id_prioridad en el parámetro implícito, error vale
                  PRIORIDAD_INEXISTENTE.
                  Si dicha prioridad tiene algún Proceso pendiente, error vale
                  PROCESO_EXISTENTE_EN_PRIORIDAD.
                  Si no se dan estos casos, ya no existe una prioridad con
                  identificador igual a id_prioridad en el parámetro implícito.
        */
        void baja_prioridad(const string& id_prioridad, int& error);

        /** @brief Da de alta un proceso en una prioridad del parámetro
                   implícito.

            \pre Cierto.
                 
            \post Si no existe una prioridad con identificador igual a
                  id_prioridad en el parámetro implícito, error vale
                  PRIORIDAD_INEXISTENTE.
                  Si dicha prioridad tiene asignada algún Proceso igual a
                  proceso, error vale PROCESO_EXISTENTE_EN_PRIORIDAD.
                  Si no se dan estos casos, la prioridad con identificador
                  igual a id_prioridad del parámetro implícito pasa a tener
                  asignada un Proceso igual a proceso.
        */
        void alta_proceso_espera(const Proceso& proceso, const string& id_prioridad, int& error);

        /** @brief Envía n procesos pendientes a un determinado Cluster para
                   que sean ejecutados.

            \pre n >= 0. cluster está inicializado con almenos un Procesador.

            \post Se han enviado entre 0 y n procesos con éxito en orden de
                  prioridad y antigüedad a cluster. Quedan registradas la
                  cantidad de éxitos y la de fracasos en la prioridad
                  correspondiente del parámetro implícito. Los procesos
                  colocados en cluster abandonan la prioridad en la que
                  estaban, y los rechazados vuelven a ella como si fueran
                  nuevos.
        */
        void enviar_procesos_cluster(int n, Cluster& cluster);
        

        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime una determinada prioridad del parámetro implícito
                   por el canal de salida estándar.

            \pre Existe una prioridad con identificador igual a id_prioridad en
                 el parámetro implícito.

            \post Si no existe una prioridad con identificador igual a
                  id_prioridad en el parámetro implícito, error vale
                  PRIORIDAD_INEXISTENTE.
                  Si existe, quedan escritos en el canal de salida estándar los
                  procesos pendientes de dicha prioridad en orden decreciente
                  de antigüedad, y su número de procesos colocados y
                  rechazados.
        */
        void imprimir_prioridad(const string& id_prioridad, int& error) const;

        /** @brief Imprime todas las prioridades del parámetro implícito por el
                   canal de salida estándar.

            \pre Cierto.

            \post Quedan escritos en el canal de salida estándar los procesos
                  pendientes de todas las prioridades del parámetro implícito
                  en orden decreciente de antigüedad, y el número de procesos
                  colocados y rechazados de cada una de ellas.
        */
        void imprimir_area_espera() const;
};

#endif