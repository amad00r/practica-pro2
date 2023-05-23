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
#include <iostream>
#endif

using namespace std;

/** @class ProcesosPendientes
    @brief Representa una sala de espera de procesos pendientes a ejecutarse.

    En cada momento puede contener un número variable de procesos pendientes
    con diferentes prioridades.
*/
class ProcesosPendientes {
    private:

        /** @brief Estructura de datos que representa una prioridad del área de
                   espera.
        */
        struct Prioridad {

            /** @brief Representa una cola de procesos con una cierta prioridad
            */
            list<Proceso> lista_procesos;

            /** @brief Conjunto de identificadores de los procesos que se
                       encuentran en una misma prioridad.
            */
            set<int> conjunto_procesos;

            /** @brief Contador de todos los procesos con una misma prioridad
                       que han sido enviados a un clúster.
            */
            int procesos_colocados;
            
            /** @brief Contador de todos los procesos con una misma prioridad
                       que han sido rechazados por un clúster.
            */
            int procesos_rechazados;
        };

        /** @brief Prioridades del área de espera. */
        map<string, Prioridad> mapa_prioridades;

        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime una cierta prioridad por el canal de salida estándar
        */
        static void auxiliar_imprimir_prioridad(
            const map<string, Prioridad>::const_iterator &it_prioridad
        );

    public:

        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al
                   declarar un ProcesosPendientes.

            \pre En el canal de entrada estándar hay un entero n y, a
                 continuación, n prioridades.

            \post El resultado es un ProcesosPendientes inicializado con las
                  prioridades del canal de entrada estándar.
        */
        ProcesosPendientes();

        // MODIFICADORAS ######################################################

        /** @brief Da de alta una prioridad.

            \pre id_prioridad contiene únicamente letras y números.

            \post Si existe una prioridad con identificador igual a
                  id_prioridad en el parámetro implícito, error vale
                  PRIORIDAD_EXISTENTE.
                  Si no existe, se crea en el parámetro implícito dicha
                  prioridad sin procesos pendientes.
        */
        void alta_prioridad(const string &id_prioridad, int &error);

        /** @brief Da de baja una prioridad.

            \pre Cierto.

            \post Si no existe una prioridad con identificador igual a
                  id_prioridad en el parámetro implícito, error vale
                  PRIORIDAD_INEXISTENTE.
                  Si dicha prioridad tiene algún proceso pendiente, error vale
                  PROCESO_EXISTENTE_EN_PRIORIDAD.
                  Si no se dan estos casos, ya no existe una prioridad con
                  identificador igual a id_prioridad en el parámetro implícito.
        */
        void baja_prioridad(const string &id_prioridad, int &error);

        /** @brief Da de alta un proceso en una cierta prioridad.

            \pre proceso está inicializado.
                 
            \post Si no existe una prioridad con identificador igual a
                  id_prioridad en el parámetro implícito, error vale
                  PRIORIDAD_INEXISTENTE.
                  Si dicha prioridad tiene asignada algún proceso igual a
                  proceso, error vale PROCESO_EXISTENTE_EN_PRIORIDAD.
                  Si no se dan estos casos, proceso se coloca el último en la
                  prioridad con identificador igual a id_prioridad del
                  parámetro implícito.
        */
        void alta_proceso_espera(
            const Proceso &proceso,
            const string &id_prioridad,
            int &error
        );

        /** @brief Envía n procesos pendientes a un cierto cluster para
                   que sean ejecutados.

            \pre n >= 0.

            \post Se han enviado entre 0 y n procesos con éxito en orden de
                  prioridad y antigüedad a cluster. Quedan registradas la
                  cantidad de éxitos y la de fracasos en la prioridad
                  correspondiente. Los procesos colocados en cluster abandonan
                  la prioridad en la que estaban, y los rechazados se vuelven a
                  colocar al final de la prioridad.
        */
        void enviar_procesos_cluster(int n, Cluster &cluster);
        

        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime una cierta prioridad por el canal de salida
                   estándar.

            \pre Cierto.

            \post Si no existe una prioridad con identificador igual a
                  id_prioridad en el parámetro implícito, error vale
                  PRIORIDAD_INEXISTENTE.
                  De otra manera, quedan escritos en el canal de salida 
                  estándar los procesos pendientes de dicha prioridad en orden
                  decreciente de antigüedad, y su número de procesos colocados
                  y rechazados.
        */
        void imprimir_prioridad(const string &id_prioridad, int &error) const;

        /** @brief Imprime todas las prioridades por el canal de salida
                   estándar.

            \pre Cierto.

            \post Quedan escritos en el canal de salida estándar los procesos
                  pendientes de todas las prioridades del parámetro implícito
                  en orden decreciente de antigüedad, y el número de procesos
                  colocados y rechazados de cada una de ellas.
        */
        void imprimir_area_espera() const;
};

#endif