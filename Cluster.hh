#pragma once

/** @file Cluster.hh
    @brief Especificación de la clase Cluster.
*/

#include "Procesador.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <map>
#include "BinTree.hh"
#endif

using namespace std;

/** @class Cluster
    @brief Representa un clúster de Procesador.
*/
class Cluster {
    private:
        map<string, Procesador> mapa_procesadores;
        BinTree<map<string, Procesador>::iterator> arbol_procesadores;

        // LECTURA/ESCRITURA ##################################################

        /** @brief Lee un árbol binario de Procesador del canal de entrada 
                   estándar.

            \pre El canal de entrada estándar contiene una secuencia de
                 identificadores no repetidos de Procesador.

            \post El parámetro arbol contiene los Procesador leídos del canal de
                  entrada estándar.
        */
        void leer_procesadores(BinTree<map<string, Procesador>::iterator> &arbol);
        void consumir_cluster_input() const;
        bool auxiliar_modificar_cluster(
            BinTree<map<string, Procesador>::iterator> &arbol,
            const string &id_procesador,
            int &error
        );
        void auxiliar_imprimir_estructura_cluster(const BinTree<map<string, Procesador>::iterator> &arbol) const;
        bool procesador_preferido(
            const map<string, Procesador>::iterator &preferido,
            int profundidad_preferido,
            const map<string, Procesador>::iterator &it,
            int profundidad,
            const Proceso &proceso
        ) const;
        void auxiliar_alta_proceso(
            map<string, Procesador>::iterator &preferido,
            int &profundidad_preferido,
            const BinTree<map<string, Procesador>::iterator> &arbol,
            int profundidad,
            const Proceso &proceso
        ) const;

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al
                   declarar un Cluster.

            \pre Cierto.

            \post El resultado es un Cluster no inicializado.
        */  
        Cluster();


        // MODIFICADORAS ######################################################

        /** @brief Configura el parámetro implícito con nuevos Procesador
                   leídos del canal de entrada estándar.

            \pre El canal de entrada estándar contiene una secuencia de
                 identificadores no repetidos de Procesador.

            \post Los Procesador del parámetro implícito no se repiten y son
                  los que se han leído del canal de entrada estándar. Si el
                  parámetro implícito ya contenía procesadores, estos se ven
                  reemplazados por los nuevos.
        */
        void configurar_cluster();

        /** @brief Sustituye un Procesador del parámetro implícito por un nuevo
                   clúster de Procesador leído del canal de entrada estándar.

            \pre El canal de entrada estándar contiene una secuencia de
                 identificadores no repetidos de Procesador.

            \post Si no existe un Procesador en el parámetro implícito con
                  identificador igual a id_procesador, error vale 
                  PROCESADOR_INEXISTENTE.
                  Si dicho Procesador tiene algún Proceso en ejecución, error
                  vale PROCESOS_EN_EJECUCION.
                  Si dicho Procesador tiene algún Procesador auxiliar, error
                  vale TIENE_PROCESADORES_AUXILIARES.
                  Si no se dan estos casos, el Procesador del parámetro
                  implícito con identificador igual a id_procesador es el
                  clúster de Procesador leído del canal de entrada estándar.
        */
        void modificar_cluster(const string& id_procesador, int& error);
        
