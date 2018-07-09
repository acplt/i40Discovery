
/******************************************************************************
*
*   FILE
*   ----
*   DSSecurityServiceType1.c
*
*   History
*   -------
*   2018-05-14   File created
*
*******************************************************************************
*
*   This file is generated by the 'acplt_builder' command
*
******************************************************************************/


#ifndef OV_COMPILE_LIBRARY_DSServices
#define OV_COMPILE_LIBRARY_DSServices
#endif


#include "DSServices.h"
#include "libov/ov_macros.h"
#include "json_helper.h"
#include "service_helper.h"
#include <time.h>


OV_DLLFNCEXPORT OV_RESULT DSServices_DSSecurityServiceType1_executeService(OV_INSTPTR_openAASDiscoveryServer_DSService pinst, const json_data JsonInput, OV_STRING *JsonOutput, OV_STRING *errorMessage) {
    /*    
    *   local variables
    */
	OV_RESULT resultOV = OV_ERR_OK;
	OV_STRING certificate = NULL;
	OV_STRING certificateDS = NULL;
	OV_STRING securityKey = NULL;
	OV_STRING componentID = NULL;

	OV_STRING table  = NULL;
	OV_STRING fields[3];
	OV_STRING fieldsValues[3];
	OV_STRING whereFields[1];
	OV_STRING wherevalues[1];

	// Parsing Body
	OV_STRING_VEC tags;
	tags.value = NULL;
	tags.veclen = 0;
	Ov_SetDynamicVectorLength(&tags, 2, STRING);
	OV_STRING_VEC values;
	values.value = NULL;
	values.veclen = 0;
	Ov_SetDynamicVectorLength(&values, 2, STRING);

	ov_string_setvalue(&tags.value[0], "componentID");
	ov_string_setvalue(&tags.value[1], "certificate");

	jsonGetValuesByTags(tags, JsonInput, 1, &values);

	ov_string_setvalue(&componentID, values.value[0]);
	ov_string_setvalue(&certificate, values.value[1]);

	// find certificate in DB
	table  = "SecurityData";
	fields[0] = "Certificate";
	whereFields[0] = "ComponentID";
	wherevalues[0] = NULL;
	ov_string_print(&wherevalues[0], "'%s'", componentID);
	OV_STRING_VEC result;
	result.value = NULL;
	result.veclen = 0;

	OV_BOOL certificateCheckSuccessful = FALSE;
	OV_INSTPTR_openAASDiscoveryServer_DBWrapper pDBWrapper = NULL;
	OV_VTBLPTR_openAASDiscoveryServer_DBWrapper pDBWrapperVTable = NULL;
	for (OV_UINT i = 0; i < pinst->v_DBWrapperUsed.veclen; i++){
		pDBWrapper = Ov_DynamicPtrCast(openAASDiscoveryServer_DBWrapper, ov_path_getobjectpointer(pinst->v_DBWrapperUsed.value[i], 2));
		if (!pDBWrapper){
			ov_string_setvalue(errorMessage, "Internal Error");
			ov_logfile_error("Could not find DBWrapper Object");
			goto FINALIZE;
		}
		// TODO check return value from selectData(...). If table is wrong DSService has a bad configuration or/and DBWrapper has a wrong config
		Ov_GetVTablePtr(openAASDiscoveryServer_DBWrapper,pDBWrapperVTable, pDBWrapper);
		OV_RESULT res = pDBWrapperVTable->m_selectData(table, fields, 1, whereFields, 1, wherevalues, 1, &result);
		if(res != OV_ERR_OK) {
			ov_string_setvalue(errorMessage, "Internal Error: SQL error");
			ov_logfile_error("Internal Error: SQL error");
			goto FINALIZE;
		}

		for (OV_UINT j = 0; j < result.veclen; j++){
			if (ov_string_compare(result.value[j], certificate) == OV_STRCMP_EQUAL){
				certificateCheckSuccessful = TRUE;
				Ov_SetDynamicVectorLength(&result, 0, STRING);
				break;
			}
		}
		if (certificateCheckSuccessful == TRUE){
			break;
		}else if (result.veclen > 0){
			Ov_SetDynamicVectorLength(&result, 0, STRING);
		}
	}
	ov_string_setvalue(&wherevalues[0], NULL);

	if (certificateCheckSuccessful == FALSE){
		// TODO: Check certificate extern

		// Insert certificate in database
		table  = "SecurityData";
		fields[0] = "ComponentID";
		fields[1] = "Certificate";
		fields[2] = "SecurityKey";
		fieldsValues[0] = NULL;
		ov_string_print(&fieldsValues[0], "'%s'", componentID);
		fieldsValues[1] = NULL;
		ov_string_print(&fieldsValues[1], "'%s'", certificate);
		fieldsValues[2] = "''";
		resultOV = pDBWrapperVTable->m_insertData(table, fields, 3, fieldsValues, 3);
		ov_string_setvalue(&fieldsValues[0], NULL);
		ov_string_setvalue(&fieldsValues[1], NULL);
		if (resultOV != OV_ERR_OK){
			ov_string_setvalue(errorMessage, "Internal Error");
			ov_logfile_error("Could not insert certificate");
			goto FINALIZE;
		}
	}


	// Check if securityKey already exist
	table  = "SecurityData";
	fields[0] = "SecurityKey";
	whereFields[0] = "ComponentID";
	wherevalues[0] = NULL;
	ov_string_print(&wherevalues[0], "'%s'", componentID);
	result.value = NULL;
	result.veclen = 0;
	OV_BOOL securityKeyAlreadyExist = FALSE;
	pDBWrapper = NULL;
	pDBWrapperVTable = NULL;
	for (OV_UINT i = 0; i < pinst->v_DBWrapperUsed.veclen; i++){
		pDBWrapper = Ov_DynamicPtrCast(openAASDiscoveryServer_DBWrapper, ov_path_getobjectpointer(pinst->v_DBWrapperUsed.value[i], 2));
		if (!pDBWrapper){
			ov_string_setvalue(errorMessage, "Internal Error");
			ov_logfile_error("Could not find DBWrapper Object");
			goto FINALIZE;
		}

		Ov_GetVTablePtr(openAASDiscoveryServer_DBWrapper,pDBWrapperVTable, pDBWrapper);
		pDBWrapperVTable->m_selectData(table, fields, 1, whereFields, 1, wherevalues, 1, &result);
		if (result.veclen > 0){
			securityKeyAlreadyExist = TRUE;
			ov_string_setvalue(&securityKey, result.value[0]);// TODO: Handling more than one securityKey
			Ov_SetDynamicVectorLength(&result, 0, STRING);
			break;
		}
	}
	ov_string_setvalue(&wherevalues[0], NULL);

	if(securityKeyAlreadyExist == FALSE){
		// TODO: generate securityKey
		srand(time(NULL));
		OV_UINT i = rand();
		ov_string_print(&securityKey, "AutgenKey%i", i);
		// Insert securityKey in database
		table  = "SecurityData";
		fields[0] = "SecurityKey";
		fieldsValues[0] = NULL;
		ov_string_print(&fieldsValues[0], "'%s'", securityKey);
		whereFields[0] = "ComponentID";
		wherevalues[0] = NULL;
		ov_string_print(&wherevalues[0], "'%s'", componentID);
		resultOV = pDBWrapperVTable->m_updateData(table, fields, 1, fieldsValues, 1, whereFields, 1, wherevalues, 1);
		ov_string_setvalue(&fieldsValues[0], NULL);
		ov_string_setvalue(&wherevalues[0], NULL);
		if (resultOV != OV_ERR_OK){
			ov_string_setvalue(errorMessage, "Internal Error");
			ov_logfile_error("Could not insert SecurityKey");
			goto FINALIZE;
		}
	}

	// get certificate of DS from DB
	OV_BOOL FoundCertificate = FALSE;
	table  = "SecurityData";
	fields[0] = "Certificate";
	whereFields[0] = "ComponentID";
	wherevalues[0] = "'DiscoveryServer'";
	pDBWrapper = NULL;
	pDBWrapperVTable = NULL;;
	for (OV_UINT i = 0; i < pinst->v_DBWrapperUsed.veclen; i++){
		pDBWrapper = Ov_DynamicPtrCast(openAASDiscoveryServer_DBWrapper, ov_path_getobjectpointer(pinst->v_DBWrapperUsed.value[i], 2));
		if (!pDBWrapper)
			break;

		Ov_GetVTablePtr(openAASDiscoveryServer_DBWrapper,pDBWrapperVTable, pDBWrapper);
		pDBWrapperVTable->m_selectData(table, fields, 1, whereFields, 1, wherevalues, 1, &result);
		for (OV_UINT j = 0; j < result.veclen; j++){
			if (result.value[j] != NULL && ov_string_compare(result.value[j], "") != OV_STRCMP_EQUAL){ // TODO: Handling more than one certificate
				ov_string_setvalue(&certificateDS, result.value[0]);
				FoundCertificate = TRUE;
				Ov_SetDynamicVectorLength(&result, 0, STRING);
				break;
			}
		}
	}

	if (FoundCertificate == FALSE){
		ov_string_setvalue(errorMessage, "Internal Error");
		ov_logfile_error("Could not find certificate of DS");
		return OV_ERR_GENERIC;
	}

	ov_string_print(JsonOutput, "\"body\":{\"certificate\":\"%s\", \"securityKey\":\"%s\"}", certificateDS, securityKey);

	FINALIZE:
	ov_string_setvalue(&certificate, NULL);
	ov_string_setvalue(&certificateDS, NULL);
	ov_string_setvalue(&securityKey, NULL);
	ov_string_setvalue(&componentID, NULL);
	Ov_SetDynamicVectorLength(&tags, 0, STRING);
	Ov_SetDynamicVectorLength(&values, 0, STRING);
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS DSServices_DSSecurityServiceType1_getaccess(
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

