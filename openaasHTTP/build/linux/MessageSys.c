/*
*   This file was generated by the ACPLT/OV C-Code Generator.
*
*   C-Code Generator version: 1.6.4
*   ACPLT/OV library version: 2.0.0
*   Date of file generation:  21-Sep-2018 (10:33:41)
*
*   DO NOT EDIT THIS FILE!
*/

#ifndef OV_COMPILE_LIBRARY_MessageSys
#define OV_COMPILE_LIBRARY_MessageSys
#endif

#include "MessageSys.h"
#include "libov/ov_macros.h"

OV_DLLVAREXPORT OV_INSTPTR_ov_class pclass_MessageSys_MsgDelivery = NULL;
OV_DLLVAREXPORT OV_INSTPTR_ov_class pclass_MessageSys_Message = NULL;
OV_DLLVAREXPORT OV_INSTPTR_ov_class pclass_MessageSys_MsgSendExtension = NULL;
OV_DLLVAREXPORT OV_INSTPTR_ov_class pclass_MessageSys_inbox = NULL;
OV_DLLVAREXPORT OV_INSTPTR_ov_class pclass_MessageSys_msgIdentificator = NULL;
OV_DLLVAREXPORT OV_INSTPTR_ov_class pclass_MessageSys_msgHandler = NULL;

OV_DLLVAREXPORT OV_INSTPTR_ov_association passoc_MessageSys_MsgDelivery2CurrentMessage = NULL;
OV_DLLVAREXPORT OV_INSTPTR_ov_association passoc_MessageSys_MsgDelivery2Message = NULL;
OV_DLLVAREXPORT OV_INSTPTR_ov_association passoc_MessageSys_Message2Channel = NULL;
OV_DLLVAREXPORT OV_INSTPTR_ov_association passoc_MessageSys_SendExtension2Message = NULL;

OV_VTBL_MessageSys_MsgDelivery OV_VTABLE_MessageSys_MsgDelivery = {
    MessageSys_MsgDelivery_constructor,
    ov_object_checkinit,
    ksbase_ComTask_destructor,
    ov_object_startup,
    ov_object_shutdown,
    ov_object_rename,
    ksbase_ComTask_getaccess,
    ov_object_getflags,
    ov_object_getcomment,
    ov_object_gettechunit,
    ov_object_getvar,
    ov_object_setvar,
    ksbase_ComTask_calcExec,
    MessageSys_MsgDelivery_typemethod,
    MessageSys_MsgDelivery_sendMessage,
    MessageSys_MsgDelivery_findService
};

OV_VTBL_MessageSys_Message OV_VTABLE_MessageSys_Message = {
    MessageSys_Message_constructor,
    ov_object_checkinit,
    ov_object_destructor,
    ov_object_startup,
    ov_object_shutdown,
    ov_object_rename,
    MessageSys_Message_getaccess,
    ov_object_getflags,
    ov_object_getcomment,
    ov_object_gettechunit,
    ov_object_getvar,
    ov_object_setvar
};

OV_VTBL_MessageSys_MsgSendExtension OV_VTABLE_MessageSys_MsgSendExtension = {
    ksbase_ComTask_constructor,
    ov_object_checkinit,
    ksbase_ComTask_destructor,
    ov_object_startup,
    ov_object_shutdown,
    ov_object_rename,
    ksbase_ComTask_getaccess,
    ov_object_getflags,
    ov_object_getcomment,
    ov_object_gettechunit,
    ov_object_getvar,
    ov_object_setvar,
    ksbase_ComTask_calcExec,
    ksbase_ComTask_typemethod,
    (KSBASE_FNC_HANDLEDATA*)0,
    (MSGSYS_SENDMSG*)0
};

OV_VTBL_MessageSys_inbox OV_VTABLE_MessageSys_inbox = {
    ov_object_constructor,
    ov_object_checkinit,
    ov_object_destructor,
    ov_object_startup,
    ov_object_shutdown,
    ov_object_rename,
    ov_object_getaccess,
    ov_object_getflags,
    ov_object_getcomment,
    ov_object_gettechunit,
    ov_object_getvar,
    ov_object_setvar
};

