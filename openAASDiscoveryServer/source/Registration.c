
/******************************************************************************
*
*   FILE
*   ----
*   Registration.c
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

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_AddSEWrapper_set(
    OV_INSTPTR_openAASDiscoveryServer_Registration          pobj,
    const OV_BOOL  value
) {
    pobj->v_AddSEWrapper = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_RemoveSEWrapper_set(
    OV_INSTPTR_openAASDiscoveryServer_Registration          pobj,
    const OV_BOOL  value
) {
    pobj->v_RemoveSEWrapper = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_ProcessRegistrationMessage_set(
    OV_INSTPTR_openAASDiscoveryServer_Registration          pobj,
    const OV_BOOL  value
) {
    pobj->v_ProcessRegistrationMessage = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_ProcessUnregistrationMessage_set(
    OV_INSTPTR_openAASDiscoveryServer_Registration          pobj,
    const OV_BOOL  value
) {
    pobj->v_ProcessUnregistrationMessage = value;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS openAASDiscoveryServer_Registration_getaccess(
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

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*    
    *   local variables
    */
    //OV_INSTPTR_openAASDiscoveryServer_Registration pinst = Ov_StaticPtrCast(openAASDiscoveryServer_Registration, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = openAASDiscoveryServer_Part_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */


    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_addSEWrapper(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *SEWrapper, OV_UINT veclen) {
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openAASDiscoveryServer_Registration pRegistration = NULL;
	pRegistration = Ov_DynamicPtrCast(openAASDiscoveryServer_Registration, pinst);
	if (!pRegistration){
		return OV_ERR_BADOBJTYPE;
	}
	for (OV_UINT i = 0; i < veclen; i++){
		pobj = ov_path_getobjectpointer(SEWrapper[i], 2);
		if (Ov_CanCastTo(openAASDiscoveryServer_SEWrapper, pobj) == FALSE){
			return OV_ERR_BADOBJTYPE;
		}
		if (pRegistration->v_SEWrapper.veclen == 0){
			Ov_SetDynamicVectorLength(&pRegistration->v_SEWrapper, pRegistration->v_SEWrapper.veclen + 1, STRING);
			ov_string_setvalue(&pRegistration->v_SEWrapper.value[pRegistration->v_SEWrapper.veclen - 1], SEWrapper[i]);
			continue;
		}
		for (OV_UINT j = 0; j < pRegistration->v_SEWrapper.veclen; j++){
			if (ov_string_compare(SEWrapper[i], pRegistration->v_SEWrapper.value[j]) == OV_STRCMP_EQUAL){
				break;
			}
			if (j == pRegistration->v_SEWrapper.veclen - 1){
				Ov_SetDynamicVectorLength(&pRegistration->v_SEWrapper, pRegistration->v_SEWrapper.veclen + 1, STRING);
				ov_string_setvalue(&pRegistration->v_SEWrapper.value[pRegistration->v_SEWrapper.veclen - 1], SEWrapper[i]);
			}
		}
	}
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_removeSEWrapper(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *SEWrapper, OV_UINT veclen) {
	OV_INSTPTR_openAASDiscoveryServer_Registration pRegistration = NULL;
	pRegistration = Ov_DynamicPtrCast(openAASDiscoveryServer_Registration, pinst);
	if (!pRegistration){
		return OV_ERR_BADOBJTYPE;
	}
	for (OV_UINT i = 0; i < veclen; i++){
		for (OV_UINT j = 0; j < pRegistration->v_SEWrapper.veclen; j++){
			if (ov_string_compare(SEWrapper[i], pRegistration->v_SEWrapper.value[j]) == OV_STRCMP_EQUAL){
				for(OV_UINT k = j; k < pRegistration->v_SEWrapper.veclen-1; k++){
					ov_string_setvalue(&pRegistration->v_SEWrapper.value[k], pRegistration->v_SEWrapper.value[k+1]);
				}
				Ov_SetDynamicVectorLength(&pRegistration->v_SEWrapper, pRegistration->v_SEWrapper.veclen - 1, STRING);
			}
		}
	}
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_addDSService(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *DSService, OV_UINT veclen) {
    /*    
    *   local variables
    */
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openAASDiscoveryServer_Registration pRegistration = NULL;
	pRegistration = Ov_DynamicPtrCast(openAASDiscoveryServer_Registration, pinst);
	if (!pRegistration){
		return OV_ERR_BADOBJTYPE;
	}
	for (OV_UINT i = 0; i < veclen; i++){
		pobj = ov_path_getobjectpointer(DSService[i], 2);
		if (Ov_CanCastTo(openAASDiscoveryServer_DSRegistrationService, pobj) == FALSE){
			if (Ov_CanCastTo(openAASDiscoveryServer_DSUnRegistrationService, pobj) == FALSE){
				return OV_ERR_BADOBJTYPE;
			}
		}
		if (pRegistration->v_DSService.veclen == 0){
			Ov_SetDynamicVectorLength(&pRegistration->v_DSService, pRegistration->v_DSService.veclen + 1, STRING);
			ov_string_setvalue(&pRegistration->v_DSService.value[pRegistration->v_DSService.veclen - 1], DSService[i]);
			continue;
		}
		for (OV_UINT j = 0; j < pRegistration->v_DSService.veclen; j++){
			if (ov_string_compare(DSService[i], pRegistration->v_DSService.value[j]) == OV_STRCMP_EQUAL){
				break;
			}
			if (j == pRegistration->v_DSService.veclen - 1){
				Ov_SetDynamicVectorLength(&pRegistration->v_DSService, pRegistration->v_DSService.veclen + 1, STRING);
				ov_string_setvalue(&pRegistration->v_DSService.value[pRegistration->v_DSService.veclen - 1], DSService[i]);
			}
		}
	}
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_removeDSService(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *DSService, OV_UINT veclen) {
    /*    
    *   local variables
    */
	OV_INSTPTR_openAASDiscoveryServer_Registration pRegistration = NULL;
	pRegistration = Ov_DynamicPtrCast(openAASDiscoveryServer_Registration, pinst);
	if (!pRegistration){
		return OV_ERR_BADOBJTYPE;
	}
	for (OV_UINT i = 0; i < veclen; i++){
		for (OV_UINT j = 0; j < pRegistration->v_DSService.veclen; j++){
			if (ov_string_compare(DSService[i], pRegistration->v_DSService.value[j]) == OV_STRCMP_EQUAL){
				for(OV_UINT k = j; k < pRegistration->v_DSService.veclen-1; k++){
					ov_string_setvalue(&pRegistration->v_DSService.value[k], pRegistration->v_DSService.value[k+1]);
				}
				Ov_SetDynamicVectorLength(&pRegistration->v_DSService, pRegistration->v_DSService.veclen - 1, STRING);
			}
		}
	}
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_configureDSService(OV_INSTPTR_openAASDiscoveryServer_Part pinst, OV_STRING *DBWrapper, OV_UINT veclenDBWrapper, OV_STRING *URMSWrapper, OV_UINT veclenURMSWrapper, OV_STRING *CAWrapper, OV_UINT veclenCAWrapper, OV_STRING *SEWrapper, OV_UINT veclenSEWrapper, OV_STRING DSService) {
    /*    
    *   local variables
    */
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openAASDiscoveryServer_Registration pRegistration = NULL;
	pRegistration = Ov_DynamicPtrCast(openAASDiscoveryServer_Registration, pinst);
	if (!pRegistration){
		return OV_ERR_BADOBJTYPE;
	}
	// Is Service registered?
	OV_BOOL foundDSService = FALSE;
	for (OV_UINT j = 0; j < pRegistration->v_DSService.veclen; j++){
		if (ov_string_compare(DSService, pRegistration->v_DSService.value[j]) == OV_STRCMP_EQUAL){
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
	OV_INSTPTR_openAASDiscoveryServer_DSRegistrationService pDSRegistration = NULL;
	OV_INSTPTR_openAASDiscoveryServer_DSUnRegistrationService pDSUnregistration = NULL;
	pDSRegistration = Ov_DynamicPtrCast(openAASDiscoveryServer_DSRegistrationService, pobj);
	pDSUnregistration = Ov_DynamicPtrCast(openAASDiscoveryServer_DSUnRegistrationService, pobj);
	if (!pDSRegistration && !pDSUnregistration){
		return OV_ERR_BADOBJTYPE;
	}
	OV_BOOL foundDBWrapper = TRUE;
	for (OV_UINT i = 0; i < veclenDBWrapper; i++){
		for (OV_UINT j = 0; j < pRegistration->v_DBWrapper.veclen; j++){
			if (ov_string_compare(DBWrapper[i], pRegistration->v_DBWrapper.value[j]) == OV_STRCMP_EQUAL){
				break;
			}
			if (j == pRegistration->v_DBWrapper.veclen - 1){
				foundDBWrapper = FALSE;
			}
		}
	}
	if (foundDBWrapper == FALSE){
		return OV_ERR_BADSELECTOR;
	}
	if (pDSRegistration)
		Ov_SetDynamicVectorValue(&pDSRegistration->v_DBWrapperUsed, DBWrapper, veclenDBWrapper, STRING);
	else
		Ov_SetDynamicVectorValue(&pDSUnregistration->v_DBWrapperUsed, DBWrapper, veclenDBWrapper, STRING);

	OV_BOOL foundSEWrapper = TRUE;
	for (OV_UINT i = 0; i < veclenSEWrapper; i++){
		for (OV_UINT j = 0; j < pRegistration->v_SEWrapper.veclen; j++){
			if (ov_string_compare(SEWrapper[i], pRegistration->v_SEWrapper.value[j]) == OV_STRCMP_EQUAL){
				if (pDSRegistration){
					if (Ov_CanCastTo(openAASDiscoveryServer_DSRegistrationService, ov_path_getobjectpointer(SEWrapper[i], 2))){
						break;
					}
				}else{
					if (Ov_CanCastTo(openAASDiscoveryServer_DSUnRegistrationService, ov_path_getobjectpointer(SEWrapper[i], 2))){
						break;
					}
				}
				break;
			}
			if (j == pRegistration->v_SEWrapper.veclen - 1){
				foundSEWrapper = FALSE;
			}
		}
	}
	if (foundSEWrapper == FALSE){
		return OV_ERR_BADSELECTOR;
	}
	if (pDSRegistration)
		Ov_SetDynamicVectorValue(&pDSRegistration->v_SEWrapperUsed, SEWrapper, veclenSEWrapper, STRING);
	else
		Ov_SetDynamicVectorValue(&pDSUnregistration->v_SEWrapperUsed, SEWrapper, veclenSEWrapper, STRING);

    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_getRegistrationMessage(OV_INSTPTR_openAASDiscoveryServer_Part pinst, const json_data body, OV_STRING *JsonOutput, OV_STRING *errorMessage) {
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openAASDiscoveryServer_DSRegistrationService pService = NULL;
	OV_STRING tmpJsonOutput = NULL;
	*JsonOutput = NULL;
	for (OV_UINT i = 0; i < pinst->v_UsedDSServicePaths.veclen; i++){
		pobj = ov_path_getobjectpointer(pinst->v_UsedDSServicePaths.value[i], 2);
		if (!pobj){
			continue;
		}
		pService = Ov_DynamicPtrCast(openAASDiscoveryServer_DSRegistrationService, pobj);
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

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_Registration_getUnregistrationMessage(OV_INSTPTR_openAASDiscoveryServer_Part pinst, const json_data body, OV_STRING *JsonOutput, OV_STRING *errorMessage) {
	OV_INSTPTR_ov_object pobj = NULL;
	OV_INSTPTR_openAASDiscoveryServer_DSUnRegistrationService pService = NULL;
	OV_STRING tmpJsonOutput = NULL;
	*JsonOutput = NULL;
	for (OV_UINT i = 0; i < pinst->v_UsedDSServicePaths.veclen; i++){
		pobj = ov_path_getobjectpointer(pinst->v_UsedDSServicePaths.value[i], 2);
		if (!pobj){
			continue;
		}
		pService = Ov_DynamicPtrCast(openAASDiscoveryServer_DSUnRegistrationService, pobj);
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

