
/******************************************************************************
*
*   FILE
*   ----
*   DBWrapper.c
*
*   History
*   -------
*   2018-05-04   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_openAASDiscoveryServer
#define OV_COMPILE_LIBRARY_openAASDiscoveryServer
#endif


#include "openAASDiscoveryServer.h"
#include "libov/ov_macros.h"


OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DBWrapper_StartConnect_set(
    OV_INSTPTR_openAASDiscoveryServer_DBWrapper          pobj,
    const OV_BOOL  value
) {
    pobj->v_StartConnect = value;

    if(pobj->v_StartConnect) {
    	OV_VTBLPTR_openAASDiscoveryServer_DBWrapper pvtable;
    	Ov_GetVTablePtr(openAASDiscoveryServer_DBWrapper,pvtable, pobj);
		pvtable->m_connect();
    }

    pobj->v_StartConnect = FALSE;

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS openAASDiscoveryServer_DBWrapper_getaccess(
	OV_INSTPTR_ov_object	pobj,
	const OV_ELEMENT		*pelem,
	const OV_TICKET			*pticket
) {
    /*    
    *   local variables
    */
	switch(pelem->elemtype) {
		case OV_ET_VARIABLE:
			if(pelem->elemunion.pvar->v_offset >= offsetof(OV_INST_ov_object,__classinfo)) {
				if(pelem->elemunion.pvar->v_vartype == OV_VT_CTYPE)
					return OV_AC_NONE;
				else{
					if((pelem->elemunion.pvar->v_varprops & OV_VP_DERIVED)){
						if((pelem->elemunion.pvar->v_varprops & OV_VP_SETACCESSOR)){
							return OV_AC_READWRITE;
						} else {
							return OV_AC_READ;
						}
					} else {
						return OV_AC_READWRITE;
					}
				}
			}
		break;
		default:
		break;
	}

	return ov_object_getaccess(pobj, pelem, pticket);
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DBWrapper_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    //OV_INSTPTR_openAASDiscoveryServer_DBWrapper pinst = Ov_StaticPtrCast(openAASDiscoveryServer_DBWrapper, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = ov_object_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */


    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DBWrapper_connect(void){

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DBWrapper_disconnect(void){

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DBWrapper_insertData(const OV_STRING table, const OV_STRING* fields, const OV_STRING* values) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DBWrapper_selectData(const OV_STRING table, const OV_STRING* fields, const OV_STRING* whereFields, OV_STRING* whereValues) {

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DBWrapper_deleteData(const OV_STRING table, const OV_STRING* fields, const OV_STRING* values) {

    return OV_ERR_OK;
}

