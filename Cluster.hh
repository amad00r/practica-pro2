#ifndef CLUSTER_HH
#define CLUSTER_HH

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
    @brief Representa un clúster de procesadores.

    Los procesadores se encuentran organizados en una jerarquía dónde cada uno
    puede tener dos procesadores auxiliares.
*/
class Cluster {

    private:
        /** @brief Mapa de identificador->Procesador que contiene los
                   procesadores del Cluster.
        */
        map<string, Procesador> mapa_procesadores;

        /** @brief Árbol binario que representa una jerarquía de procesadores.
        */
        BinTree<map<string, Procesador>::iterator> arbol_procesadores;

        // LECTURA/ESCRITURA ##################################################

        /** @brief Lee un árbol binario de procesadores del canal de entrada 
                   estándar.

            \pre El canal de entrada estándar contiene una secuencia de
                 identificadores no repetidos de procesadores.

            \post El parámetro arbol contiene los procesadores leídos del canal
                  de entrada estándar. El canal de entrada estándar no contiene
                  una secuencia de identificadores de procesadores.
        */
        void leer_procesadores(
            BinTree<map<string, Procesador>::iterator> &arbol
        );

        /** @brief Consume un árbol binario de procesadores del canal de
                   entrada estándar.
                
            \pre El canal de entrada estándar contiene una secuencia de
                 identificadores de procesadores.

            \post El canal de entrada estándar no contiene una secuencia de
                  identificadores de procesadores.
        */
        static void consumir_cluster_input();

        /** @brief Auxiliar recursiva para imprimir la estructura del clúster
         
            \pre Cierto.

            \post Se ha escrito en el canal de salida estándar la estructura
                  interna de los procesadores del parámetro implícito.
        */
        static void auxiliar_imprimir_estructura_cluster(
            const BinTree<map<string, Procesador>::iterator> &arbol
        );

        // MODIFICADORAS ######################################################

        /** @brief Sustituye un procesador por un nuevo clúster
        
            \pre El canal de entrada estándar contiene una secuencia de
                 identificadores no repetidos de procesadores.

            \post Si no existe un procesador en el parámetro implícito con
                  identificador igual a id_procesador, error vale
                  PROCESADOR_INEXISTENTE.
                  Si dicho procesador tiene algún proceso en ejecución, error
                  vale PROCESOS_EN_EJECUCION.
                  Si dicho procesador tiene algún procesador auxiliar, error
                  vale TIENE_PROCESADORES_AUXILIARES.
                  Si no se dan estos casos, el procesador del parámetro
                  implícito con identificador igual a id_procesador es
                  sustituido por el clúster leído del canal de entrada
                  estándar.
        */
        bool auxiliar_modificar_cluster(
            BinTree<map<string, Procesador>::iterator> &arbol,
            const string &id_procesador,
            int &error
        );

        // CONSULTORAS ########################################################

        /** @brief Determina si un procesador es más adecuado que otro para
                   almacenar un cierto proceso.

            \pre preferido apunta a mapa_procesadores.end() o a un procesador
                 inicializado.
                 it apunta a un procesador inicializado.
                 proceso está inicializado.

            \post El resultado es true si el procesador apuntado por preferido
                  que se encuentra a una profundidad igual a
                  profundidad_prferido es igual de preferido o más que el
                  procesador apuntado por el iterador it que se encuentra a una
                  profundidad igual a profundidad.
                  De otra manera, el resultado es false.
        */
        bool procesador_preferido(
            const map<string, Procesador>::iterator &preferido,
            int hueco_min_preferido,
            int profundidad_preferido,
            const map<string, Procesador>::iterator &it,
            int profundidad,
            const Proceso &proceso
        ) const;

        /** @brief Auxiliar recursiva para dar de alta un cierto proceso en el
                   procesador más adecuado del parámetro implícito

            \pre preferido apunta a mapa_procesadores.end() o a un procesador
                 inicializado.
                 profundidad_preferido, profundidad >= 0.
                 proceso está inicializado.

            \post Si no existe ningún procesador que pueda ejecutar proceso,
                  proceso = mapa_procesadores.end().
                  De otro modo, proceso apunta al procesador del parámetro
                  implícito más adecuado para ejecutar proceso.
                  profundidad_preferido representa la profundidad en el clúster
                  de dicho procesador.
        */
        void auxiliar_alta_proceso(
            map<string, Procesador>::iterator &preferido,
            int &hueco_min_preferido,
            int &profundidad_preferido,
            const BinTree<map<string, Procesador>::iterator> &arbol,
            int profundidad,
            const Proceso &proceso
        ) const;

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al
                   declarar un Cluster.

            \pre El canal de entrada estándar contiene una secuencia de
                 identificadores no repetidos de procesadores.

            \post El resultado es un clúster inizializado con un clúster leído
                  del canal de entrada estándar. El canal de entrada estándar
                  no contiene una secuencia de identificadores de procesadores.
        */  
        Cluster();


        // MODIFICADORAS ######################################################

        /** @brief Configura el parámetro implícito con nuevos procesadores
                   leídos del canal de entrada estándar.

            \pre El canal de entrada estándar contiene una secuencia de
                 identificadores no repetidos de procesadores.

            \post Los procesadores del parámetro implícito no se repiten y son
                  los que se han leído del canal de entrada estándar. Si el
                  parámetro implícito ya contenía procesadores, estos se ven
                  reemplazados por los nuevos.
                  El canal de entrada estándar no contiene una secuencia de
                  identificadores de procesadores.
        */
        void configurar_cluster();

