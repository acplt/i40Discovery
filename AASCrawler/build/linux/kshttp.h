/*
*   This file was generated by the ACPLT/OV C-Code Generator.
*
*   C-Code Generator version: 1.6.4
*   ACPLT/OV library version: 2.0.0
*   Date of file generation:  24-Oct-2018 (13:55:12)
*
*   DO NOT EDIT THIS FILE!
*/

#ifndef OV_LIBRARY_kshttp_H_INCLUDED
#define OV_LIBRARY_kshttp_H_INCLUDED

#include "libov/ov_library.h"
#include "libov/ov_structure.h"
#include "libov/ov_class.h"
#include "libov/ov_association.h"
#include "libov/ov_variable.h"
#include "libov/ov_part.h"
#include "libov/ov_operation.h"
#include "ov.h"
#include "ksbase.h"

#include "kshttp.ovt"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef OV_COMPILE_LIBRARY_kshttp
#if OV_COMPILER_BORLAND
#define OV_VAREXTERN extern
#else
#define OV_VAREXTERN OV_DLLVAREXPORT
#endif
#define OV_FNCEXTERN OV_DLLFNCEXPORT
#else
#define OV_VAREXTERN OV_DLLVARIMPORT
#define OV_FNCEXTERN OV_DLLVARIMPORT
#endif

#define OV_BIPT_kshttp_httpIdentificator OV_INSTPTR_ksbase_ProtocolIdentificator
#define OV_BVPT_kshttp_httpIdentificator OV_VTBLPTR_ksbase_ProtocolIdentificator

#define OV_INSTBODY_kshttp_httpIdentificator \
    OV_INSTBODY_ksbase_ProtocolIdentificator \
    OV_STRING_VEC v_AllowedMethods;

#define OV_CIB_kshttp_httpIdentificator \
    OV_CIB_ksbase_ProtocolIdentificator \
    int is_of_class_kshttp_httpIdentificator:1;

#define OV_STATICINSTBODY_kshttp_httpIdentificator

#define OV_BIPT_kshttp_httpclienthandler OV_INSTPTR_ksbase_ClientHandler
#define OV_BVPT_kshttp_httpclienthandler OV_VTBLPTR_ksbase_ClientHandler

#define OV_INSTBODY_kshttp_httpclienthandler \
    OV_INSTBODY_ksbase_ClientHandler \
    HTTP_REQUEST v_ClientRequest; \
    HTTP_RESPONSE v_ServerResponse; \
    HTTP_COMMUNICATIONSTATUS v_CommunicationStatus;

#define OV_CIB_kshttp_httpclienthandler \
    OV_CIB_ksbase_ClientHandler \
    int is_of_class_kshttp_httpclienthandler:1;

#define OV_STATICINSTBODY_kshttp_httpclienthandler

#define OV_BIPT_kshttp_getvarpushhandler OV_INSTPTR_ksbase_ClientHandler
#define OV_BVPT_kshttp_getvarpushhandler OV_VTBLPTR_ksbase_ClientHandler

#define OV_INSTBODY_kshttp_getvarpushhandler \
    OV_INSTBODY_ksbase_ClientHandler \
    OV_INT v_responseformat; \
    OV_STRING_VEC v_urlQuery; \
    OV_STRING v_responseSent;

#define OV_CIB_kshttp_getvarpushhandler \
    OV_CIB_ksbase_ClientHandler \
    int is_of_class_kshttp_getvarpushhandler:1;

#define OV_STATICINSTBODY_kshttp_getvarpushhandler

#define OV_BIPT_kshttp_httpClientHandlerExtension OV_INSTPTR_ksbase_baseClientHandlerExtension
#define OV_BVPT_kshttp_httpClientHandlerExtension OV_VTBLPTR_ksbase_baseClientHandlerExtension

#define OV_INSTBODY_kshttp_httpClientHandlerExtension \
    OV_INSTBODY_ksbase_baseClientHandlerExtension \
    OV_STRING_VEC v_commandList;

#define OV_CIB_kshttp_httpClientHandlerExtension \
    OV_CIB_ksbase_baseClientHandlerExtension \
    int is_of_class_kshttp_httpClientHandlerExtension:1;

#define OV_STATICINSTBODY_kshttp_httpClientHandlerExtension

