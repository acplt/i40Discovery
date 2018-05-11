
/******************************************************************************
*
*   FILE
*   ----
*   DiscoveryServer.c
*
*   History
*   -------
*   2018-04-23   File created
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
#include <pthread.h>
#include "MessageSys_helpers.h"
#include "libov/ov_logfile.h"
#include "libov/ov_result.h"
#include "libov/ov_path.h"
#include "json_helper.h"

#if OV_SYSTEM_NT
	#include <windows.h>
#endif

#define MUTEX_LOCK(MUTEX)\
		pthread_mutex_lock(MUTEX);\

#define MUTEX_UNLOCK(MUTEX)\
		pthread_mutex_unlock(MUTEX);\

typedef struct thread_data{
	pthread_mutex_t mutex;
	pthread_t thread;
	OV_STRING message;
	OV_INSTPTR_openAASDiscoveryServer_DiscoveryServer pDiscoveryServer;
}thread_data;

/* thread function */
static void* thread_fcn(void*ptr){
	thread_data* pthreadData = ptr;

	OV_VTBLPTR_openAASDiscoveryServer_Registration pvtableRegistration = NULL;
	OV_VTBLPTR_openAASDiscoveryServer_Security pvtableSecurity = NULL;
	OV_VTBLPTR_openAASDiscoveryServer_Search pvtableSearch = NULL;

	OV_STRING JsonOutput = NULL;
	OV_STRING errorMessage = NULL;
	OV_RESULT resultOV = 0;
	request_data requestData;
	request_data_init(&requestData);

	resultOV = jsonRequestParse(&requestData, pthreadData->message);
	ov_string_setvalue(&pthreadData->message, NULL);

	switch(requestData.header.messageType){
		case 1: // SecurityMessage
			Ov_GetVTablePtr(openAASDiscoveryServer_Security, pvtableSecurity, &pthreadData->pDiscoveryServer->p_Security);
			if (pvtableSecurity)
				resultOV = pvtableSecurity->m_getSecurityMessage(Ov_DynamicPtrCast(openAASDiscoveryServer_Part, &pthreadData->pDiscoveryServer->p_Security), requestData.body, &JsonOutput, &errorMessage);
			else
				ov_logfile_error("Could not get VTable Pointer of Security-Object");
		break;
		case 2: // RegistrationMessage
			Ov_GetVTablePtr(openAASDiscoveryServer_Registration, pvtableRegistration, &pthreadData->pDiscoveryServer->p_Registration);
			if (pvtableRegistration)
				resultOV = pvtableRegistration->m_getRegistrationMessage(Ov_DynamicPtrCast(openAASDiscoveryServer_Part, &pthreadData->pDiscoveryServer->p_Registration), requestData.body, &JsonOutput, &errorMessage);
			else
				ov_logfile_error("Could not get VTable Pointer of Registration-Object");
		break;
		case 3: // UnregistrationMessage
			Ov_GetVTablePtr(openAASDiscoveryServer_Registration, pvtableRegistration, &pthreadData->pDiscoveryServer->p_Registration);
			if (pvtableRegistration)
				resultOV = pvtableRegistration->m_getUnregistrationMessage(Ov_DynamicPtrCast(openAASDiscoveryServer_Part, &pthreadData->pDiscoveryServer->p_Registration), requestData.body, &JsonOutput, &errorMessage);
			else
				ov_logfile_error("Could not get VTable Pointer of pvtableRegistration-Object");
		break;
		case 4: // SearchMessage
			Ov_GetVTablePtr(openAASDiscoveryServer_Search, pvtableSearch, &pthreadData->pDiscoveryServer->p_Search);
			if (pvtableSearch)
				resultOV = pvtableSearch->m_getSearchMessage(Ov_DynamicPtrCast(openAASDiscoveryServer_Part, &pthreadData->pDiscoveryServer->p_Search), requestData.body, &JsonOutput, &errorMessage);
			else
				ov_logfile_error("Could not get VTable Pointer of Search-Object");
		break;
		default:
		break;
	}



	// freeMemory and delete thread from list
	for (OV_UINT i = 0; i < pthreadData->pDiscoveryServer->v_threadDataHndl.veclen; i++){
		if ((OV_UINT)pthreadData == pthreadData->pDiscoveryServer->v_threadDataHndl.value[i]){
			pthreadData->pDiscoveryServer->v_threadDataHndl.value[i] = 0;
			// Copy each value to the index before
			for (OV_UINT j = i; j < pthreadData->pDiscoveryServer->v_threadDataHndl.veclen-1; j++){
				pthreadData->pDiscoveryServer->v_threadDataHndl.value[j] = pthreadData->pDiscoveryServer->v_threadDataHndl.value[j+1];
			}
			Ov_SetDynamicVectorLength(&pthreadData->pDiscoveryServer->v_threadDataHndl, pthreadData->pDiscoveryServer->v_threadDataHndl.veclen-1, INT);
		}
	}

	// create response-message
	response_header responseHeader;
	responseHeader.endpointReceiver = requestData.header.endpointReceiver;
	responseHeader.endpointSender = requestData.header.endpointSender;
	// Check ErrorMessage
	if (resultOV){
		ov_logfile_error("Error in part-function: %s", errorMessage);
		responseHeader.errorFlag = TRUE;
		responseHeader.errorMessage = errorMessage;
	}else{
		responseHeader.errorFlag = FALSE;
		responseHeader.errorMessage = NULL;
	}
	// responseHeader.messageID = ???
	responseHeader.referToMessageID = requestData.header.messageID;
	responseHeader.messageType = requestData.header.messageType + 1;
	pthreadData->pDiscoveryServer->v_messageCount = pthreadData->pDiscoveryServer->v_messageCount + 1;
	ov_string_print(&responseHeader.messageID, "&i", pthreadData->pDiscoveryServer->v_messageCount);

	// Send Response
	ov_string_setvalue(&errorMessage, NULL);
	resultOV = openAASDiscoveryServer_DiscoveryServer_sendMessage(pthreadData->pDiscoveryServer, JsonOutput, &errorMessage, responseHeader, requestData.header.protocolType);
	if (resultOV){
		ov_logfile_error("Error in sendMessage: %s", errorMessage);
		ov_string_setvalue(&errorMessage, NULL);
	}

	// freeMemory
	request_data_deleteMembers(&requestData);
	ov_string_setvalue(&responseHeader.messageID, NULL);
	ov_string_setvalue(&JsonOutput, NULL);
	Ov_HeapFree(pthreadData);

	pthread_exit(0);
	return 0;
}