OV_VTBL_MessageSys_msgIdentificator OV_VTABLE_MessageSys_msgIdentificator = {
    MessageSys_msgIdentificator_constructor,
    ov_object_checkinit,
    ov_object_destructor,
    ov_object_startup,
    ov_object_shutdown,
    ov_object_rename,
    ksbase_ProtocolIdentificator_getaccess,
    ov_object_getflags,
    ov_object_getcomment,
    ov_object_gettechunit,
    ov_object_getvar,
    ov_object_setvar,
    MessageSys_msgIdentificator_identify,
    MessageSys_msgIdentificator_createClientHandler
};

OV_VTBL_MessageSys_msgHandler OV_VTABLE_MessageSys_msgHandler = {
    ksbase_ComTask_constructor,
    ov_object_checkinit,
    ksbase_ComTask_destructor,
    MessageSys_msgHandler_startup,
    MessageSys_msgHandler_shutdown,
    ov_object_rename,
    ksbase_ComTask_getaccess,
    ov_object_getflags,
    ov_object_getcomment,
    ov_object_gettechunit,
    ov_object_getvar,
    ov_object_setvar,
    ksbase_ComTask_calcExec,
    ksbase_ClientHandler_typemethod,
    MessageSys_msgHandler_HandleRequest
};

char OV_INITSTRING_DEF_MessageSys_MsgDelivery_regComponentPath_1[] = "/communication/ServiceProvider/SystemServices";

OV_VARIABLE_DEF OV_VARIABLE_DEF_MessageSys_MsgDelivery[] = {{
    &OV_VARIABLE_DEF_MessageSys_MsgDelivery[1],
    "retrieveMessage",
    1,
    2,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_MsgDelivery, v_retrieveMessage),
    0,
    (OV_STRING)NULL,
    "setVar called by ksapi",
    NULL,
    (OV_FNCPTR_SET)MessageSys_MsgDelivery_retrieveMessage_set
}, {
    &OV_VARIABLE_DEF_MessageSys_MsgDelivery[2],
    "regComponentPath",
    1,
    0,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_MsgDelivery, v_regComponentPath),
    0,
    (OV_STRING)NULL,
    "Path to the Domain where the registered Services are located",
    NULL,
    NULL
}, {
    &OV_VARIABLE_DEF_MessageSys_MsgDelivery[3],
    "sendTimeOut",
    1,
    0,
    17,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_UINT),
    offsetof(OV_INST_MessageSys_MsgDelivery, v_sendTimeOut),
    0,
    (OV_STRING)NULL,
    "Time in seconds to wait for delivery of a message before it is deleted from the queue",
    NULL,
    NULL
}, {
    (OV_VARIABLE_DEF*)0,
    "sendTime",
    1,
    0,
    49,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_TIME),
    offsetof(OV_INST_MessageSys_MsgDelivery, v_sendTime),
    0,
    (OV_STRING)NULL,
    "Time of last send process",
    NULL,
    NULL
}};

OV_PART_DEF OV_PART_DEF_MessageSys_MsgDelivery[] = {{
    (OV_PART_DEF*)0,
    "Channels",
    "ov/domain",
     0,
    offsetof(OV_INST_MessageSys_MsgDelivery, p_Channels)
}};

OV_OPERATION_DEF OV_OPERATION_DEF_MessageSys_MsgDelivery[] = {{
    &OV_OPERATION_DEF_MessageSys_MsgDelivery[1],
    "constructor",
    0,
    "OV_FNC_CONSTRUCTOR"
}, {
    &OV_OPERATION_DEF_MessageSys_MsgDelivery[2],
    "typemethod",
    0,
    "KSBASE_FNC_TYPEMETHOD"
}, {
    &OV_OPERATION_DEF_MessageSys_MsgDelivery[3],
    "sendMessage",
    0,
    "SENDMESSAGE_FNC"
}, {
    (OV_OPERATION_DEF*)0,
    "findService",
    0,
    "MSGSYS_FINDSERVICE_FNC"
}};