        /** @brief Da de alta un Proceso en un Procesador del parámetro
                   implícito.

            \pre Cierto.

            \post Si no existe un Procesador con identificador igual a
                  id_procesador en el parámetro implícito, error vale
                  PROCESADOR_INEXISTENTE.
                  Si existe algún Proceso idéntico a proceso en dicho
                  Procesador, error vale PROCESO_EXISTENTE_EN_PROCESADOR.
                  Si proceso no se puede colocar en dicho Procesador, error
                  vale PROCESO_NO_COLOCABLE.
                  Si no se dan estos casos, proceso se ejecuta en el Procesador
                  del parámetro implícito con identificador igual a
                  id_procesador. proceso es colocado en la posición de memoria
                  más pequeña de dicho Procesador que deje el hueco más
                  ajustado posible.
        */
        void alta_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error);

        /** @brief Da de baja un Proceso de un Procesador del parámetro
                   implícito.

            \pre Cierto.

            \post Si no existe un Procesador con identificador igual a
                  id_procesador el parámetro implícito, error vale
                  PROCESADOR_INEXISTENTE.
                  Si no existe un Proceso con identificador igual a id_proceso
                  en dicho Procesador, error vale
                  PROCESO_INEXISTENTE_EN_PROCESADOR.
                  Si no se dan estos casos, ya no se ejecuta ningún Proceso con
                  identificador igual a id_proceso en el Procesador del
                  parámetro implícito con identificador igual a id_procesador.
                  Se ha liberado la memoria de dicho Procesador que ocupaba
                  dicho Proceso.
        */
        void baja_proceso_procesador(int id_proceso, const string& id_procesador, int& error);

        /** @brief Da de alta un Proceso en un Procesador del parámetro
                   implícito.

            \pre Cierto.

            \post Si proceso se ha colocado, proceso se ejecuta en el
                  Procesador que disponga de un hueco más ajustado respecto a
                  proceso, disponga de más memoria libre, se encuentre más
                  cerca de la raíz del árbol de procesadores, o, en última
                  instancia, se encuentre más a la izquierda.
                  Si proceso no se ha colocado, error vale PROCESO_NO_COLOCABLE.
        */
        bool alta_proceso(const Proceso& proceso);

        /** @brief Avanza el tiempo que ha transcurrido en la ejecución de los
                   Proceso de los Procesador del parámetro implícito.

            \pre t >= 0.

            \post El tiempo estimado de los Proceso de todos los Procesador del
                  parámetro implícito se ha visto decrementado en t. Si un
                  Proceso tenía un tiempo estimado menor que t se ha liberado
                  de la memoria de su correspondiente Procesador.
        */
        void avanzar_tiempo(int t);

        /** @brief Compacta los Proceso en memoria de un determinado Procesador
                   del parámetro implícito.

            \pre Cierto.

            \post Si no existe un Procesador con identificador igual a
                  id_procesador en el parámetro implícito, error vale
                  PROCESADOR_INEXISTENTE.
                  Si existe dicho Procesador, sus Proceso en memoria quedan
                  compactados hacia el comienzo de la memoria sin dejar huecos,
                  sin solaparse, y respetando el orden inicial.
        */
        void compactar_memoria_procesador(const string& id_procesador, int& error);

        /** @brief Compacta los Proceso en memoria de todos los Procesador del
                   parámetro implícito.

            \pre Cierto.

            \post Los Proceso en memoria de todos los Procesador del parámetro
                  implícito quedan compactados hacia el comienzo de la memoria
                  sin dejar huecos, sin solaparse, y respetando el orden inicial.
        */
        void compactar_memoria_cluster();


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime un determinado Procesador del parámetro implícito
                   por el canal de salida estándar.

            \pre Cierto.

            \post Si no existe un Procesador con identificador igual a
                  id_procesador en el parámetro implícito, error vale
                  PROCESADOR_INEXISTENTE.
                  Si existe dicho Procesador, quedan escritos en el canal de
                  salida estándar sus Proceso de en orden creciente de primera
                  posición de memoria, incluyendo dicha posición.
        */
        void imprimir_procesador(const string& id_procesador, int& error) const;

        /** @brief Imprime todo Procesador del parámetro implícito por el canal
                   de salida estándar.
            
            \pre Cierto.
            
            \post Quedan escritos en el canal de salida estándar los Proceso (en
                  orden creciente de primera posición de memoria, incluyendo
                  dicha posición) de todo Procesador (en orden creciente de
                  identificador) del parámetro implícito.
        */
        void imprimir_procesadores_cluster() const;

        /** @brief Imprime la estructura interna del parámetro implícito por el
                   canal de salida estándar.

            \pre Cierto.

            \post Queda escrito en el canal de salida estándar la estructura
                  interna del parámetro implícito.
        */
        void imprimir_estructura_cluster() const;
};