        /** @brief Sustituye un procesador del parámetro implícito por un nuevo
                   clúster leído del canal de entrada estándar.

            \pre El canal de entrada estándar contiene una secuencia de
                 identificadores no repetidos de procesadores.

            \post Si no existe un procesador en el parámetro implícito con
                  identificador igual a id_procesador, error vale 
                  PROCESADOR_INEXISTENTE.
                  Si dicho procesador tiene algún proceso en ejecución, error
                  vale PROCESOS_EN_EJECUCION.
                  Si dicho procesador tiene algún procesador auxiliar, error
                  vale TIENE_PROCESADORES_AUXILIARES.
                  Si no se dan estos casos, el procesador del parámetro
                  implícito con identificador igual a id_procesador es el
                  clúster de procesadores leído del canal de entrada estándar.
                  El canal de entrada estándar no contiene una secuencia de
                  identificadores de procesadores.
        */
        void modificar_cluster(const string &id_procesador, int &error);
        
        /** @brief Da de alta un proceso en un cierto procesador del parámetro
                   implícito.

            \pre proceso está inicializado.

            \post Si no existe un procesador con identificador igual a
                  id_procesador en el parámetro implícito, error vale
                  PROCESADOR_INEXISTENTE.
                  Si existe algún proceso con mismo identificador que proceso
                  en dicho procesador, error vale
                  PROCESO_EXISTENTE_EN_PROCESADOR.
                  Si proceso no se puede colocar en dicho procesador, error
                  vale PROCESO_NO_COLOCABLE.
                  Si no se dan estos casos, proceso se ejecuta en el procesador
                  del parámetro implícito con identificador igual a
                  id_procesador.
                  proceso es colocado en la posición de memoria más pequeña de
                  dicho procesador que deje el hueco más ajustado posible.
        */
        void alta_proceso_procesador(
            const Proceso &proceso,
            const string &id_procesador,
            int &error
        );

        /** @brief Da de baja un proceso de un cierto procesador del parámetro
                   implícito.

            \pre Cierto.

            \post Si no existe un procesador con identificador igual a
                  id_procesador el parámetro implícito, error vale
                  PROCESADOR_INEXISTENTE.
                  Si no existe un proceso con identificador igual a id_proceso
                  en dicho procesador, error vale
                  PROCESO_INEXISTENTE_EN_PROCESADOR.
                  Si no se dan estos casos, ya no se ejecuta ningún proceso con
                  identificador igual a id_proceso en el procesador del
                  parámetro implícito con identificador igual a id_procesador.
                  Se ha liberado la memoria de dicho procesador que ocupaba
                  dicho proceso.
        */
        void baja_proceso_procesador(
            int id_proceso,
            const string &id_procesador,
            int &error
        );

        /** @brief Da de alta un proceso en un procesador del parámetro
                   implícito.

            \pre proceso está inicializado.

            \post Si proceso se ha colocado el resultado es true.
                  proceso se ejecuta en el procesador que disponga de un hueco
                  más ajustado para proceso, disponga de más memoria libre, se
                  encuentre más cerca de la raíz del clúster, o, en última
                  instancia, se encuentre más a la izquierda en el clúster.
                  Además, proceso se ha colocado en la posición de memoria más
                  pequeña de dicho procesador que deje el hueco más ajustado
                  posible.
                  Si proceso no se ha colocado, el resultado es false.
        */
        bool alta_proceso(const Proceso &proceso);

        /** @brief Avanza el tiempo que ha transcurrido en la ejecución de los
                   procesos de los procesadores del parámetro implícito.

            \pre t >= 0.

            \post El tiempo estimado de los procesos de todos los procesadores
                  del parámetro implícito se ha visto decrementado en t. Si un
                  proceso tenía un tiempo estimado menor que t se ha liberado
                  de la memoria de su correspondiente procesador.
        */
        void avanzar_tiempo(int t);

        /** @brief Compacta los procesos en memoria de un cierto procesador
                   del parámetro implícito.

            \pre Cierto.

            \post Si no existe un procesador con identificador igual a
                  id_procesador en el parámetro implícito, error vale
                  PROCESADOR_INEXISTENTE.
                  Si existe dicho procesador, sus procesos en memoria quedan
                  compactados hacia el comienzo de la memoria sin dejar huecos,
                  sin solaparse, y respetando el orden inicial.
        */
        void compactar_memoria_procesador(const string &id_procesador, int &error);

        /** @brief Compacta los procesos en memoria de todos los procesadores
                   del parámetro implícito.

            \pre Cierto.

            \post Los proceso en memoria de todos los procesadores del
                  parámetro implícito quedan compactados hacia el comienzo de
                  la memoria sin dejar huecos, sin solaparse, y respetando el
                  orden inicial.
        */
        void compactar_memoria_cluster();


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime un determinado procesador del parámetro implícito
                   por el canal de salida estándar.

            \pre Cierto.

            \post Si no existe un procesador con identificador igual a
                  id_procesador en el parámetro implícito, error vale
                  PROCESADOR_INEXISTENTE.
                  Si existe dicho procesador, quedan escritos en el canal de
                  salida estándar sus procesos de en orden creciente de primera
                  posición de memoria, incluyendo dicha posición.
        */
        void imprimir_procesador(
            const string &id_procesador,
            int& error
        ) const;

        /** @brief Imprime todo procesador del parámetro implícito por el canal
                   de salida estándar.
            
            \pre Cierto.
            
            \post Quedan escritos en el canal de salida estándar los procesos
                  (en orden creciente de primera posición de memoria,
                  incluyendo dicha posición) de todo procesador (en orden
                  creciente de identificador) del parámetro implícito.
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

#endif