OV_CLASS_DEF OV_CLASS_DEF_MessageSys_MsgDelivery = {
    &OV_CLASS_DEF_MessageSys_Message,
    "MsgDelivery",
    "ksbase/ComTask",
    1,
    0,
    (OV_STRING)NULL,
    Ov_GetInstSize(MessageSys_MsgDelivery),
    Ov_GetStaticInstSize(MessageSys_MsgDelivery),
    (OV_POINTER)&OV_VTABLE_MessageSys_MsgDelivery,
    &OV_VARIABLE_DEF_MessageSys_MsgDelivery[0],
    &OV_PART_DEF_MessageSys_MsgDelivery[0],
    &OV_OPERATION_DEF_MessageSys_MsgDelivery[0]
};

char OV_INITSTRING_DEF_MessageSys_Message_senderAddress_1[] = "127.0.0.1";
char OV_INITSTRING_DEF_MessageSys_Message_receiverAddress_1[] = "127.0.0.1";
char OV_INITSTRING_DEF_MessageSys_Message_senderName_1[] = "";
char OV_INITSTRING_DEF_MessageSys_Message_receiverName_1[] = "";
char OV_INITSTRING_DEF_MessageSys_Message_senderComponent_1[] = "";
char OV_INITSTRING_DEF_MessageSys_Message_receiverComponent_1[] = "";
char OV_INITSTRING_DEF_MessageSys_Message_msgID_1[] = "";
char OV_INITSTRING_DEF_MessageSys_Message_refMsgID_1[] = "";
char OV_INITSTRING_DEF_MessageSys_Message_auth_1[] = "";

OV_VARIABLE_DEF OV_VARIABLE_DEF_MessageSys_Message[] = {{
    &OV_VARIABLE_DEF_MessageSys_Message[1],
    "senderAddress",
    1,
    3,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_senderAddress),
    0,
    (OV_STRING)NULL,
    "Address of sender machine",
    (OV_FNCPTR_GET)MessageSys_Message_senderAddress_get,
    (OV_FNCPTR_SET)MessageSys_Message_senderAddress_set
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[2],
    "receiverAddress",
    1,
    3,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_receiverAddress),
    0,
    (OV_STRING)NULL,
    "Address of receiver machine",
    (OV_FNCPTR_GET)MessageSys_Message_receiverAddress_get,
    (OV_FNCPTR_SET)MessageSys_Message_receiverAddress_set
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[3],
    "senderName",
    1,
    3,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_senderName),
    0,
    (OV_STRING)NULL,
    "Servername of sender",
    (OV_FNCPTR_GET)MessageSys_Message_senderName_get,
    (OV_FNCPTR_SET)MessageSys_Message_senderName_set
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[4],
    "receiverName",
    1,
    3,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_receiverName),
    0,
    (OV_STRING)NULL,
    "Servername of receiver",
    (OV_FNCPTR_GET)MessageSys_Message_receiverName_get,
    (OV_FNCPTR_SET)MessageSys_Message_receiverName_set
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[5],
    "senderComponent",
    1,
    3,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_senderComponent),
    0,
    (OV_STRING)NULL,
    "Name of sender-component",
    (OV_FNCPTR_GET)MessageSys_Message_senderComponent_get,
    (OV_FNCPTR_SET)MessageSys_Message_senderComponent_set
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[6],
    "receiverComponent",
    1,
    3,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_receiverComponent),
    0,
    (OV_STRING)NULL,
    "Name of receiver-component",
    (OV_FNCPTR_GET)MessageSys_Message_receiverComponent_get,
    (OV_FNCPTR_SET)MessageSys_Message_receiverComponent_set
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[7],
    "msgStatus",
    1,
    3,
    16,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_INT),
    offsetof(OV_INST_MessageSys_Message, v_msgStatus),
    0,
    (OV_STRING)NULL,
    "0=NEW, 1=READYFORSENDING, 2=WAITING, 3=DONE, 4=RECEIVERERROR, 5=FATALERROR, 10=NEWARRIVED, 11=DONERECEIVE",
    (OV_FNCPTR_GET)MessageSys_Message_msgStatus_get,
    (OV_FNCPTR_SET)MessageSys_Message_msgStatus_set
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[8],
    "msgID",
    1,
    3,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_msgID),
    0,
    (OV_STRING)NULL,
    "ID of this Message",
    (OV_FNCPTR_GET)MessageSys_Message_msgID_get,
    (OV_FNCPTR_SET)MessageSys_Message_msgID_set
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[9],
    "refMsgID",
    1,
    0,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_refMsgID),
    0,
    (OV_STRING)NULL,
    "ID of last Message in Conversation",
    NULL,
    NULL
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[10],
    "auth",
    1,
    0,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_auth),
    0,
    (OV_STRING)NULL,
    "Authentication Data in header",
    NULL,
    NULL
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[11],
    "msgBody",
    1,
    3,
    48,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_STRING),
    offsetof(OV_INST_MessageSys_Message, v_msgBody),
    0,
    (OV_STRING)NULL,
    "Message Body",
    (OV_FNCPTR_GET)MessageSys_Message_msgBody_get,
    (OV_FNCPTR_SET)MessageSys_Message_msgBody_set
}, {
    &OV_VARIABLE_DEF_MessageSys_Message[12],
    "sendBy",
    1,
    0,
    65,
    "MESSAGESYS_SENDBY",
    (OV_STRING)NULL,
    1*sizeof(MESSAGESYS_SENDBY),
    offsetof(OV_INST_MessageSys_Message, v_sendBy),
    0,
    (OV_STRING)NULL,
    "Determines sending behaviour: 0: directly; 2: ks-setvar; 16: extension",
    NULL,
    NULL
}, {
    (OV_VARIABLE_DEF*)0,
    "expectAnswer",
    1,
    0,
    2,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_BOOL),
    offsetof(OV_INST_MessageSys_Message, v_expectAnswer),
    0,
    (OV_STRING)NULL,
    "TRUE tells MsgDelivery to expect an answer message (keep connection open if possible with protocol)",
    NULL,
    NULL
}};