OV_DLLFNCEXPORT OV_ACCESS openAASDiscoveryServer_DiscoveryServer_getaccess(
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

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DiscoveryServer_getMessage(OV_INSTPTR_openAASDiscoveryServer_DiscoveryServer pinst, const OV_STRING JsonInput, OV_STRING *errorMessage) {

	thread_data *pthreadData = NULL;
	pthreadData = Ov_HeapMalloc(sizeof(thread_data));
	if(!pthreadData){
		return OV_ERR_GENERIC;
	}
	pthreadData->thread = 0;
	pthreadData->pDiscoveryServer = pinst;
	ov_string_setvalue(&pthreadData->message, JsonInput);

	OV_UINT threadResult = 0;
	Ov_SetDynamicVectorLength(&pinst->v_threadDataHndl, pinst->v_threadDataHndl.veclen + 1, INT);
	pinst->v_threadDataHndl.value[pinst->v_threadDataHndl.veclen-1] = (OV_UINT) pthreadData;
	threadResult = pthread_create(&pthreadData->thread, NULL, thread_fcn, (void*) pthreadData);

	if (threadResult){
		ov_logfile_error("Could not create a thread for getting Message. ErrorCode: %i", threadResult);
		ov_string_print(errorMessage, "Could not create a thread for getting Message. ErrorCode: %i", threadResult);
		Ov_SetDynamicVectorLength(&pinst->v_threadDataHndl, pinst->v_threadDataHndl.veclen-1, INT);
		ov_string_setvalue(&pthreadData->message, NULL);
		Ov_HeapFree(pthreadData);
		return OV_ERR_GENERIC;
	}

	return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DiscoveryServer_sendMessage(OV_INSTPTR_openAASDiscoveryServer_DiscoveryServer pinst, const OV_STRING JsonInput, OV_STRING *errorMessage, const response_header responseHeader, OV_UINT protocolType) {
	OV_INSTPTR_MessageSys_Message panswerMessage = NULL;
	OV_RESULT resultOV = 0;
	if (!JsonInput){
		ov_string_print(errorMessage, "empty JSON-String");
		return OV_ERR_GENERIC;
	}

	switch (protocolType){
		case 1: { // MessageSys
			// Parse endpoint
			OV_STRING *pListExtern = NULL;
			OV_UINT len = 0;
			// endpoint of old sender have to be of format IP:MANAGERNAME:PathToKSEndpoint
			pListExtern = ov_string_split(responseHeader.endpointSender, ":", &len);
			if (len != 3){
				ov_logfile_error("Endpoint of sender is not of correct format");
				ov_string_print(errorMessage, "Endpoint of sender is not of correct format");
				return OV_ERR_GENERIC;
			}

			OV_STRING *pListIntern = NULL;
			// endpoint have to be of format IP:MANAGERNAME:PathToKSEndpoint
			pListIntern = ov_string_split(responseHeader.endpointReceiver, ":", &len);
			if (len != 3){
				ov_logfile_error("Endpoint of receiver is not of correct format");
				ov_string_print(errorMessage, "Endpoint of receiver is not of correct format");
				return OV_ERR_GENERIC;
			}

			// Create MessageObject in Outbox
			resultOV = Ov_CreateObject(MessageSys_Message, panswerMessage, &pinst->p_ComponentManager.p_OUTBOX, responseHeader.messageID);
			if(Ov_Fail(resultOV)){
				ov_logfile_error("Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
				ov_string_print(errorMessage, "Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
				return OV_ERR_GENERIC;
			}

			// Sender = Endpoint of Discovery-Server (IP, MANAGER-Name, Path)
			MessageSys_Message_senderAddress_set(panswerMessage, pListIntern[0]);
			MessageSys_Message_senderName_set(panswerMessage, pListIntern[1]);
			MessageSys_Message_senderComponent_set(panswerMessage, pListIntern[2]);
			ov_string_freelist(pListIntern);

			// Receiver = Sender of old message
			MessageSys_Message_receiverAddress_set(panswerMessage, pListExtern[0]);
			MessageSys_Message_receiverName_set(panswerMessage, pListExtern[1]);
			MessageSys_Message_receiverComponent_set(panswerMessage, pListExtern[2]);
			ov_string_freelist(pListExtern);

			ov_string_setvalue(&panswerMessage->v_refMsgID, responseHeader.referToMessageID);

			// generate JSON-Header
			OV_STRING jsonHeader = NULL;
			ov_string_print(&jsonHeader, "\"header\":{\"endpointSender\":\"%s\",\"endpointReceiver\":\"%s\",\"messageID\":\"%s\",\"referToMessageID\":\"%s\",\"messageType\":\"%i\",\"errorFlag\":\"%s\",\"errorMessage\":\"%s\"}", responseHeader.endpointSender, responseHeader.endpointReceiver, responseHeader.messageID, responseHeader.referToMessageID, responseHeader.messageType, responseHeader.errorFlag == TRUE ? "true" : "false", responseHeader.errorMessage);

			// Body
			// XML Encoding
			OV_STRING answerBody = NULL;
			ov_string_setvalue(&answerBody, "<bdy>");
			ov_string_append(&answerBody, "{");
			ov_string_append(&answerBody, jsonHeader);
			ov_string_append(&answerBody, ",");
			ov_string_append(&answerBody, JsonInput);
			ov_string_append(&answerBody, "}");
			ov_string_append(&answerBody, "</bdy>");
			ov_string_setvalue(&panswerMessage->v_msgBody, answerBody);
			ov_string_setvalue(&answerBody, NULL);
			ov_string_setvalue(&jsonHeader, NULL);

			// Message ready for sending
			panswerMessage->v_msgStatus = MSGREADYFORSENDING;

			// Search for MsgDelivery object
			OV_INSTPTR_MessageSys_MsgDelivery pmsgDelivery = NULL;
			Ov_ForEachChildEx(ov_instantiation, pclass_MessageSys_MsgDelivery, pmsgDelivery, MessageSys_MsgDelivery){
				if(ov_string_compare(pmsgDelivery->v_identifier, "MessageSys") == OV_STRCMP_EQUAL){
					break;
				}
			}
			if (!pmsgDelivery){
				Ov_DeleteObject((OV_INSTPTR_ov_object) panswerMessage);
				ov_logfile_error("Could not find MessageSys");
				ov_string_setvalue(errorMessage, "Could not find MessageSys");
				return OV_ERR_GENERIC;
			}

			// send Message
			if (MessageSys_MsgDelivery_sendMessage(pmsgDelivery, panswerMessage) == FALSE){
				Ov_DeleteObject((OV_INSTPTR_ov_object) panswerMessage);
				ov_logfile_error("Could not send Message");
				ov_string_setvalue(errorMessage, "Could not send Message");
				return OV_ERR_GENERIC;
			}
		}
		break;
		case 2: // OPC UA
		break;
		case 3: // KS http
		break;
	}

    return OV_ERR_OK;
}



OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_DiscoveryServer_constructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*
    *   local variables
    */
    //OV_INSTPTR_openAASDiscoveryServer_DiscoveryServer pinst = Ov_StaticPtrCast(openAASDiscoveryServer_DiscoveryServer, pobj);
    OV_RESULT    result;

    /* do what the base class does first */
    result = ov_object_constructor(pobj);
    if(Ov_Fail(result))
         return result;

    /* do what */


    return OV_ERR_OK;
}

OV_DLLFNCEXPORT void openAASDiscoveryServer_DiscoveryServer_destructor(
	OV_INSTPTR_ov_object 	pobj
) {
    /*
    *   local variables
    */
    OV_INSTPTR_openAASDiscoveryServer_DiscoveryServer pinst = Ov_StaticPtrCast(openAASDiscoveryServer_DiscoveryServer, pobj);

    /* do what */
    for (OV_UINT i = 0; i < pinst->v_threadDataHndl.veclen; i++){
		thread_data * pthreadData = (thread_data *) pinst->v_threadDataHndl.value[i];
		pthread_cancel(pthreadData->thread);
		pthread_join(pthreadData->thread,NULL);
		ov_string_setvalue(&pthreadData->message, NULL);
		Ov_HeapFree(pthreadData);
		pinst->v_threadDataHndl.value[i] = 0;
    }
    Ov_SetDynamicVectorLength(&pinst->v_threadDataHndl, 0, INT);

    /* destroy object */
    ov_object_destructor(pobj);

    return;
}

