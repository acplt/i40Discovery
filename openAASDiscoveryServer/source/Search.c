
/******************************************************************************
*
*   FILE
*   ----
*   Search.c
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
#include "libov/ov_path.h"


OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_AddSEWrapper_set(
    OV_INSTPTR_openAASDiscoveryServer_Search          pobj,
    const OV_BOOL  value
) {
    pobj->v_AddSEWrapper = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_RemoveSEWrapper_set(
    OV_INSTPTR_openAASDiscoveryServer_Search          pobj,
    const OV_BOOL  value
) {
    pobj->v_RemoveSEWrapper = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_ProcessSearchMessage_set(
    OV_INSTPTR_openAASDiscoveryServer_Search          pobj,
    const OV_BOOL  value
) {
    pobj->v_ProcessSearchMessage = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS openAASDiscoveryServer_Search_getaccess(
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
					if(pelem->elemunion.pvar->v_flags == 256) { // InputFlag is set
						return OV_AC_READWRITE;
					}
					/* Nicht FB? */
					if(pelem->elemunion.pvar->v_varprops & OV_VP_SETACCESSOR) {
						return OV_AC_READWRITE;
					}
					return OV_AC_READ;
				}
			}
		break;
		default:
		break;
	}

	return ov_object_getaccess(pobj, pelem, pticket);
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    //OV_INSTPTR_openAASDiscoveryServer_Search pinst = Ov_StaticPtrCast(openAASDiscoveryServer_Search, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = openAASDiscoveryServer_Part_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */


    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_addSEWrapper(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *SEWrapper, OV_UINT veclen) {
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openAASDiscoveryServer_Search pSearch = NULL;
	pSearch = Ov_DynamicPtrCast(openAASDiscoveryServer_Search, pinst);
	if (!pSearch){
		return OV_ERR_BADOBJTYPE;
	}
	for (OV_UINT i = 0; i < veclen; i++){
		pobj = ov_path_getobjectpointer(SEWrapper[i], 2);
		if (Ov_CanCastTo(openAASDiscoveryServer_SEWrapper, pobj) == FALSE){
			return OV_ERR_BADOBJTYPE;
		}
		if (pSearch->v_SEWrapper.veclen == 0){
			Ov_SetDynamicVectorLength(&pSearch->v_SEWrapper, pSearch->v_SEWrapper.veclen + 1, STRING);
			ov_string_setvalue(&pSearch->v_SEWrapper.value[pSearch->v_SEWrapper.veclen - 1], SEWrapper[i]);
			continue;
		}
		for (OV_UINT j = 0; j < pSearch->v_SEWrapper.veclen; j++){
			if (ov_string_compare(SEWrapper[i], pSearch->v_SEWrapper.value[j]) == OV_STRCMP_EQUAL){
				break;
			}
			if (j == pSearch->v_SEWrapper.veclen - 1){
				Ov_SetDynamicVectorLength(&pSearch->v_SEWrapper, pSearch->v_SEWrapper.veclen + 1, STRING);
				ov_string_setvalue(&pSearch->v_SEWrapper.value[pSearch->v_SEWrapper.veclen - 1], SEWrapper[i]);
			}
		}
	}
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_removeSEWrapper(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *SEWrapper, OV_UINT veclen) {
	OV_INSTPTR_openAASDiscoveryServer_Search pSearch = NULL;
	pSearch = Ov_DynamicPtrCast(openAASDiscoveryServer_Search, pinst);
	if (!pSearch){
		return OV_ERR_BADOBJTYPE;
	}
	for (OV_UINT i = 0; i < veclen; i++){
		for (OV_UINT j = 0; j < pSearch->v_SEWrapper.veclen; j++){
			if (ov_string_compare(SEWrapper[i], pSearch->v_SEWrapper.value[j]) == OV_STRCMP_EQUAL){
				for(OV_UINT k = j; k < pSearch->v_SEWrapper.veclen-1; k++){
					ov_string_setvalue(&pSearch->v_SEWrapper.value[k], pSearch->v_SEWrapper.value[k+1]);
				}
				Ov_SetDynamicVectorLength(&pSearch->v_SEWrapper, pSearch->v_SEWrapper.veclen - 1, STRING);
			}
		}
	}
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_addDSService(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *DSService, OV_UINT veclen) {
    /*    
    *   local variables
    */
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openAASDiscoveryServer_Search pSearch = NULL;
	pSearch = Ov_DynamicPtrCast(openAASDiscoveryServer_Search, pinst);
	if (!pSearch){
		return OV_ERR_BADOBJTYPE;
	}
	for (OV_UINT i = 0; i < veclen; i++){
		pobj = ov_path_getobjectpointer(DSService[i], 2);
		if (Ov_CanCastTo(openAASDiscoveryServer_DSSearchService, pobj) == FALSE){
			return OV_ERR_BADOBJTYPE;
		}
		if (pSearch->v_DSService.veclen == 0){
			Ov_SetDynamicVectorLength(&pSearch->v_DSService, pSearch->v_DSService.veclen + 1, STRING);
			ov_string_setvalue(&pSearch->v_DSService.value[pSearch->v_DSService.veclen - 1], DSService[i]);
			continue;
		}
		for (OV_UINT j = 0; j < pSearch->v_DSService.veclen; j++){
			if (ov_string_compare(DSService[i], pSearch->v_DSService.value[j]) == OV_STRCMP_EQUAL){
				break;
			}
			if (j == pSearch->v_DSService.veclen - 1){
				Ov_SetDynamicVectorLength(&pSearch->v_DSService, pSearch->v_DSService.veclen + 1, STRING);
				ov_string_setvalue(&pSearch->v_DSService.value[pSearch->v_DSService.veclen - 1], DSService[i]);
			}
		}
	}
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_removeDSService(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *DSService, OV_UINT veclen) {
    /*    
    *   local variables
    */
	OV_INSTPTR_openAASDiscoveryServer_Search pSearch = NULL;
	pSearch = Ov_DynamicPtrCast(openAASDiscoveryServer_Search, pinst);
	if (!pSearch){
		return OV_ERR_BADOBJTYPE;
	}
	for (OV_UINT i = 0; i < veclen; i++){
		for (OV_UINT j = 0; j < pSearch->v_DSService.veclen; j++){
			if (ov_string_compare(DSService[i], pSearch->v_DSService.value[j]) == OV_STRCMP_EQUAL){
				for(OV_UINT k = j; k < pSearch->v_DSService.veclen-1; k++){
					ov_string_setvalue(&pSearch->v_DSService.value[k], pSearch->v_DSService.value[k+1]);
				}
				Ov_SetDynamicVectorLength(&pSearch->v_DSService, pSearch->v_DSService.veclen - 1, STRING);
			}
		}
	}
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_configureDSService(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *DBWrapper, OV_UINT veclenDBWrapper, OV_STRING *URMSWrapper, OV_UINT veclenURMSWrapper, OV_STRING *CAWrapper, OV_UINT veclenCAWrapper, OV_STRING *SEWrapper, OV_UINT veclenSEWrapper, OV_STRING DSService) {
    /*    
    *   local variables
    */
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openAASDiscoveryServer_Search pSearch = NULL;
	pSearch = Ov_DynamicPtrCast(openAASDiscoveryServer_Search, pinst);
	if (!pSearch){
		return OV_ERR_BADOBJTYPE;
	}
	// Is Service registered?
	OV_BOOL foundDSService = FALSE;
	for (OV_UINT j = 0; j < pSearch->v_DSService.veclen; j++){
		if (ov_string_compare(DSService, pSearch->v_DSService.value[j]) == OV_STRCMP_EQUAL){
			foundDSService = TRUE;
			break;
		}
	}
	if(foundDSService == FALSE){
		return OV_ERR_BADSELECTOR;
	}

	pobj = ov_path_getobjectpointer(DSService, 2);
	if (!pobj){
		return OV_ERR_NOACCESS;
	}
	OV_INSTPTR_openAASDiscoveryServer_DSSearchService pDSSearch = NULL;
	pDSSearch = Ov_DynamicPtrCast(openAASDiscoveryServer_DSSearchService, pobj);
	if (!pDSSearch){
		return OV_ERR_BADOBJTYPE;
	}
	OV_BOOL foundDBWrapper = TRUE;
	for (OV_UINT i = 0; i < veclenDBWrapper; i++){
		for (OV_UINT j = 0; j < pSearch->v_DBWrapper.veclen; j++){
			if (ov_string_compare(DBWrapper[i], pSearch->v_DBWrapper.value[j]) == OV_STRCMP_EQUAL){
				break;
			}
			if (j == pSearch->v_DBWrapper.veclen - 1){
				foundDBWrapper = FALSE;
			}
		}
	}
	if (foundDBWrapper == FALSE){
		return OV_ERR_BADSELECTOR;
	}
	Ov_SetDynamicVectorValue(&pDSSearch->v_DBWrapperUsed, DBWrapper, veclenDBWrapper, STRING);

	OV_BOOL foundSEWrapper = TRUE;
	for (OV_UINT i = 0; i < veclenSEWrapper; i++){
		for (OV_UINT j = 0; j < pSearch->v_SEWrapper.veclen; j++){
			if (ov_string_compare(SEWrapper[i], pSearch->v_SEWrapper.value[j]) == OV_STRCMP_EQUAL){
				break;
			}
			if (j == pSearch->v_SEWrapper.veclen - 1){
				foundSEWrapper = FALSE;
			}
		}
	}
	if (foundSEWrapper == FALSE){
		return OV_ERR_BADSELECTOR;
	}
	Ov_SetDynamicVectorValue(&pDSSearch->v_SEWrapperUsed, SEWrapper, veclenSEWrapper, STRING);

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Search_getSearchMessage(OV_INSTPTR_openAASDiscoveryServer_Part pinst, const json_data body, OV_STRING *JsonOutput, OV_STRING *errorMessage) {
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openAASDiscoveryServer_DSSearchService pService = NULL;
	OV_STRING tmpJsonOutput = NULL;
	*JsonOutput = NULL;
	for (OV_UINT i = 0; i < pinst->v_UsedDSServicePaths.veclen; i++){
		pobj = ov_path_getobjectpointer(pinst->v_UsedDSServicePaths.value[i], 2);
		if (!pobj){
			continue;
		}
		pService = Ov_DynamicPtrCast(openAASDiscoveryServer_DSSearchService, pobj);
		if (!pService){
			continue;
		}
		OV_VTBLPTR_openAASDiscoveryServer_DSService pvtable = NULL;
		Ov_GetVTablePtr(openAASDiscoveryServer_DSService, pvtable, pService);
		if (i == 0)
			pvtable->m_executeService(Ov_DynamicPtrCast(openAASDiscoveryServer_DSService, pService), body, JsonOutput);
		else
			pvtable->m_executeService(Ov_DynamicPtrCast(openAASDiscoveryServer_DSService, pService), body, &tmpJsonOutput);
	}
	if (!*JsonOutput){
		ov_string_setvalue(errorMessage, "Internal Error");
		ov_string_setvalue(JsonOutput, "\"body\"{}");
		return OV_ERR_GENERIC;
	}
	if (tmpJsonOutput){
		ov_logfile_info("%s", tmpJsonOutput);
		ov_string_setvalue(&tmpJsonOutput, NULL);
	}
    return OV_ERR_OK;
}