#define OV_BIPT_kshttp_httpSimpleTicketAuthenticator OV_INSTPTR_ksbase_TicketAuthenticator
#define OV_BVPT_kshttp_httpSimpleTicketAuthenticator OV_VTBLPTR_ksbase_TicketAuthenticator

#define OV_INSTBODY_kshttp_httpSimpleTicketAuthenticator \
    OV_INSTBODY_ksbase_TicketAuthenticator

#define OV_CIB_kshttp_httpSimpleTicketAuthenticator \
    OV_CIB_ksbase_TicketAuthenticator \
    int is_of_class_kshttp_httpSimpleTicketAuthenticator:1;

#define OV_STATICINSTBODY_kshttp_httpSimpleTicketAuthenticator

#define OV_BIPT_kshttp_httpManagerCom OV_INSTPTR_ksbase_ComTask
#define OV_BVPT_kshttp_httpManagerCom OV_VTBLPTR_ksbase_ComTask

#define OV_INSTBODY_kshttp_httpManagerCom \
    OV_INSTBODY_ksbase_ComTask \
    OV_STRING v_ManagerPort; \
    OV_STRING v_OwnPort; \
    OV_BOOL v_UseShortCut; \
    OV_UINT v_RegisterState; \
    OV_UINT v_Tries;

#define OV_CIB_kshttp_httpManagerCom \
    OV_CIB_ksbase_ComTask \
    int is_of_class_kshttp_httpManagerCom:1;

#define OV_STATICINSTBODY_kshttp_httpManagerCom

#define OV_BIPT_kshttp_httpClientBase OV_INSTPTR_ksbase_ClientBase
#define OV_BVPT_kshttp_httpClientBase OV_VTBLPTR_ksbase_ClientBase

#define OV_INSTBODY_kshttp_httpClientBase \
    OV_INSTBODY_ksbase_ClientBase \
    OV_UINT v_httpParseStatus; \
    OV_UINT v_httpStatusCode; \
    KSBASE_CALLBACKSTRUCT v_tempCallback; \
    HTTP_RESPONSE v_ServerResponse;

#define OV_CIB_kshttp_httpClientBase \
    OV_CIB_ksbase_ClientBase \
    int is_of_class_kshttp_httpClientBase:1;

#define OV_STATICINSTBODY_kshttp_httpClientBase

#define OV_BIPT_kshttp_httpClient OV_INSTPTR_kshttp_httpClientBase
#define OV_BVPT_kshttp_httpClient OV_VTBLPTR_kshttp_httpClientBase

#define OV_INSTBODY_kshttp_httpClient \
    OV_INSTBODY_kshttp_httpClientBase \
    OV_STRING v_ManagerPort;

#define OV_CIB_kshttp_httpClient \
    OV_CIB_kshttp_httpClientBase \
    int is_of_class_kshttp_httpClient:1;

#define OV_STATICINSTBODY_kshttp_httpClient

#define OV_BIPT_kshttp_genericHttpClient OV_INSTPTR_kshttp_httpClientBase
#define OV_BVPT_kshttp_genericHttpClient OV_VTBLPTR_kshttp_httpClientBase

#define OV_INSTBODY_kshttp_genericHttpClient \
    OV_INSTBODY_kshttp_httpClientBase \
    OV_BOOL v_beginCommunication; \
    OV_STRING v_URI; \
    OV_STRING v_messageBody; \
    OV_UINT v_contentLength; \
    OV_STRING v_contentType;

#define OV_CIB_kshttp_genericHttpClient \
    OV_CIB_kshttp_httpClientBase \
    int is_of_class_kshttp_genericHttpClient:1;

#define OV_STATICINSTBODY_kshttp_genericHttpClient

#define OV_BIPT_kshttp_authenticatedsession OV_INSTPTR_ov_object
#define OV_BVPT_kshttp_authenticatedsession OV_VTBLPTR_ov_object

#define OV_INSTBODY_kshttp_authenticatedsession \
    OV_INSTBODY_ov_object \
    OV_STRING v_nonce; \
    OV_INT v_securitylevel; \
    OV_TIME v_lastactivity; \
    OV_INT v_uncheckedaccess;