OV_OPERATION_DEF OV_OPERATION_DEF_MessageSys_Message[] = {{
    &OV_OPERATION_DEF_MessageSys_Message[1],
    "constructor",
    0,
    "OV_FNC_CONSTRUCTOR"
}, {
    (OV_OPERATION_DEF*)0,
    "getaccess",
    0,
    "OV_FNC_GETACCESS"
}};

OV_CLASS_DEF OV_CLASS_DEF_MessageSys_Message = {
    &OV_CLASS_DEF_MessageSys_MsgSendExtension,
    "Message",
    "ov/object",
    1,
    0,
    (OV_STRING)NULL,
    Ov_GetInstSize(MessageSys_Message),
    Ov_GetStaticInstSize(MessageSys_Message),
    (OV_POINTER)&OV_VTABLE_MessageSys_Message,
    &OV_VARIABLE_DEF_MessageSys_Message[0],
    (OV_PART_DEF*)0,
    &OV_OPERATION_DEF_MessageSys_Message[0]
};


OV_OPERATION_DEF OV_OPERATION_DEF_MessageSys_MsgSendExtension[] = {{
    (OV_OPERATION_DEF*)0,
    "sendMessage",
    1,
    "MSGSYS_SENDMSG"
}};

OV_CLASS_DEF OV_CLASS_DEF_MessageSys_MsgSendExtension = {
    &OV_CLASS_DEF_MessageSys_inbox,
    "MsgSendExtension",
    "ksbase/DataHandler",
    0,
    0,
    "Baseclass for Send Extensions. Is a message should be send via an Extension the Message is linked to the Extension Object.",
    Ov_GetInstSize(MessageSys_MsgSendExtension),
    Ov_GetStaticInstSize(MessageSys_MsgSendExtension),
    (OV_POINTER)&OV_VTABLE_MessageSys_MsgSendExtension,
    (OV_VARIABLE_DEF*)0,
    (OV_PART_DEF*)0,
    &OV_OPERATION_DEF_MessageSys_MsgSendExtension[0]
};


