/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _INTERFACE2_H_RPCGEN
#define _INTERFACE2_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif

#define MAXCADENA 30
#define MEDCADENA 15
#define MINCADENA 5

struct nodo_Alertas2 {
	char fecha[MEDCADENA];
	char hora[MEDCADENA];
	float puntuacion;
};
typedef struct nodo_Alertas2 nodo_Alertas2;

struct nodo_Indicadores2 {
	float frecuenciaCardiaca;
	float frecuenciaRespiratoria;
	float temperatura;
};
typedef struct nodo_Indicadores2 nodo_Indicadores2;

struct nodo_Asintomatico2 {
	char nombre[MAXCADENA];
	char apellido[MAXCADENA];
	char tipo_id[MINCADENA];
	int id;
	char direccion[MAXCADENA];
	int ultimoIndicador;
	nodo_Indicadores2 ultimoIndicador2;
	nodo_Alertas2 alertas[5];
};
typedef struct nodo_Asintomatico2 nodo_Asintomatico2;

#define gestion_notificaciones 0x30000001
#define gestion_notificaciones_version 1

#if defined(__STDC__) || defined(__cplusplus)
#define enviarNotificacion 1
extern  bool_t * enviarnotificacion_1(nodo_Asintomatico2 *, CLIENT *);
extern  bool_t * enviarnotificacion_1_svc(nodo_Asintomatico2 *, struct svc_req *);
extern int gestion_notificaciones_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define enviarNotificacion 1
extern  bool_t * enviarnotificacion_1();
extern  bool_t * enviarnotificacion_1_svc();
extern int gestion_notificaciones_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_nodo_Alertas2 (XDR *, nodo_Alertas2*);
extern  bool_t xdr_nodo_Indicadores2 (XDR *, nodo_Indicadores2*);
extern  bool_t xdr_nodo_Asintomatico2 (XDR *, nodo_Asintomatico2*);

#else /* K&R C */
extern bool_t xdr_nodo_Alertas2 ();
extern bool_t xdr_nodo_Indicadores2 ();
extern bool_t xdr_nodo_Asintomatico2 ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_INTERFACE2_H_RPCGEN */
