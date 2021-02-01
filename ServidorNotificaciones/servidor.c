/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "interface2.h"

bool_t *
enviarnotificacion_1_svc(nodo_Asintomatico2 *argp, struct svc_req *rqstp)
{
	static bool_t  result;

	printf("Desde enviarnotificacion_1_svc()...\n");
	printf("\n                        ALERTA GENERADA                        \n");
	printf("No de id: %s %d\n",argp->tipo_id,argp->id);
	printf("Nombre y Apellidos: %s %s\n",argp->nombre,argp->apellido);
	printf("Direccion: %s\n",argp->direccion);
	printf("Hora de alerta: %s\n",argp->alertas[4].hora);
	printf("Hora de alerta: %s\n",argp->alertas[4].fecha);
	printf("                                                        \n");
	printf("\n              Indicadores que generaron la alerta             \n");
	printf(" ______________________________________________________________ \n");
	printf("|                                   |                          |\n");
	printf("|         Nombre del indicador      |           Valor          |\n");
	printf("|___________________________________|__________________________|\n");
	printf("|       Frecuencia cardiaca:        |           %.2f          |\n",argp->ultimoIndicador2.frecuenciaCardiaca);
	printf("|       Frecuencia respiratoria:    |           %.2f          |\n",argp->ultimoIndicador2.frecuenciaRespiratoria);
	printf("|       Temperatura:                |           %.2f          |\n",argp->ultimoIndicador2.temperatura);
	printf("|___________________________________|__________________________|\n");
	printf("                                                                \n");
	printf("     La enfermera o el medico deben revisar al paciente:        \n");
	printf("                     %s %s con %s.%d                            \n",argp->nombre,argp->apellido,argp->tipo_id,argp->id);
	printf("                                                                \n");
	printf("                        Ultimas 5 alertas                       \n");
	printf(" ______________________________________________________________ \n");
	printf("|                      |                     |                 |\n");
	printf("|     Fecha alerta     |    Hora de alerta   |    Puntuacion   |\n");
	printf("|______________________|_____________________|_________________|\n");
	for(int i=0 ; i< 5 ;i++){
		if(argp->alertas[i].puntuacion != -1){
			printf("|      %s       |      %s	     |     %0.2f        |\n",argp->alertas[i].fecha,argp->alertas[i].hora,argp->alertas[i].puntuacion);
		}
	}
	printf("|______________________|_____________________|_________________|\n");
	printf("Saliò de enviarnotificacion_1_svc()\n");

	return &result;
}