OV_VARIABLE_DEF OV_VARIABLE_DEF_MessageSys_inbox[] = {{
    (OV_VARIABLE_DEF*)0,
    "holdConnection",
    1,
    0,
    2,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_BOOL),
    offsetof(OV_INST_MessageSys_inbox, v_holdConnection),
    0,
    (OV_STRING)NULL,
    "TRUE: tells the message sys to keep the connections for incoming messages open to send answers back",
    NULL,
    NULL
}};

OV_CLASS_DEF OV_CLASS_DEF_MessageSys_inbox = {
    &OV_CLASS_DEF_MessageSys_msgIdentificator,
    "inbox",
    "ov/domain",
    1,
    0,
    "generic inbox class. Basicly a domain without functionality",
    Ov_GetInstSize(MessageSys_inbox),
    Ov_GetStaticInstSize(MessageSys_inbox),
    (OV_POINTER)&OV_VTABLE_MessageSys_inbox,
    &OV_VARIABLE_DEF_MessageSys_inbox[0],
    (OV_PART_DEF*)0,
    (OV_OPERATION_DEF*)0
};


OV_OPERATION_DEF OV_OPERATION_DEF_MessageSys_msgIdentificator[] = {{
    &OV_OPERATION_DEF_MessageSys_msgIdentificator[1],
    "constructor",
    0,
    "OV_FNC_CONSTRUCTOR"
}, {
    &OV_OPERATION_DEF_MessageSys_msgIdentificator[2],
    "identify",
    0,
    "KSBASE_FNC_IDENTIFY"
}, {
    (OV_OPERATION_DEF*)0,
    "createClientHandler",
    0,
    "KSBASE_FNC_CREATECH"
}};

OV_CLASS_DEF OV_CLASS_DEF_MessageSys_msgIdentificator = {
    &OV_CLASS_DEF_MessageSys_msgHandler,
    "msgIdentificator",
    "ksbase/ProtocolIdentificator",
    1,
    0,
    "class for identifing MsgSys-messages",
    Ov_GetInstSize(MessageSys_msgIdentificator),
    Ov_GetStaticInstSize(MessageSys_msgIdentificator),
    (OV_POINTER)&OV_VTABLE_MessageSys_msgIdentificator,
    (OV_VARIABLE_DEF*)0,
    (OV_PART_DEF*)0,
    &OV_OPERATION_DEF_MessageSys_msgIdentificator[0]
};


OV_VARIABLE_DEF OV_VARIABLE_DEF_MessageSys_msgHandler[] = {{
    &OV_VARIABLE_DEF_MessageSys_msgHandler[1],
    "connectionTimeout",
    1,
    0,
    17,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_UINT),
    offsetof(OV_INST_MessageSys_msgHandler, v_connectionTimeout),
    0,
    (OV_STRING)NULL,
    "Timeout in s for idle connections",
    NULL,
    NULL
}, {
    (OV_VARIABLE_DEF*)0,
    "timeoutIncomplete",
    1,
    0,
    17,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_UINT),
    offsetof(OV_INST_MessageSys_msgHandler, v_timeoutIncomplete),
    0,
    (OV_STRING)NULL,
    "Time in s to wait for the next part of an incomplete message",
    NULL,
    NULL
}};

OV_OPERATION_DEF OV_OPERATION_DEF_MessageSys_msgHandler[] = {{
    &OV_OPERATION_DEF_MessageSys_msgHandler[1],
    "startup",
    0,
    "OV_FNC_STARTUP"
}, {
    &OV_OPERATION_DEF_MessageSys_msgHandler[2],
    "shutdown",
    0,
    "OV_FNC_SHUTDOWN"
}, {
    (OV_OPERATION_DEF*)0,
    "HandleRequest",
    0,
    "KSBASE_FNC_HANDLEREQUEST"
}};

OV_CLASS_DEF OV_CLASS_DEF_MessageSys_msgHandler = {
    (OV_CLASS_DEF*)0,
    "msgHandler",
    "ksbase/ClientHandler",
    1,
    0,
    "Handler for MsgSys-messages. ",
    Ov_GetInstSize(MessageSys_msgHandler),
    Ov_GetStaticInstSize(MessageSys_msgHandler),
    (OV_POINTER)&OV_VTABLE_MessageSys_msgHandler,
    &OV_VARIABLE_DEF_MessageSys_msgHandler[0],
    (OV_PART_DEF*)0,
    &OV_OPERATION_DEF_MessageSys_msgHandler[0]
};

OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_MessageSys_MsgDelivery2CurrentMessage = {
    &OV_ASSOCIATION_DEF_MessageSys_MsgDelivery2Message,
    "MsgDelivery2CurrentMessage",
    3,
    0,
    "chCurrentMessage",
    "MessageSys/MsgDelivery",
    "parMsgDelivery",
    "MessageSys/Message",
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    0,
    0,
    0,
    0,
    (OV_FNCPTR_LINK)MessageSys_MsgDelivery2CurrentMessage_link,
    (OV_FNCPTR_UNLINK)MessageSys_MsgDelivery2CurrentMessage_unlink,
    (OV_FNCPTR_GETACCESS)MessageSys_MsgDelivery2CurrentMessage_getaccess
};

OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_MessageSys_MsgDelivery2Message = {
    &OV_ASSOCIATION_DEF_MessageSys_Message2Channel,
    "MsgDelivery2Message",
    1,
    0,
    "chMessage",
    "MessageSys/MsgDelivery",
    "parMsgDelivery2",
    "MessageSys/Message",
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    0,
    0,
    0,
    0,
    (OV_FNCPTR_LINK)MessageSys_MsgDelivery2Message_link,
    (OV_FNCPTR_UNLINK)MessageSys_MsgDelivery2Message_unlink,
    (OV_FNCPTR_GETACCESS)MessageSys_MsgDelivery2Message_getaccess
};

OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_MessageSys_Message2Channel = {
    &OV_ASSOCIATION_DEF_MessageSys_SendExtension2Message,
    "Message2Channel",
    3,
    0,
    "chChannel",
    "MessageSys/Message",
    "parMsg",
    "ksbase/Channel",
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    0,
    0,
    0,
    0,
    (OV_FNCPTR_LINK)MessageSys_Message2Channel_link,
    (OV_FNCPTR_UNLINK)MessageSys_Message2Channel_unlink,
    (OV_FNCPTR_GETACCESS)MessageSys_Message2Channel_getaccess
};

OV_ASSOCIATION_DEF OV_ASSOCIATION_DEF_MessageSys_SendExtension2Message = {
    (OV_ASSOCIATION_DEF*)0,
    "SendExtension2Message",
    1,
    0,
    "chMsg",
    "MessageSys/MsgSendExtension",
    "parSendExt",
    "MessageSys/Message",
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    0,
    0,
    0,
    0,
    (OV_FNCPTR_LINK)MessageSys_SendExtension2Message_link,
    (OV_FNCPTR_UNLINK)MessageSys_SendExtension2Message_unlink,
    (OV_FNCPTR_GETACCESS)MessageSys_SendExtension2Message_getaccess
};

OV_LIBRARY_DEF OV_LIBRARY_DEF_MessageSys = {
    "MessageSys",
    "V0.1 (DD-Mon-YYYY)",
    "2.0.0",
    "",
    "",
    "",
    (OV_STRUCTURE_DEF*)0,
    &OV_CLASS_DEF_MessageSys_MsgDelivery,
    &OV_ASSOCIATION_DEF_MessageSys_MsgDelivery2CurrentMessage,
    ov_library_setglobalvars_MessageSys
};

#include "libov/ov_macros.h"