#define OV_CIB_kshttp_authenticatedsession \
    OV_CIB_ov_object \
    int is_of_class_kshttp_authenticatedsession:1;

#define OV_STATICINSTBODY_kshttp_authenticatedsession

#define OV_BIPT_kshttp_staticfile OV_INSTPTR_ov_object
#define OV_BVPT_kshttp_staticfile OV_VTBLPTR_ov_object

#define OV_INSTBODY_kshttp_staticfile \
    OV_INSTBODY_ov_object \
    OV_STRING v_content; \
    OV_STRING v_mimetype; \
    OV_STRING v_encoding;

#define OV_CIB_kshttp_staticfile \
    OV_CIB_ov_object \
    int is_of_class_kshttp_staticfile:1;

#define OV_STATICINSTBODY_kshttp_staticfile

OV_TYPEDEF_INSTANCE(kshttp_httpIdentificator);
OV_TYPEDEF_INSTANCE(kshttp_httpclienthandler);
OV_TYPEDEF_INSTANCE(kshttp_getvarpushhandler);
OV_TYPEDEF_INSTANCE(kshttp_httpClientHandlerExtension);
OV_TYPEDEF_INSTANCE(kshttp_httpSimpleTicketAuthenticator);
OV_TYPEDEF_INSTANCE(kshttp_httpManagerCom);
OV_TYPEDEF_INSTANCE(kshttp_httpClientBase);
OV_TYPEDEF_INSTANCE(kshttp_httpClient);
OV_TYPEDEF_INSTANCE(kshttp_genericHttpClient);
OV_TYPEDEF_INSTANCE(kshttp_authenticatedsession);
OV_TYPEDEF_INSTANCE(kshttp_staticfile);

#include "kshttp.ovf"

OV_FNCEXTERN OV_FNC_CONSTRUCTOR kshttp_httpIdentificator_constructor;
OV_FNCEXTERN KSBASE_FNC_IDENTIFY kshttp_httpIdentificator_identify;
OV_FNCEXTERN KSBASE_FNC_CREATECH kshttp_httpIdentificator_createClientHandler;

OV_FNCEXTERN KSBASE_FNC_HANDLEREQUEST kshttp_httpclienthandler_HandleRequest;
OV_FNCEXTERN OV_FNC_STARTUP kshttp_httpclienthandler_startup;
OV_FNCEXTERN OV_FNC_SHUTDOWN kshttp_httpclienthandler_shutdown;
OV_FNCEXTERN KSHTTP_FNC_INDATAHANDLING kshttp_httpclienthandler_analyzeRequestHeader;
OV_FNCEXTERN KSHTTP_FNC_INDATAHANDLING kshttp_httpclienthandler_analyzeRequestBody;
OV_FNCEXTERN KSHTTP_FNC_GENERATEKSBODY kshttp_httpclienthandler_generateHttpBody;
OV_FNCEXTERN KSHTTP_FNC_GENERATEHEADER kshttp_httpclienthandler_generateHttpHeader;
OV_FNCEXTERN KSHTTP_FNC_RESULT2HTTP kshttp_httpclienthandler_mapresult2http;
OV_FNCEXTERN KSHTTP_FNC_OUTPACKETHANDLING kshttp_httpclienthandler_sendHttpHeader;
OV_FNCEXTERN KSHTTP_FNC_OUTPACKETHANDLING kshttp_httpclienthandler_sendHttpBody;

OV_FNCEXTERN KSBASE_FNC_HANDLEREQUEST kshttp_getvarpushhandler_HandleRequest;
OV_FNCEXTERN KSBASE_FNC_TYPEMETHOD kshttp_getvarpushhandler_typemethod;

OV_FNCEXTERN KSHTTP_FNC_HANDLEEXTREQUEST kshttp_httpClientHandlerExtension_HandleExtendedRequest;
OV_FNCEXTERN KSHTTP_FNC_CHECKCOMMAND kshttp_httpClientHandlerExtension_CheckCommand;
OV_FNCEXTERN KSBASE_FNC_HANDLEREQUEST kshttp_httpClientHandlerExtension_HandleRequest;

