/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "interface1.h"
#include "interface2.h"
#include <string.h>
#include <time.h>
#include <stdbool.h>

/*For files*/
#include <stdio.h>
#include <stdlib.h>


int copado[1]={0}; /*Esto sirve de apoyo para obtener las ultimas 5 alertas*/
int copado2[1]={0};

int	escribirAlertaEnArchivo(nodo_Indicadores *argp, nodo_Asintomatico2 *asintomatico);
int	leerAlertasDesdeArchivo(nodo_Asintomatico2 *asintomatico);
int archivoEscribir(char *cadena, char *nombreArchivo);
int archivoLeer(char *nombreArchivo, nodo_Asintomatico2 *asintomatico);
int obtenerPuntuacionDeAlerta(nodo_Indicadores *argp);
int registrarAsintomaticoEnArchivo(nodo_Asintomatico *argp);
int existeAsintomaticoConId(nodo_Indicadores *argp, nodo_Asintomatico2 *structuraTemporal);

bool_t *
registrarasintomatico_1_svc(nodo_Asintomatico *argp, struct svc_req *rqstp)
{
	static bool_t result=1;/*1 no se registrò*/

	printf("Desde registrarasintomatico_1_svc()...\n");
	int valor = registrarAsintomaticoEnArchivo(argp);
	if(valor == 0){
		printf("  Se registrò con exito.\n");
		result=0;
	}else{
		printf("  No se realizò el registro.\n");
		result=1;
	}

	printf("Saliò de registrarasintomatico_1_svc()\n");
	return &result;
}

