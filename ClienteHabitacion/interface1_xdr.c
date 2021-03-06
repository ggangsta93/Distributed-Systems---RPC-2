/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "interface1.h"

bool_t
xdr_nodo_Indicadores (XDR *xdrs, nodo_Indicadores *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->tipo_id, MINCADENA,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->id))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->frecuenciaCardiaca))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->frecuenciaRespiratoria))
		 return FALSE;
	 if (!xdr_float (xdrs, &objp->temperatura))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_nodo_Asintomatico (XDR *xdrs, nodo_Asintomatico *objp)
{
	register int32_t *buf;

	int i;
	 if (!xdr_vector (xdrs, (char *)objp->nombre, MAXCADENA,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->apellido, MAXCADENA,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->tipo_id, MINCADENA,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->id))
		 return FALSE;
	 if (!xdr_vector (xdrs, (char *)objp->direccion, MAXCADENA,
		sizeof (char), (xdrproc_t) xdr_char))
		 return FALSE;
	return TRUE;
}