OV_FNCEXTERN OV_FNC_CONSTRUCTOR kshttp_httpSimpleTicketAuthenticator_constructor;
OV_FNCEXTERN OV_FNC_STARTUP kshttp_httpSimpleTicketAuthenticator_startup;
OV_FNCEXTERN OV_FNC_SHUTDOWN kshttp_httpSimpleTicketAuthenticator_shutdown;
OV_FNCEXTERN KSBASE_FNC_CREATETICKET kshttp_httpSimpleTicketAuthenticator_createticket;
OV_FNCEXTERN KSBASE_FNC_DELETETICKET kshttp_httpSimpleTicketAuthenticator_deleteticket;
OV_FNCEXTERN KSBASE_FNC_ENCODEREPLY kshttp_httpSimpleTicketAuthenticator_encodereply;
OV_FNCEXTERN KSBASE_FNC_GETACCESS kshttp_httpSimpleTicketAuthenticator_TicketGetaccess;

OV_FNCEXTERN OV_FNC_STARTUP kshttp_httpManagerCom_startup;
OV_FNCEXTERN OV_FNC_SHUTDOWN kshttp_httpManagerCom_shutdown;
OV_FNCEXTERN KSBASE_FNC_TYPEMETHOD kshttp_httpManagerCom_typemethod;

OV_FNCEXTERN KSBASE_FNC_RESET kshttp_httpClientBase_reset;
OV_FNCEXTERN KSBASE_FNC_TYPEMETHOD kshttp_httpClientBase_typemethod;
OV_FNCEXTERN KSBASE_FNC_HANDLEDATA kshttp_httpClientBase_HandleData;
OV_FNCEXTERN OV_FNC_STARTUP kshttp_httpClientBase_startup;
OV_FNCEXTERN OV_FNC_SHUTDOWN kshttp_httpClientBase_shutdown;

OV_FNCEXTERN KSBASE_FNC_REQREG kshttp_httpClient_requestRegister;
OV_FNCEXTERN KSBASE_FNC_PROCREG kshttp_httpClient_processRegister;
OV_FNCEXTERN KSBASE_FNC_REQUNREG kshttp_httpClient_requestUnRegister;
OV_FNCEXTERN KSBASE_FNC_PROCUNREG kshttp_httpClient_processUnRegister;

OV_FNCEXTERN KSBASE_FNC_RESET kshttp_genericHttpClient_reset;
OV_FNCEXTERN KSHTTP_FNC_SENDHTTPREQUEST kshttp_genericHttpClient_sendHTTPRequest;
OV_FNCEXTERN OV_FNC_CONSTRUCTOR kshttp_genericHttpClient_constructor;

#define OV_VTBLBODY_kshttp_httpIdentificator \
    OV_VTBLBODY_ksbase_ProtocolIdentificator

#define OV_VTBLBODY_kshttp_httpclienthandler \
    OV_VTBLBODY_ksbase_ClientHandler \
    KSHTTP_FNC_INDATAHANDLING* m_analyzeRequestHeader; \
    KSHTTP_FNC_INDATAHANDLING* m_analyzeRequestBody; \
    KSHTTP_FNC_GENERATEKSBODY* m_generateHttpBody; \
    KSHTTP_FNC_GENERATEHEADER* m_generateHttpHeader; \
    KSHTTP_FNC_RESULT2HTTP* m_mapresult2http; \
    KSHTTP_FNC_OUTPACKETHANDLING* m_sendHttpHeader; \
    KSHTTP_FNC_OUTPACKETHANDLING* m_sendHttpBody;

#define OV_VTBLBODY_kshttp_getvarpushhandler \
    OV_VTBLBODY_ksbase_ClientHandler

#define OV_VTBLBODY_kshttp_httpClientHandlerExtension \
    OV_VTBLBODY_ksbase_baseClientHandlerExtension \
    KSHTTP_FNC_HANDLEEXTREQUEST* m_HandleExtendedRequest; \
    KSHTTP_FNC_CHECKCOMMAND* m_CheckCommand;

#define OV_VTBLBODY_kshttp_httpSimpleTicketAuthenticator \
    OV_VTBLBODY_ksbase_TicketAuthenticator

#define OV_VTBLBODY_kshttp_httpManagerCom \
    OV_VTBLBODY_ksbase_ComTask

#define OV_VTBLBODY_kshttp_httpClientBase \
    OV_VTBLBODY_ksbase_ClientBase