bool_t *
enviarindicadores_1_svc(nodo_Indicadores *argp, struct svc_req *rqstp)
{
	printf("Desde enviarindicadores_1_svc()...\n");

	CLIENT *clnt;
	bool_t  *result_1;
	nodo_Asintomatico2  enviarnotificacion_1_arg;
	char *host="localhost";

#ifndef	DEBUG
	clnt = clnt_create (host, gestion_notificaciones, gestion_notificaciones_version, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
	
#ifndef	DEBUG
#endif	 /* DEBUG */
	static bool_t  result;

	int puntuacion=0;
	nodo_Asintomatico2 registroTemporal;

	int existe = existeAsintomaticoConId(argp, &registroTemporal);/*Le paso una estructura nodo_Asintomatico2 vacia*/
	if(existe==0){
		escribirAlertaEnArchivo(argp,&registroTemporal);/*Registra alerta en el archivo del asintomatico*/
		puntuacion = obtenerPuntuacionDeAlerta(argp);
			
		
		if(puntuacion >=3 ){
			printf("  Se enviò al servidor la notificacion.\n");
			registroTemporal.ultimoIndicador2.frecuenciaCardiaca = argp->frecuenciaCardiaca;
			registroTemporal.ultimoIndicador2.frecuenciaRespiratoria = argp->frecuenciaRespiratoria;
			registroTemporal.ultimoIndicador2.temperatura = argp->temperatura;
			leerAlertasDesdeArchivo(&registroTemporal);/*Se le pasa el asintomatico para que llene los ùltimos 5 registros que se encuentran en el archivo del asintomatico*/
			registroTemporal.ultimoIndicador = puntuacion;/*Se adjunta la ùltima puntuacion*/
			result_1 = enviarnotificacion_1(&registroTemporal, clnt);
			if (result_1 == (bool_t *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		}
	}

	printf("Saliò de enviarindicadores_1_svc()\n");
	clnt_destroy (clnt);
	return &result;
}


int	escribirAlertaEnArchivo(nodo_Indicadores *argp, nodo_Asintomatico2 *asintomatico){
	
	time_t t = time(NULL);
 	struct tm tm = *localtime(&t);
	
	char nombreArchivo[10];
	char registro[200];
	char fecha[10];
	char hora[10];
	int puntuacion = obtenerPuntuacionDeAlerta(argp);

	snprintf(fecha, sizeof(fecha), "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	snprintf(hora, sizeof(hora), "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
	snprintf(registro, sizeof(registro), "%s %d %s %s %s %s %d",asintomatico->tipo_id,asintomatico->id,asintomatico->nombre,asintomatico->apellido,fecha,hora,puntuacion);

	/*Creacion del nombre del archivo*/
	strcat(nombreArchivo,"HistorialDeAlertas/");/*Dentro del directorio*/
	strcat(nombreArchivo,asintomatico->tipo_id);
	char buffer[5];
	int ret = snprintf(buffer, sizeof buffer, "%d", asintomatico->id);
	strcat(nombreArchivo, buffer);
	strcat(nombreArchivo,".txt");
	archivoEscribir(registro, nombreArchivo);

	return 0;
}


int	leerAlertasDesdeArchivo(nodo_Asintomatico2 *asintomatico){
	
	time_t t = time(NULL);
 	struct tm tm = *localtime(&t);
	
	char nombreArchivo[10];

	/*Creacion del nombre del archivo*/
	strcat(nombreArchivo,"HistorialDeAlertas/");/*Dentro del directorio*/
	strcat(nombreArchivo,asintomatico->tipo_id);
	char buffer[5];
	int ret = snprintf(buffer, sizeof buffer, "%d", asintomatico->id);
	strcat(nombreArchivo, buffer);
	strcat(nombreArchivo,".txt");

	archivoLeer(nombreArchivo,asintomatico);

	return 0;
}


int obtenerPuntuacionDeAlerta(nodo_Indicadores *argp){
	int suma = 0;
	if(argp->frecuenciaCardiaca >= 60 && argp->frecuenciaCardiaca<=80 ){
		suma++;
	}
	if(argp->frecuenciaRespiratoria >= 70 && argp->frecuenciaRespiratoria<=90 ){
		suma++;
	}
	if(argp->temperatura >= 36.2 && argp->temperatura<=37.2 ){
		suma++;
	}
	return suma;
}

int archivoEscribir(char *cadena, char *nombreArchivo)/*Este metodo es invocado por:  escribirAlertaEnArchivo()*/
{
	FILE *archivo;
	archivo = fopen(nombreArchivo,"at");

	if (archivo == NULL)
	{
		printf("Erro al abrir el archivo en archivoEscribir");
	} 		
	else
	{
		fputs(cadena, archivo);
		fputs("\n", archivo);
		fclose(archivo);
		printf("  Se realizò la alerta.\n");

	}
	
	return 0;
}


int archivoLeer(char *nombreArchivo, nodo_Asintomatico2 *asintomatico)/*Este metodo es invocado por: leerAlertasDesdeArchivo()*/
{
	FILE *archivo;
	
	char lineaLeida[100];
	char lineaUltima[100];
	struct linea{ 
			char registro[100];
	};
	struct linea arreglo[5];

	
	archivo = fopen(nombreArchivo,"r");

	if (archivo == NULL)
	{
		printf("Erro al abrir el archivo en archivoLeer");
	} 		
	else
	{
		strcpy(arreglo[0].registro, ".");/* la inicializacion me indicarà de que està vacio el arreglo*/
		strcpy(arreglo[1].registro, ".");
		strcpy(arreglo[2].registro, ".");
		strcpy(arreglo[3].registro, ".");
		strcpy(arreglo[4].registro, ".");


		//int vuelta=0;
		while (feof(archivo) == 0)
		{
			//vuelta++;
			fgets(lineaLeida,100,archivo);
			//printf("# %d = %s \n",vuelta,lineaLeida);

			if(strcmp(lineaUltima,lineaLeida)!=0){
				strcpy(lineaUltima,lineaLeida);
				bool permanecer = TRUE;
				int i=-1;
				while(permanecer){	
					i++;
					if(strcmp(arreglo[i].registro,".")==0){
						strcpy(arreglo[i].registro,lineaLeida);				
						permanecer = FALSE;
					}
					if(i == 4){
						permanecer =FALSE;
						if(copado2[0]==0){
							copado[0]=1;
						}else{
							copado[0]=0;	
						}
					}	
				}
				
				if(copado[0]!=1 && strcmp(arreglo[4].registro,".")!=0 ){/*Toca desplazar los elementos*/
					arreglo[0] = arreglo[1];
					arreglo[1] = arreglo[2];
					arreglo[2] = arreglo[3];
					arreglo[3] = arreglo[4];
					strcpy(arreglo[4].registro,lineaLeida);				
				}
				
				if(copado[0]==1){
					copado2[0]=1;
				}	
				
			}/*Cierre del if*/
			
		}/*Cierre del while*/
		fclose(archivo);
	}/*Cierre del else*/




	for(int i=0 ; i<5; i++){
		int iteraciones=1;
		char * token = strtok(arreglo[i].registro, " ");
		while( token != NULL ) {
			if(iteraciones == 5){
				strcpy(asintomatico->alertas[i].fecha,token);
			}
			if(iteraciones == 6){
				strcpy(asintomatico->alertas[i].hora,token);
			}
			if(iteraciones == 7){
				asintomatico->alertas[i].puntuacion = atoi(token);
			}
			token = strtok(NULL, " ");
			iteraciones++;
  	 	}
	}
					
	copado[0]=0;
	copado2[0]=0;
	return 0;
}


int registrarAsintomaticoEnArchivo(nodo_Asintomatico *argp)
{
	FILE *archivo;	
	char lineaLeida[100];
	archivo = fopen("Asintomaticos/registrados.txt","a+");
	int esRegistrado = 0;/*1=no se registro*/

	if (archivo == NULL)
	{
		printf("Erro al abrir el archivo en regisrtrarAsintomaticoEnArchivo");
	} 		
	else
	{
		char pruebanombre[30];
		char pruebaapellido[30];
		char pruebatipoid[10];
		int  pruebaid;
		char pruebadireccion[30];
		
		//int vuelta=0;
		while (feof(archivo) == 0)
		{
			//vuelta++;
			fgets(lineaLeida,100,archivo);
			//printf("# %d = %s \n",vuelta,lineaLeida);
			
			char * token = strtok(lineaLeida, " ");
			int iteraciones=1;
			while( token != NULL ) {
				if(iteraciones == 1){
					strcpy(pruebatipoid,token);
				}
				if(iteraciones == 2){
					pruebaid = atoi(token);
				}
				token = strtok(NULL, " ");
				iteraciones++;
  	 		}
			if(strcmp(pruebatipoid,argp->tipo_id)==0 && pruebaid==argp->id){
				esRegistrado=1; 
			}			
		}
		
		if(esRegistrado==0){
			char nuevoRegistro[100];	
			snprintf(nuevoRegistro, sizeof(nuevoRegistro), "%s %d %s %s %s",argp->tipo_id,argp->id,argp->nombre,argp->apellido,argp->direccion);
			fputs(nuevoRegistro, archivo);
			fputs("\n", archivo);
		}

		fclose(archivo);
	}/*Cierre del else*/
	
	return esRegistrado;
}


int existeAsintomaticoConId(nodo_Indicadores *argp, nodo_Asintomatico2 *structuraTemporal)
{
	FILE *archivo;	
	char lineaLeida[100];
	archivo = fopen("Asintomaticos/registrados.txt","a+");
	int existe= 1;/*1=no existe*/

	if (archivo == NULL)
	{
		printf("Erro al abrir el archivo en existeAsintomaticoConId");
	} 		
	else
	{
		char nombre[30];
		char apellido[30];
		char tipoid[10];
		int  id;
		char direccion[30];
		
		//int vuelta=0;
		while (feof(archivo) == 0)
		{
			//vuelta++;
			fgets(lineaLeida,100,archivo);
			//printf("# %d = %s \n",vuelta,lineaLeida);
			
			char * token = strtok(lineaLeida, " ");
			int iteraciones=1;
			while( token != NULL ) {
				if(iteraciones == 1){
					strcpy(tipoid,token);
				}
				if(iteraciones == 2){
					id = atoi(token);
				}
				if(iteraciones == 3){
					strcpy(nombre,token);
				}
				if(iteraciones == 4){
					strcpy(apellido,token);
				}
				if(iteraciones == 5){
					strcpy(direccion,token);
				}
				token = strtok(NULL, " ");
				iteraciones++;
  	 		}
			if(strcmp(tipoid,argp->tipo_id)==0 && id==argp->id){/*Si existe el asintomatico, entonces llenamos la estructura*/
				strcpy(structuraTemporal->tipo_id,tipoid);
				structuraTemporal->id = id;
				strcpy(structuraTemporal->nombre,nombre);
				strcpy(structuraTemporal->apellido,apellido);
				strcpy(structuraTemporal->direccion,direccion);
				structuraTemporal->alertas[0].puntuacion = -1;
				structuraTemporal->alertas[1].puntuacion = -1;
				structuraTemporal->alertas[2].puntuacion = -1;
				structuraTemporal->alertas[3].puntuacion = -1;
				structuraTemporal->alertas[4].puntuacion = -1;
				existe=0; 
			}			
		}
		fclose(archivo);
	}/*Cierre del else*/
	
	return existe;
}