OV_RESULT ov_library_setglobalvars_MessageSys(void) {
    OV_INSTPTR_ov_library plib;
    OV_INSTPTR_ov_variable pvar;

    Ov_ForEachChildEx(ov_instantiation, pclass_ov_library, plib, ov_library) {
        if(!strcmp(plib->v_identifier, "MessageSys")) {
            pclass_MessageSys_MsgDelivery = Ov_SearchChildEx(ov_containment, plib, "MsgDelivery", ov_class);
            if(!pclass_MessageSys_MsgDelivery) {
                return OV_ERR_GENERIC;
            }
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_MsgDelivery, "regComponentPath", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_MsgDelivery_regComponentPath_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_MsgDelivery, "sendTimeOut", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_UINT;
            pvar->v_initialvalue.value.valueunion.val_uint = 5 ;
            pclass_MessageSys_Message = Ov_SearchChildEx(ov_containment, plib, "Message", ov_class);
            if(!pclass_MessageSys_Message) {
                return OV_ERR_GENERIC;
            }
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "senderAddress", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_Message_senderAddress_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "receiverAddress", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_Message_receiverAddress_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "senderName", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_Message_senderName_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "receiverName", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_Message_receiverName_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "senderComponent", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_Message_senderComponent_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "receiverComponent", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_Message_receiverComponent_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "msgStatus", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_INT;
            pvar->v_initialvalue.value.valueunion.val_int = 0 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "msgID", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_Message_msgID_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "refMsgID", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_Message_refMsgID_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "auth", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_STRING;
            pvar->v_initialvalue.value.valueunion.val_string =  OV_INITSTRING_DEF_MessageSys_Message_auth_1 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_Message, "expectAnswer", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_BOOL;
            pvar->v_initialvalue.value.valueunion.val_bool = 0 ;
            pclass_MessageSys_MsgSendExtension = Ov_SearchChildEx(ov_containment, plib, "MsgSendExtension", ov_class);
            if(!pclass_MessageSys_MsgSendExtension) {
                return OV_ERR_GENERIC;
            }
            pclass_MessageSys_inbox = Ov_SearchChildEx(ov_containment, plib, "inbox", ov_class);
            if(!pclass_MessageSys_inbox) {
                return OV_ERR_GENERIC;
            }
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_inbox, "holdConnection", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_BOOL;
            pvar->v_initialvalue.value.valueunion.val_bool = 0 ;
            pclass_MessageSys_msgIdentificator = Ov_SearchChildEx(ov_containment, plib, "msgIdentificator", ov_class);
            if(!pclass_MessageSys_msgIdentificator) {
                return OV_ERR_GENERIC;
            }
            pclass_MessageSys_msgHandler = Ov_SearchChildEx(ov_containment, plib, "msgHandler", ov_class);
            if(!pclass_MessageSys_msgHandler) {
                return OV_ERR_GENERIC;
            }
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_msgHandler, "connectionTimeout", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_UINT;
            pvar->v_initialvalue.value.valueunion.val_uint = 120 ;
            pvar = Ov_SearchChildEx(ov_containment, pclass_MessageSys_msgHandler, "timeoutIncomplete", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_UINT;
            pvar->v_initialvalue.value.valueunion.val_uint = 2 ;
            passoc_MessageSys_MsgDelivery2CurrentMessage = Ov_SearchChildEx(ov_containment, plib, "MsgDelivery2CurrentMessage", ov_association);
            if(!passoc_MessageSys_MsgDelivery2CurrentMessage) {
                return OV_ERR_GENERIC;
            }
            passoc_MessageSys_MsgDelivery2Message = Ov_SearchChildEx(ov_containment, plib, "MsgDelivery2Message", ov_association);
            if(!passoc_MessageSys_MsgDelivery2Message) {
                return OV_ERR_GENERIC;
            }
            passoc_MessageSys_Message2Channel = Ov_SearchChildEx(ov_containment, plib, "Message2Channel", ov_association);
            if(!passoc_MessageSys_Message2Channel) {
                return OV_ERR_GENERIC;
            }
            passoc_MessageSys_SendExtension2Message = Ov_SearchChildEx(ov_containment, plib, "SendExtension2Message", ov_association);
            if(!passoc_MessageSys_SendExtension2Message) {
                return OV_ERR_GENERIC;
            }
            return OV_ERR_OK;
        }
    }
    return OV_ERR_GENERIC;
}

OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_MessageSys(void) {
    /*
     * loading required libraries
     */
    Ov_loadRequiredLib("ksbase");
    Ov_loadRequiredLib("ksapi");
    return &OV_LIBRARY_DEF_MessageSys;
}

/*
*   End of file
*/
