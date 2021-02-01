/*Declaracion de datos a transferir entre el servidorAlertas y el servidorNotificaciones*/
/*Declaracion de constantes*/
const MAXCADENA = 30;
const MEDCADENA = 15;
const MINCADENA = 5;


struct nodo_Alertas2{
    char fecha[MEDCADENA];
    char hora[MEDCADENA];
    float puntuacion;    
};

struct nodo_Indicadores2{
    float frecuenciaCardiaca;
    float frecuenciaRespiratoria;
    float temperatura;
};

/*Declaracion de la estructura que permite almacenar los datos de un anteproyecto*/

struct nodo_Asintomatico2{
    char nombre[MAXCADENA];
    char apellido[MAXCADENA];
    char tipo_id[MINCADENA];
    int id;
    char direccion[MAXCADENA];
    int ultimoIndicador;
    nodo_Indicadores2 ultimoIndicador2;
    nodo_Alertas2 alertas[5];
};

program gestion_notificaciones{
version gestion_notificaciones_version{
    bool enviarNotificacion(nodo_Asintomatico2 objAsin)=1;
    }=1;
}=0x30000001;

