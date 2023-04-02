/** @file Cluster.hh
    @brief Especificación de la clase Cluster.
*/

#include "Procesador.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <string>
#include "BinTree.hh"
#endif

using namespace std;

/** @class Cluster
    @brief Representa un clúster de Procesador.
*/
class Cluster {
    private:
        BinTree<Procesador> procesadores;


        // LECTURA/ESCRITURA ##################################################

        /** @brief Lee un árbol binario de Procesador del canal de entrada estándar.
            \pre El canal de entrada estándar contiene una secuencia de identificadores no repetidos de Procesador.
            \post El parámetro tree contiene los Procesador leídos del canal de entrada estándar.
        */
        void leer_procesadores(BinTree<Procesador>& tree);

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al declarar un Cluster.
            \pre Cierto.
            \post El resultado es un Cluster no inicializado.
        */  
        Cluster();


        // MODIFICADORAS ######################################################

        /** @brief Configura el parámetro implícito con nuevos Procesador leídos del canal de entrada estándar.
            \pre El canal de entrada estándar contiene una secuencia de identificadores no repetidos de Procesador.
            \post Los Procesador del parámetro implícito no se repiten y son los que se han leído del canal de entrada estándar. Si el parámetro implícito ya contenía procesadores, estos se ven reemplazados por los nuevos.
        */
        void configurar_cluster();

        /** @brief Sustituye un Procesador del parámetro implícito por un nuevo clúster de Procesador leído del canal de entrada estándar.
            \pre El canal de entrada estándar contiene una secuencia de identificadores no repetidos de Procesador. Existe un Procesador en el parámetro implícito con identificador igual a id_procesador. Dicho Procesador no tiene ningún Proceso en ejecución ni ningún Procesador auxiliar.
            \post El Procesador del parámetro implícito con identificador igual a id_procesador es el clúster de Procesador leído del canal de entrada estándar. El resultado indica si se ha encontrado el Procesador del parámetro implícito con identificador igual a id_procesador en el parámetro implícito.
        */
        bool modificar_cluster(const string& id_procesador, int& error);
        
        /** @brief Da de alta un Proceso en un Procesador del parámetro implícito.
            \pre Existe un Procesador con identificador igual a id_procesador en el parámetro implícito. No existe ningún Proceso idéntico a proceso en dicho Procesador. proceso se puede colocar en dicho Procesador.
            \post proceso se ejecuta en el Procesador del parámetro implícito con identificador igual a id_procesador. proceso se coloca en la posición de memoria más pequeña de dicho Procesador que deje el hueco más ajustado. El resultado indica si se ha encontrado el Procesador con identificador igual a id_procesador en el parámetro implícito.
        */
        bool alta_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error);

        /** @brief Da de baja un Proceso de un Procesador del parámetro implícito.
            \pre Existe un Procesador con identificador igual a id_procesador el parámetro implícito. Existe un Proceso idéntico a proceso en dicho Procesador.
            \post proceso ya no se ejecuta en el Procesador del parámetro implícito con identificador igual a id_procesador. Se ha liberado la memoria de dicho Procesador que ocupaba proceso. El resultado indica si se ha encontrado el Procesador con identificador igual a id_procesador en el parámetro implícito.
        */
        bool baja_proceso_procesador(const Proceso& proceso, const string& id_procesador, int& error);

        /** @brief Da de alta un Proceso en un Procesador del parámetro implícito.
            \pre Cierto.
            \post Si proceso se ha colocado, colocado vale true y proceso se ejecuta en el Procesador que disponga de un hueco más ajustado respecto a proceso, disponga de más memoria libre, se encuentre más cerca de la raíz del árbol de procesadores, o, en última instancia, se encuentre más a la izquierda. Si, por otro lado, proceso no se ha colocado, colocado vale false. El resultado indica si se ha encontrado el Procesador con identificador igual a id_procesador en el parámetro implícito.
        */
        bool alta_proceso(const Proceso& proceso, int& error);

        /** @brief Avanza el tiempo que ha transcurrido en la ejecución de los Proceso de los Procesador del parámetro implícito.
            \pre t >= 0.
            \post El tiempo estimado de los Proceso de todos los Procesador del parámetro implícito se ha visto decrementado en t. Si un Proceso tenía un tiempo estimado menor que t se ha liberado de la memoria de su correspondiente Procesador.
        */
        void avanzar_tiempo(int t);

        /** @brief Compacta los Proceso en memoria de un determinado Procesador del parámetro implícito.
            \pre Existe un Procesador con identificador igual a id_procesador en el parámetro implícito.
            \post Los Proceso en memoria del Procesador con identificador igual a id_procesador del parámetro implícito quedan compactados hacia el comienzo de la memoria sin dejar huecos, sin solaparse, y respetando el orden inicial. El resultado indica si se ha encontrado el Procesador con identificador igual a id_procesador en el parámetro implícito.
        */
        bool compactar_memoria_procesador(const string& id_procesador, int& error);

        /** @brief Compacta los Proceso en memoria de todos los Procesador del parámetro implícito.
            \pre Cierto.
            \post Los Proceso en memoria de todos los Procesador del parámetro implícito quedan compactados hacia el comienzo de la memoria sin dejar huecos, sin solaparse, y respetando el orden inicial.
        */
        void compactar_memoria_cluster();


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime un determinado Procesador del parámetro implícito por el canal de salida estándar.
            \pre Existe un Procesador con identificador igual a id_procesador en el parámetro implícito.
            \post Quedan escritos en el canal de salida estándar los Proceso de dicho Procesador en orden creciente de primera posición de memoria, incluyendo dicha posición. El resultado indica si se ha encontrado el Procesador con identificador igual a id_procesador en el parámetro implícito.
        */
        bool imprimir_procesador(const string& id_procesador, int& error) const;

        /** @brief Imprime todo Procesador del parámetro implícito por el canal de salida estándar.
            \pre Cierto.
            \post Quedan escritos en el canal de salida estándar los Proceso (en orden creciente de primera posición de memoria, incluyendo dicha posición) de todo Procesador (en orden creciente de identificador) del parámetro implícito.
        */
        void imprimir_procesadores_cluster() const;

        /** @brief Imprime la estructura interna del parámetro implícito por el canal de salida estándar.
            \pre Cierto.
            \post Queda escrito en el canal de salida estándar la estructura interna del parámetro implícito.
        */
        void imprimir_estructura_cluster() const;
};