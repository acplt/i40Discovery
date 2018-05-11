
/******************************************************************************
*
*   FILE
*   ----
*   TestClient.c
*
*   History
*   -------
*   2018-05-09   File created
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
#include "libov/ov_result.h"
#include "MessageSys_helpers.h"

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_TestClient_SendSecurityMessage_set(
    OV_INSTPTR_openAASDiscoveryServer_TestClient          pobj,
    const OV_BOOL  value
) {

    pobj->v_SendSecurityMessage = value;
    if (pobj->v_SendSecurityMessage == TRUE){
    	ov_string_setvalue(&pobj->v_errorMessage, NULL);
		pobj->v_errorFlag = FALSE;
    	if (pobj->v_state != 1){
        	ov_string_setvalue(&pobj->v_errorMessage, "Client ist not in state 1");
    		pobj->v_errorFlag = TRUE;
    		return OV_ERR_GENERIC;
    	}

    	OV_STRING tmpString = NULL;
		OV_INSTPTR_MessageSys_Message panswerMessage = NULL;

		// Parse endpoint
		OV_STRING *pListExtern = NULL;
		OV_UINT len = 0;
		// endpoint have to be of format IP:MANAGERNAME:PathToKSEndpoint
		pListExtern = ov_string_split(pobj->v_EndpointDS, ":", &len);
		if (len != 3){
			ov_logfile_error("EndpointExtern is not of correct format");
			ov_string_print(&pobj->v_errorMessage, "EndpointExtern is not of correct format");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		OV_STRING *pListIntern = NULL;
		// endpoint have to be of format IP:MANAGERNAME:PathToKSEndpoint
		pListIntern = ov_string_split(pobj->v_EndpointTestClient, ":", &len);
		if (len != 3){
			ov_logfile_error("EndpointIntern is not of correct format");
			ov_string_print(&pobj->v_errorMessage, "EndpointIntern is not of correct format");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		// Create MessageObject in Outbox
		OV_RESULT resultOV = 0;
		ov_string_print(&tmpString, "%i", (pobj->v_messageCount + 1));
		resultOV = Ov_CreateObject(MessageSys_Message, panswerMessage, &pobj->p_ComponentManager.p_OUTBOX, tmpString);
		ov_string_setvalue(&tmpString, NULL);
		if(Ov_Fail(resultOV)){
			ov_logfile_error("Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
			ov_string_print(&pobj->v_errorMessage, "Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}
		pobj->v_messageCount = pobj->v_messageCount + 1;

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

		// Body
		// XML Encoding
		OV_STRING answerBody = NULL;
		ov_string_setvalue(&answerBody, "<bdy>");
		ov_string_print(&tmpString, "{ \"header\":{\"endpointSender\":\"%s\", \"endpointReceiver\":\"%s\", \"messageID\":\"%i\", \"messageType\":\"1\", \"protocolType\":\"1\", \"componentID\":\"%s\"},\"body\":{\"certificate\":\"%s\"}}", pobj->v_EndpointTestClient, pobj->v_EndpointDS, pobj->v_messageCount, pobj->v_ComponentID, pobj->v_CertificateTC);
		ov_string_append(&answerBody, tmpString);
		ov_string_setvalue(&tmpString, NULL);
		ov_string_append(&answerBody, "</bdy>");
		ov_string_setvalue(&panswerMessage->v_msgBody, answerBody);
		ov_string_setvalue(&answerBody, NULL);

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
			ov_string_setvalue(&pobj->v_errorMessage, "Could not find MessageSys");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		// send Message
		if (MessageSys_MsgDelivery_sendMessage(pmsgDelivery, panswerMessage) == FALSE){
			Ov_DeleteObject((OV_INSTPTR_ov_object) panswerMessage);
			ov_logfile_error("Could not send Message");
			ov_string_setvalue(&pobj->v_errorMessage, "Could not send Message");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}
		pobj->v_state = 2;
    }
    pobj->v_SendSecurityMessage = FALSE;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_TestClient_SendRegistrationMessage_set(
    OV_INSTPTR_openAASDiscoveryServer_TestClient          pobj,
    const OV_BOOL  value
) {
    pobj->v_SendRegistrationMessage = value;
    if (pobj->v_SendRegistrationMessage == TRUE && pobj->v_securityKey){
		ov_string_setvalue(&pobj->v_errorMessage, NULL);
		pobj->v_errorFlag = FALSE;
		if (pobj->v_state != 1){
			ov_string_setvalue(&pobj->v_errorMessage, "Client ist not in state 1");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		OV_STRING tmpString = NULL;
		OV_INSTPTR_MessageSys_Message panswerMessage = NULL;

		// Parse endpoint
		OV_STRING *pListExtern = NULL;
		OV_UINT len = 0;
		// endpoint have to be of format IP:MANAGERNAME:PathToKSEndpoint
		pListExtern = ov_string_split(pobj->v_EndpointDS, ":", &len);
		if (len != 3){
			ov_logfile_error("EndpointExtern is not of correct format");
			ov_string_print(&pobj->v_errorMessage, "EndpointExtern is not of correct format");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		OV_STRING *pListIntern = NULL;
		// endpoint have to be of format IP:MANAGERNAME:PathToKSEndpoint
		pListIntern = ov_string_split(pobj->v_EndpointTestClient, ":", &len);
		if (len != 3){
			ov_logfile_error("EndpointIntern is not of correct format");
			ov_string_print(&pobj->v_errorMessage, "EndpointIntern is not of correct format");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		// Create MessageObject in Outbox
		OV_RESULT resultOV = 0;
		ov_string_print(&tmpString, "%i", pobj->v_messageCount + 1);
		resultOV = Ov_CreateObject(MessageSys_Message, panswerMessage, &pobj->p_ComponentManager.p_OUTBOX, tmpString);
		ov_string_setvalue(&tmpString, NULL);
		if(Ov_Fail(resultOV)){
			ov_logfile_error("Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
			ov_string_print(&pobj->v_errorMessage, "Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}
		pobj->v_messageCount = pobj->v_messageCount + 1;

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

		// Body
		// XML Encoding
		OV_STRING answerBody = NULL;
		ov_string_setvalue(&answerBody, "<bdy>");
		ov_string_print(&tmpString, "{ \"header\":{\"endpointSender\":\"%s\", \"endpointReceiver\":\"%s\", \"messageID\":\"%i\", \"messageType\":\"3\", \"protocolType\":\"1\", \"componentID\":\"%s\"},\"body\":{\"securityKey\":\"%s\", %s}}", pobj->v_EndpointTestClient, pobj->v_EndpointDS, pobj->v_messageCount, pobj->v_ComponentID, pobj->v_securityKey, pobj->v_ComponentContent);
		ov_string_append(&answerBody, tmpString);
		ov_string_setvalue(&tmpString, NULL);
		ov_string_append(&answerBody, "</bdy>");
		ov_string_setvalue(&panswerMessage->v_msgBody, answerBody);
		ov_string_setvalue(&answerBody, NULL);

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
			ov_string_setvalue(&pobj->v_errorMessage, "Could not find MessageSys");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		// send Message
		if (MessageSys_MsgDelivery_sendMessage(pmsgDelivery, panswerMessage) == FALSE){
			Ov_DeleteObject((OV_INSTPTR_ov_object) panswerMessage);
			ov_logfile_error("Could not send Message");
			ov_string_setvalue(&pobj->v_errorMessage, "Could not send Message");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}
		pobj->v_state = 3;
	}
	pobj->v_SendRegistrationMessage = FALSE;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_TestClient_SendUnregistrationMessage_set(
    OV_INSTPTR_openAASDiscoveryServer_TestClient          pobj,
    const OV_BOOL  value
) {
    pobj->v_SendUnregistrationMessage = value;
    if (pobj->v_SendUnregistrationMessage == TRUE && pobj->v_securityKey){
   		ov_string_setvalue(&pobj->v_errorMessage, NULL);
   		pobj->v_errorFlag = FALSE;
		if (pobj->v_state != 1){
			ov_string_setvalue(&pobj->v_errorMessage, "Client ist not in state 1");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

   		OV_STRING tmpString = NULL;
   		OV_INSTPTR_MessageSys_Message panswerMessage = NULL;

   		// Parse endpoint
   		OV_STRING *pListExtern = NULL;
   		OV_UINT len = 0;
   		// endpoint have to be of format IP:MANAGERNAME:PathToKSEndpoint
   		pListExtern = ov_string_split(pobj->v_EndpointDS, ":", &len);
   		if (len != 3){
   			ov_logfile_error("EndpointExtern is not of correct format");
   			ov_string_print(&pobj->v_errorMessage, "EndpointExtern is not of correct format");
   			pobj->v_errorFlag = TRUE;
   			return OV_ERR_GENERIC;
   		}

   		OV_STRING *pListIntern = NULL;
   		// endpoint have to be of format IP:MANAGERNAME:PathToKSEndpoint
   		pListIntern = ov_string_split(pobj->v_EndpointTestClient, ":", &len);
   		if (len != 3){
   			ov_logfile_error("EndpointIntern is not of correct format");
   			ov_string_print(&pobj->v_errorMessage, "EndpointIntern is not of correct format");
   			pobj->v_errorFlag = TRUE;
   			return OV_ERR_GENERIC;
   		}

   		// Create MessageObject in Outbox
   		OV_RESULT resultOV = 0;
   		ov_string_print(&tmpString, "%i", pobj->v_messageCount + 1);
   		resultOV = Ov_CreateObject(MessageSys_Message, panswerMessage, &pobj->p_ComponentManager.p_OUTBOX, tmpString);
   		ov_string_setvalue(&tmpString, NULL);
   		if(Ov_Fail(resultOV)){
   			ov_logfile_error("Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
   			ov_string_print(&pobj->v_errorMessage, "Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
   			pobj->v_errorFlag = TRUE;
   			return OV_ERR_GENERIC;
   		}
   		pobj->v_messageCount = pobj->v_messageCount + 1;

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

   		// Body
   		// XML Encoding
   		OV_STRING answerBody = NULL;
   		ov_string_setvalue(&answerBody, "<bdy>");
   		ov_string_print(&tmpString, "{ \"header\":{\"endpointSender\":\"%s\", \"endpointReceiver\":\"%s\", \"messageID\":\"%i\", \"messageType\":\"4\", \"protocolType\":\"1\", \"componentID\":\"%s\"},\"body\":{\"securityKey\":\"%s\"}}", pobj->v_EndpointTestClient, pobj->v_EndpointDS, pobj->v_messageCount, pobj->v_ComponentID, pobj->v_securityKey);
   		ov_string_append(&answerBody, tmpString);
   		ov_string_setvalue(&tmpString, NULL);
   		ov_string_append(&answerBody, "</bdy>");
   		ov_string_setvalue(&panswerMessage->v_msgBody, answerBody);
   		ov_string_setvalue(&answerBody, NULL);

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
   			ov_string_setvalue(&pobj->v_errorMessage, "Could not find MessageSys");
   			pobj->v_errorFlag = TRUE;
   			return OV_ERR_GENERIC;
   		}

   		// send Message
   		if (MessageSys_MsgDelivery_sendMessage(pmsgDelivery, panswerMessage) == FALSE){
   			Ov_DeleteObject((OV_INSTPTR_ov_object) panswerMessage);
   			ov_logfile_error("Could not send Message");
   			ov_string_setvalue(&pobj->v_errorMessage, "Could not send Message");
   			pobj->v_errorFlag = TRUE;
   			return OV_ERR_GENERIC;
   		}
   		pobj->v_state = 4;
   	}
   	pobj->v_SendUnregistrationMessage = FALSE;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_TestClient_SendSearchMessage_set(
    OV_INSTPTR_openAASDiscoveryServer_TestClient          pobj,
    const OV_BOOL  value
) {
    pobj->v_SendSearchMessage = value;
    if (pobj->v_SendSearchMessage == TRUE && pobj->v_securityKey){
		ov_string_setvalue(&pobj->v_errorMessage, NULL);
		pobj->v_errorFlag = FALSE;
		if (pobj->v_state != 1){
			ov_string_setvalue(&pobj->v_errorMessage, "Client ist not in state 1");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		OV_STRING tmpString = NULL;
		OV_INSTPTR_MessageSys_Message panswerMessage = NULL;

		// Parse endpoint
		OV_STRING *pListExtern = NULL;
		OV_UINT len = 0;
		// endpoint have to be of format IP:MANAGERNAME:PathToKSEndpoint
		pListExtern = ov_string_split(pobj->v_EndpointDS, ":", &len);
		if (len != 3){
			ov_logfile_error("EndpointExtern is not of correct format");
			ov_string_print(&pobj->v_errorMessage, "EndpointExtern is not of correct format");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		OV_STRING *pListIntern = NULL;
		// endpoint have to be of format IP:MANAGERNAME:PathToKSEndpoint
		pListIntern = ov_string_split(pobj->v_EndpointTestClient, ":", &len);
		if (len != 3){
			ov_logfile_error("EndpointIntern is not of correct format");
			ov_string_print(&pobj->v_errorMessage, "EndpointIntern is not of correct format");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		// Create MessageObject in Outbox
		OV_RESULT resultOV = 0;
		ov_string_print(&tmpString, "%i", pobj->v_messageCount + 1);
		resultOV = Ov_CreateObject(MessageSys_Message, panswerMessage, &pobj->p_ComponentManager.p_OUTBOX, tmpString);
		ov_string_setvalue(&tmpString, NULL);
		if(Ov_Fail(resultOV)){
			ov_logfile_error("Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
			ov_string_print(&pobj->v_errorMessage, "Could not create an answerMessage. Reason: %s", ov_result_getresulttext(resultOV));
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}
		pobj->v_messageCount = pobj->v_messageCount + 1;

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

		// Body
		// XML Encoding
		OV_STRING answerBody = NULL;
		ov_string_setvalue(&answerBody, "<bdy>");
		ov_string_print(&tmpString, "{ \"header\":{\"endpointSender\":\"%s\", \"endpointReceiver\":\"%s\", \"messageID\":\"%i\", \"messageType\":\"7\", \"protocolType\":\"1\", \"componentID\":\"%s\"},\"body\":{\"securityKey\":\"%s\", \"tags\":[%s]}}", pobj->v_EndpointTestClient, pobj->v_EndpointDS, pobj->v_messageCount, pobj->v_ComponentID, pobj->v_securityKey, pobj->v_Tags);
		ov_string_append(&answerBody, tmpString);
		ov_string_setvalue(&tmpString, NULL);
		ov_string_append(&answerBody, "</bdy>");
		ov_string_setvalue(&panswerMessage->v_msgBody, answerBody);
		ov_string_setvalue(&answerBody, NULL);

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
			ov_string_setvalue(&pobj->v_errorMessage, "Could not find MessageSys");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}

		// send Message
		if (MessageSys_MsgDelivery_sendMessage(pmsgDelivery, panswerMessage) == FALSE){
			Ov_DeleteObject((OV_INSTPTR_ov_object) panswerMessage);
			ov_logfile_error("Could not send Message");
			ov_string_setvalue(&pobj->v_errorMessage, "Could not send Message");
			pobj->v_errorFlag = TRUE;
			return OV_ERR_GENERIC;
		}
		pobj->v_state = 5;
	}
	pobj->v_SendSearchMessage = FALSE;
    return OV_ERR_OK;
}

OV_DLLFNCEXPORT OV_ACCESS openAASDiscoveryServer_TestClient_getaccess(
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

OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_TestClient_prepairForNextMessage_set(
    OV_INSTPTR_openAASDiscoveryServer_TestClient          pobj,
    const OV_BOOL  value
) {
    pobj->v_prepairForNextMessage = value;
    if (pobj->v_prepairForNextMessage == TRUE && pobj->v_state == 6){
    	pobj->v_state = 1;
    }
    pobj->v_prepairForNextMessage = FALSE;
    return OV_ERR_OK;
}


OV_DLLFNCEXPORT OV_RESULT openAASDiscoveryServer_TestClient_reset_set(
    OV_INSTPTR_openAASDiscoveryServer_TestClient          pobj,
    const OV_BOOL  value
) {
    pobj->v_reset = value;
    if (pobj->v_reset == TRUE){
    	pobj->v_state = 0;
    }
    pobj->v_reset = FALSE;
    return OV_ERR_OK;
}



OV_DLLFNCEXPORT void openAASDiscoveryServer_TestClient_typemethod(
	OV_INSTPTR_fb_functionblock	pfb,
	OV_TIME						*pltc
) {
    /*
    *   local variables
    */
    OV_INSTPTR_openAASDiscoveryServer_TestClient pinst = Ov_StaticPtrCast(openAASDiscoveryServer_TestClient, pfb);

    switch (pinst->v_state){
    	case 0: // Initializing
    		ov_string_setvalue(&pinst->v_securityKey, NULL);
    		pinst->v_errorFlag = FALSE;
    		ov_string_setvalue(&pinst->v_errorMessage, NULL);
    		ov_string_setvalue(&pinst->v_certificateDS, NULL);
    		pinst->v_state = 1;
		break;
    	case 1: // ReadyForSendingRequest
    		// DoNothing
		break;
    	case 2: // WaitingForSecurityResponse
    		// DoNothing
		break;
    	case 3: // WaitingForRegistrationResponse
			// DoNothing
		break;
    	case 4: // WaitingForUnregistrationResponse
			// DoNothing
		break;
    	case 5: // WaitingForSearchResponse
			// DoNothing
		break;
    	case 6: // ProcessedResponse
    		// DoNothing
		break;
    	case 7: // Error
    		// DoNothing
		break;
    	default:
		break;
    }

    return;
}

