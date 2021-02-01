/*Declaracion de datos a transferir entre el cliente y el servidor de alertas*/
/*Declaracion de constantes*/
const MAXCADENA = 30;
const MINCADENA = 5;

struct nodo_Indicadores{
    char tipo_id[MINCADENA];
    int id;
    float frecuenciaCardiaca;
    float frecuenciaRespiratoria;
    float temperatura;
};

/*Declaracion de la estructura que permite almacenar los datos de un anteproyecto*/

struct nodo_Asintomatico{
    char nombre[MAXCADENA];
    char apellido[MAXCADENA];
    char tipo_id[MINCADENA];
    int id;
    char direccion[MAXCADENA];
};

/*Definicion de las operaciones que se pueden realizar*/
program gestion_alertas{
version gestion_alertas_version{
    bool registrarAsintomatico(nodo_Asintomatico objAsin)=1;
    bool enviarIndicadores(nodo_Indicadores objIndi)=2;
    }=1;
}=0x20000001;