#define OV_VTBLBODY_kshttp_httpClient \
    OV_VTBLBODY_kshttp_httpClientBase

#define OV_VTBLBODY_kshttp_genericHttpClient \
    OV_VTBLBODY_kshttp_httpClientBase \
    KSHTTP_FNC_SENDHTTPREQUEST* m_sendHTTPRequest;

#define OV_VTBLBODY_kshttp_authenticatedsession \
    OV_VTBLBODY_ov_object

#define OV_VTBLBODY_kshttp_staticfile \
    OV_VTBLBODY_ov_object

OV_TYPEDEF_VTABLE(kshttp_httpIdentificator);
OV_TYPEDEF_VTABLE(kshttp_httpclienthandler);
OV_TYPEDEF_VTABLE(kshttp_getvarpushhandler);
OV_TYPEDEF_VTABLE(kshttp_httpClientHandlerExtension);
OV_TYPEDEF_VTABLE(kshttp_httpSimpleTicketAuthenticator);
OV_TYPEDEF_VTABLE(kshttp_httpManagerCom);
OV_TYPEDEF_VTABLE(kshttp_httpClientBase);
OV_TYPEDEF_VTABLE(kshttp_httpClient);
OV_TYPEDEF_VTABLE(kshttp_genericHttpClient);
OV_TYPEDEF_VTABLE(kshttp_authenticatedsession);
OV_TYPEDEF_VTABLE(kshttp_staticfile);

OV_DLLFNCEXPORT OV_RESULT kshttp_genericHttpClient_beginCommunication_set(
    OV_INSTPTR_kshttp_genericHttpClient pobj,
    const OV_BOOL value
);

OV_DLLFNCEXPORT OV_RESULT kshttp_genericHttpClient_URI_set(
    OV_INSTPTR_kshttp_genericHttpClient pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_TIME *kshttp_authenticatedsession_lastactivity_get(
    OV_INSTPTR_kshttp_authenticatedsession pobj
);

OV_DLLFNCEXPORT OV_RESULT kshttp_authenticatedsession_lastactivity_set(
    OV_INSTPTR_kshttp_authenticatedsession pobj,
    const OV_TIME *pvalue
);

OV_DLLFNCEXPORT OV_STRING kshttp_staticfile_content_get(
    OV_INSTPTR_kshttp_staticfile pobj
);

OV_DLLFNCEXPORT OV_RESULT kshttp_staticfile_content_set(
    OV_INSTPTR_kshttp_staticfile pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_STRING kshttp_staticfile_mimetype_get(
    OV_INSTPTR_kshttp_staticfile pobj
);

OV_DLLFNCEXPORT OV_RESULT kshttp_staticfile_mimetype_set(
    OV_INSTPTR_kshttp_staticfile pobj,
    const OV_STRING value
);

OV_DLLFNCEXPORT OV_STRING kshttp_staticfile_encoding_get(
    OV_INSTPTR_kshttp_staticfile pobj
);

OV_DLLFNCEXPORT OV_RESULT kshttp_staticfile_encoding_set(
    OV_INSTPTR_kshttp_staticfile pobj,
    const OV_STRING value
);

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_httpIdentificator;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_httpIdentificator;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_httpclienthandler;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_httpclienthandler;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_getvarpushhandler;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_getvarpushhandler;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_httpClientHandlerExtension;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_httpClientHandlerExtension;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_httpSimpleTicketAuthenticator;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_httpSimpleTicketAuthenticator;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_httpManagerCom;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_httpManagerCom;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_httpClientBase;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_httpClientBase;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_httpClient;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_httpClient;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_genericHttpClient;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_genericHttpClient;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_authenticatedsession;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_authenticatedsession;

extern OV_CLASS_DEF OV_CLASS_DEF_kshttp_staticfile;
OV_VAREXTERN OV_INSTPTR_ov_class pclass_kshttp_staticfile;

extern OV_LIBRARY_DEF OV_LIBRARY_DEF_kshttp;

OV_RESULT ov_library_setglobalvars_kshttp(void);

OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_kshttp(void);

#undef OV_VAREXTERN
#undef OV_FNCEXTERN

#ifdef __cplusplus
}
#endif

#endif

/*
*   End of file
*/
