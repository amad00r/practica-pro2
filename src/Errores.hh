/** @file Errores.hh
    @brief Definición de constantes.

    Se definen los errores que se pueden producir en los métodos de los
    módulos: ProcesosPendientes.hh, Cluster.hh.
*/

const int NO_HAY_ERROR = -1;

// ProcesosPendientes.hh ######################################################

const int PRIORIDAD_EXISTENTE                = 0;
const int PRIORIDAD_INEXISTENTE              = 1;
const int PRIORIDAD_CON_PROCESOS_PENDIENTES  = 2;
const int PROCESO_EXISTENTE_EN_PRIORIDAD     = 3;

// Cluster.hh #################################################################

const int PROCESADOR_INEXISTENTE             = 4;
const int TIENE_PROCESADORES_AUXILIARES      = 5;
const int PROCESOS_EN_EJECUCION              = 6;
const int PROCESO_NO_COLOCABLE               = 7;
const int PROCESO_EXISTENTE_EN_PROCESADOR    = 8;
const int PROCESO_INEXISTENTE_EN_PROCESADOR  = 9;