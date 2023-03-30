/** @file Cluster.hh
    @brief Especificación de la clase Cluster.
*/

#include "Procesador.hh"
#include "Proceso.hh"
#include "BinTree.hh"

#ifndef NO_DIAGRAM
#include <string>
#endif

using namespace std;

/** @class Cluster
    @brief Representa un clúster de procesadores

    Tenemos un clúster con un número de procesadores variable, distribuidos en forma de árbol binario, con identificadores únicos. El primer procesador puede ser cualquiera de ellos. Cada procesador puede tener dos, uno o cero procesadores sucesores, también llamados auxiliares. Todo clúster ha de tener como mínimo un procesador.
*/
class Cluster {
    private:
        BinTree<Procesador> procesadores;

        // LECTURA/ESCRITURA ##################################################

        /** @brief Lee un árbol binario de procesadores del canal de entrada estándar.
            \pre El canal de entrada estándar contiene una secuencia de identificadores no repetidos de procesadores.
            \post El parámetro tree contiene los procesadores leídos del canal de entrada estándar.
        */
        void leer_procesadores(BinTree<Procesador>& tree);

    public:
        // CONSTRUCTORAS ######################################################

        /** @brief Constructora por defecto. Se ejecuta automáticamente al declarar un Cluster.
            \pre cierto.
            \post El resultado es un Cluster no inicializado.
        */  
        Cluster();


        // MODIFICADORAS ######################################################

        /** @brief Configura el parámetro implícito con nuevos procesadores leídos del canal de entrada estándar.
            \pre El canal de entrada estándar contiene una secuencia de identificadores no repetidos de procesadores.
            \post Los procesadores del parámetro implícito no se repiten y son los que se han leído del canal de entrada estándar. Si ya contenía procesadores, estos se ven reemplazados.
        */
        void configurar_cluster();

        /** @brief Sustituye un procesador del parámetro implícito por un nuevo clúster de procesadores leído del canal de entrada estándar.
            \pre El canal de entrada estándar contiene una secuencia de identificadores no repetidos de procesadores. Existe un procesador en los procesadores del parámetro implícito con id = id_procesador. Dicho procesador no tiene procesos en ejecución ni procesadores auxiliares.
            \post El procesador del parámetro implícito con id = id_procesador es el clúster leído del canal de entrada estándar. El resultado indica si se ha encontrado el procesador con id = id_procesador.
        */
        bool modificar_cluster(const string& id_procesador);
        
        /** @brief Da de alta un Proceso en un Procesador del parámetro implícito.
            \pre Existe un procesador con id = id_procesador en procesadores del parámetro implícito. No existe ningún proceso idéntico a proceso en dicho procesador. proceso se puede colocar en dicho procesador.
            \post proceso se ejecuta en el procesador del parámetro implícito con id = id_procesador. Se coloca en la posición de memoria más pequeña de dicho procesador que deje el hueco más ajustado. El resultado indica si se ha encontrado el procesador con id = id_procesador.
        */
        bool alta_proceso_procesador(const Proceso& proceso, const string& id_procesador);

        /** @brief Da de baja un Proceso de un Procesador del parámetro implícito.
            \pre Existe un procesador con id = id_procesador en procesadores del parámetro implícito. Existe un proceso idéntico a proceso en dicho procesador.
            \post proceso ya no se ejecuta en el procesador del parámetro implícito con id = id_procesador. Se ha liberado la memoria de dicho procesador que ocupaba proceso. El resultado indica si se ha encontrado el procesador con id = id_procesador.
        */
        bool baja_proceso_procesador(const Proceso& proceso, const string& id_procesador);

        /** @brief Da de alta un Proceso en un Procesador del parámetro implícito.
            \pre cierto.
            \post Si el proceso se ha colocado, colocado vale true y proceso se ejecuta en el procesador que disponga de un hueco más ajustado respecto a proceso, disponga de más memoria libre, se encuentre más cerca de la raíz del árbol de procesadores, o, en última instancia, se encuentre más a la izquierda. Si, por otro lado, proceso no se ha colocado, colocado vale false. El resultado indica si se ha encontrado el procesador con id = id_procesador.
        */
        bool alta_proceso(const Proceso& proceso, bool& colocado);

        /** @brief Avanza el tiempo que ha transcurrido en la simulación de los procesadores.
            \pre cierto.
            \post Todos los procesadores del clúster han avanzado en t el tiempo de simulación de sus procesos.
        */
        void avanzar_tiempo(unsigned int t);

        /** @brief Compacta los procesos en memoria de un cierto Procesador del parámetro implícito.
            \pre Existe un procesador con id = id_procesador en procesadores del parámetro implícito.
            \post Los procesos en memoria del Procesador con id = id_procesador del parámetro implícito quedan compactados hacia el comienzo de la memoria sin dejar huecos, sin solaparse, y respetando el orden inicial. El resultado indica si se ha encontrado el procesador con id = id_procesador.
        */
        bool compactar_memoria_procesador(const string& id_procesador);

        /** @brief Compacta los procesos en memoria de todos los procesadores del parámetro implícito.
            \pre cierto.
            \post Los procesos en memoria de todos los procesadores del parámetro implícito quedan compactados hacia el comienzo de la memoria sin dejar huecos, sin solaparse, y respetando el orden inicial.
        */
        void compactar_memoria_cluster();


        // LECTURA/ESCRITURA ##################################################

        /** @brief Imprime un cierto Procesador del parámetro implícito por el canal de salida estándar.
            \pre Existe un procesador con id = id_procesador en procesadores del parámetro implícito.
            \post Quedan escritos en el canal de salida estándar los procesos de dicho Procesador en orden creciente de primera posición de memoria, incluyendo dicha posición. El resultado indica si se ha encontrado el procesador con id = id_procesador.
        */
        bool imprimir_procesador(const string& id_procesador) const;

        /** @brief Imprime un todos los procesadores del parámetro implícito por el canal de salida estándar.
            \pre cierto.
            \post Quedan escritos en el canal de salida estándar los procesos (en orden creciente de primera posición de memoria, incluyendo dicha posición) de todos los procesadores (en orden creciente de identificador) del parámetro implícito.
        */
        void imprimir_procesadores_cluster() const;

        /** @brief Imprime la estructura del clúster del parámetro implícito por el canal de salida estándar.
            \pre cierto.
            \post Queda escrito en el canal de salida estándar la estructura del clúster de procesadores del parámetro implícito.
        */
        void imprimir_estructura_cluster() const;
};