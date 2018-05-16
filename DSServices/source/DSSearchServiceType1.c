
/******************************************************************************
*
*   FILE
*   ----
*   DSSearchServiceType1.c
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
#include "service_helper.h"

struct searchtag{
	OV_STRING tag;
	OV_STRING value;
};

struct endpoint{
	OV_STRING protocolType;
	OV_STRING endpointString;
};

struct component{
	OV_STRING componentID;
	struct endpoint* endpoints;
	OV_UINT	  endpointsSize;
};

OV_DLLFNCEXPORT OV_RESULT DSServices_DSSearchServiceType1_executeService(OV_INSTPTR_openAASDiscoveryServer_DSService pinst, const json_data JsonInput, OV_STRING *JsonOutput, OV_STRING *errorMessage) {
    /*    
    *   local variables
    */
	// Parsing Body
	OV_STRING_VEC tags;
	tags.value = NULL;
	tags.veclen = 0;
	OV_STRING_VEC componentIDs;
	componentIDs.value = NULL;
	componentIDs.veclen = 0;
	OV_STRING_VEC endpointStruct;
	endpointStruct.value = NULL;
	endpointStruct.veclen = 0;
	struct component *components = NULL;
	struct searchtag *searchtags = NULL;
	OV_UINT componentSize = 0;
	OV_UINT searchtagsSize = 0;
	Ov_SetDynamicVectorLength(&tags, 3, STRING);
	ov_string_setvalue(&tags.value[0], "componentID");
	ov_string_setvalue(&tags.value[1], "securityKey");
	ov_string_setvalue(&tags.value[2], "tags");
	OV_UINT_VEC tokenIndex;
	tokenIndex.value = NULL;
	tokenIndex.veclen = 0;
	Ov_SetDynamicVectorLength(&tokenIndex, 3, UINT);

	jsonGetTokenIndexByTags(tags, JsonInput, 1, &tokenIndex);

	OV_STRING componentID = NULL;
	jsonGetValueByToken(JsonInput.js, &JsonInput.token[tokenIndex.value[0]+1], &componentID);
	OV_STRING securityKey = NULL;
	jsonGetValueByToken(JsonInput.js, &JsonInput.token[tokenIndex.value[1]+1], &securityKey);

	// check SecurityKey in Database
	OV_RESULT resultOV = checkSecurityKey(pinst->v_DBWrapperUsed, componentID, securityKey);
	if (resultOV){
		ov_string_setvalue(errorMessage, "SecurityKey is not correct");
		goto FINALIZE;
	}

	// get tags
	searchtagsSize = JsonInput.token[tokenIndex.value[2]+1].size;
	searchtags = malloc(sizeof(struct searchtag)*searchtagsSize);
	for (OV_UINT i = 0; i < searchtagsSize; i++){
		searchtags[i].tag = NULL;
		// value + 2 start of objects + i*5 next object + 2/4 values of tag and value
		jsonGetValueByToken(JsonInput.js, &JsonInput.token[tokenIndex.value[2]+2+i*5+2], &searchtags[i].tag);
		searchtags[i].value = NULL;
		jsonGetValueByToken(JsonInput.js, &JsonInput.token[tokenIndex.value[2]+2+i*5+4], &searchtags[i].value);
	}

	// search for tags in Database and get componentID and endpoints
	OV_STRING table  = "tags";
	OV_STRING *tmpFields = NULL;
	tmpFields = malloc(sizeof(OV_STRING));
	tmpFields[0] = "ComponentID";
	OV_STRING *whereFields = NULL;
	OV_STRING *tmpValues = NULL;
	whereFields = malloc(sizeof(OV_STRING)*searchtagsSize*2);
	tmpValues = malloc(sizeof(OV_STRING)*searchtagsSize*2);
	for (OV_UINT i = 0; i < searchtagsSize; i++){
		whereFields[i*2] = "Tag";
		tmpValues[i*2] = NULL;
		ov_string_print(&tmpValues[i*2], "'%s'", searchtags[i].tag);
		whereFields[i*2+1] = "Value";
		tmpValues[i*2+1] = NULL;
		ov_string_print(&tmpValues[i*2+1], "'%s'", searchtags[i].value);
	}
	Ov_SetDynamicVectorLength(&componentIDs, 0, STRING);
	OV_BOOL componentFound = FALSE;
	// Find ComponentID by Tags
	OV_INSTPTR_openAASDiscoveryServer_DBWrapper pDBWrapper = NULL;
	OV_VTBLPTR_openAASDiscoveryServer_DBWrapper pDBWrapperVTable = NULL;
	for (OV_UINT i = 0; i < pinst->v_DBWrapperUsed.veclen; i++){
		pDBWrapper = Ov_DynamicPtrCast(openAASDiscoveryServer_DBWrapper, ov_path_getobjectpointer(pinst->v_DBWrapperUsed.value[i], 2));
		if (!pDBWrapper)
			break;

		Ov_GetVTablePtr(openAASDiscoveryServer_DBWrapper,pDBWrapperVTable, pDBWrapper);
		pDBWrapperVTable->m_selectData(table, tmpFields, 1, whereFields, searchtagsSize*2, tmpValues, searchtagsSize*2, &componentIDs);
		if (componentIDs.veclen > 0){
			componentFound = TRUE;
			componentSize = componentIDs.veclen;
			break;
		}
	}

	if (componentFound == FALSE){
		ov_string_setvalue(errorMessage, "no component found by your tags");
		ov_string_setvalue(JsonOutput, "\"body\":{}");
		goto FINALIZE;
	}
	if (tmpFields)
		free(tmpFields);
	if (whereFields)
		free(whereFields);
	for (OV_UINT i = 0; i < searchtagsSize*2; i++){
		ov_string_setvalue(&tmpValues[i], NULL);
	}
	if (tmpValues)
		free(tmpValues);

	table  = "Endpoints";
	components = malloc(sizeof(struct component)*componentIDs.veclen);
	Ov_SetDynamicVectorLength(&endpointStruct, 0, STRING);
	tmpFields = NULL;
	tmpFields = malloc(sizeof(OV_STRING)*2);
	tmpFields[0] = "ProtocolType";
	tmpFields[1] = "EndpointString";
	for (OV_UINT i = 0; i < componentIDs.veclen; i++){
		components[i].componentID = NULL;
		ov_string_setvalue(&components[i].componentID, componentIDs.value[i]);
		components[i].endpoints = NULL;
		// Find ComponentID by Tags
		whereFields = NULL;
		whereFields = malloc(sizeof(OV_STRING));
		whereFields[0] = "ComponentID";
		tmpValues = NULL;
		tmpValues = malloc(sizeof(OV_STRING));
		tmpValues[0] = NULL;
		ov_string_print(&tmpValues[i], "'%s'", components[i].componentID);
		OV_INSTPTR_openAASDiscoveryServer_DBWrapper pDBWrapper = NULL;
		OV_VTBLPTR_openAASDiscoveryServer_DBWrapper pDBWrapperVTable = NULL;
		components[i].endpointsSize = 0;
		components[i].endpoints = NULL;
		for (OV_UINT i = 0; i < pinst->v_DBWrapperUsed.veclen; i++){
			pDBWrapper = Ov_DynamicPtrCast(openAASDiscoveryServer_DBWrapper, ov_path_getobjectpointer(pinst->v_DBWrapperUsed.value[i], 2));
			if (!pDBWrapper)
				break;

			Ov_GetVTablePtr(openAASDiscoveryServer_DBWrapper,pDBWrapperVTable, pDBWrapper);
			pDBWrapperVTable->m_selectData(table, tmpFields, 2, whereFields, 1, tmpValues, 1, &endpointStruct);
			if (endpointStruct.veclen > 0){
				components[i].endpointsSize = endpointStruct.veclen / 2;
				components[i].endpoints = malloc(sizeof(struct endpoint)*endpointStruct.veclen / 2);
				for (OV_UINT j = 0; j < endpointStruct.veclen/2; j++){
					components[i].endpoints[j].protocolType = NULL;
					ov_string_setvalue(&components[i].endpoints[j].protocolType, endpointStruct.value[j*2]);
					components[i].endpoints[j].endpointString = NULL;
					ov_string_setvalue(&components[i].endpoints[j].endpointString, endpointStruct.value[j*2+1]);
				}
				Ov_SetDynamicVectorLength(&endpointStruct, 0, STRING);
				break;
			}
		}
		ov_string_setvalue(&tmpValues[i], NULL);
		if (whereFields)
			free(whereFields);
		if (tmpValues)
			free(tmpValues);
	}
	if (tmpFields)
		free(tmpFields);

	// Generate Response
	ov_string_setvalue(JsonOutput, "\"body\":{\"components\":[");
	for (OV_UINT i = 0; i < componentSize; i++){
		OV_STRING tmpString = NULL;
		ov_string_print(&tmpString, "{\"componentID\":\"%s\", \"endpoints\":[", components[i].componentID);
		ov_string_append(JsonOutput, tmpString);
		ov_string_setvalue(&tmpString, NULL);
		for (OV_UINT j = 0; j < components[i].endpointsSize; j++){
			tmpString = NULL;
			ov_string_print(&tmpString, "{\"protocolType\":\"%s\", \"endpointString\":\"%s\"}", components[i].endpoints[j].protocolType, components[i].endpoints[j].endpointString);
			ov_string_append(JsonOutput, tmpString);
			ov_string_setvalue(&tmpString, NULL);
		}
		ov_string_append(JsonOutput, "]}");
	}
	ov_string_append(JsonOutput, "]}}");

	FINALIZE:
	Ov_SetDynamicVectorLength(&tags, 0, STRING);
	Ov_SetDynamicVectorLength(&tokenIndex, 0, UINT);
	Ov_SetDynamicVectorLength(&componentIDs, 0, STRING);
	Ov_SetDynamicVectorLength(&endpointStruct, 0, STRING);
	ov_string_setvalue(&componentID, NULL);
	ov_string_setvalue(&securityKey, NULL);

	for (OV_UINT i = 0; i < componentSize; i++){
		ov_string_setvalue(&components[i].componentID, NULL);
		for (OV_UINT j = 0; j < components[i].endpointsSize; j++){
			ov_string_setvalue(&components[i].endpoints[j].protocolType, NULL);
			ov_string_setvalue(&components[i].endpoints[j].endpointString, NULL);
		}
		free(components[i].endpoints);
	}
	if (components)
		free(components);

	for (OV_UINT i = 0; i < searchtagsSize; i++){
		ov_string_setvalue(&searchtags[i].tag, NULL);
		ov_string_setvalue(&searchtags[i].value, NULL);
	}
	if (searchtags)
		free(searchtags);

	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS DSServices_DSSearchServiceType1_getaccess(
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
