/*
*   This file was generated by the ACPLT/OV C-Code Generator.
*
*   C-Code Generator version: 1.6.4
*   ACPLT/OV library version: 2.0.0
*   Date of file generation:  21-Sep-2018 (10:33:41)
*
*   DO NOT EDIT THIS FILE!
*/

#ifndef OV_COMPILE_LIBRARY_openaasHTTP
#define OV_COMPILE_LIBRARY_openaasHTTP
#endif

#include "openaasHTTP.h"
#include "libov/ov_macros.h"

OV_DLLVAREXPORT OV_INSTPTR_ov_class pclass_openaasHTTP_openaasHTTPExt = NULL;

OV_VTBL_openaasHTTP_openaasHTTPExt OV_VTABLE_openaasHTTP_openaasHTTPExt = {
    openaasHTTP_openaasHTTPExt_constructor,
    ov_object_checkinit,
    ksbase_ComTask_destructor,
    ksbase_ClientHandler_startup,
    ksbase_ClientHandler_shutdown,
    ov_object_rename,
    ksbase_ComTask_getaccess,
    ov_object_getflags,
    ov_object_getcomment,
    ov_object_gettechunit,
    ov_object_getvar,
    ov_object_setvar,
    ksbase_ComTask_calcExec,
    ksbase_ClientHandler_typemethod,
    kshttp_httpClientHandlerExtension_HandleRequest,
    openaasHTTP_openaasHTTPExt_HandleExtendedRequest,
    openaasHTTP_openaasHTTPExt_CheckCommand
};


OV_VARIABLE_DEF OV_VARIABLE_DEF_openaasHTTP_openaasHTTPExt[] = {{
    &OV_VARIABLE_DEF_openaasHTTP_openaasHTTPExt[1],
    "queryType",
    1,
    0,
    17,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    1*sizeof(OV_UINT),
    offsetof(OV_INST_openaasHTTP_openaasHTTPExt, v_queryType),
    0,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    NULL,
    NULL
}, {
    &OV_VARIABLE_DEF_openaasHTTP_openaasHTTPExt[2],
    "pAAS",
    1,
    0,
    65,
    "OV_INSTPTR_openaas_aas",
    (OV_STRING)NULL,
    1*sizeof(OV_INSTPTR_openaas_aas),
    offsetof(OV_INST_openaasHTTP_openaasHTTPExt, v_pAAS),
    0,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    NULL,
    NULL
}, {
    &OV_VARIABLE_DEF_openaasHTTP_openaasHTTPExt[3],
    "pSubModel",
    1,
    0,
    65,
    "OV_INSTPTR_openaas_SubModel",
    (OV_STRING)NULL,
    1*sizeof(OV_INSTPTR_openaas_SubModel),
    offsetof(OV_INST_openaasHTTP_openaasHTTPExt, v_pSubModel),
    0,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    NULL,
    NULL
}, {
    &OV_VARIABLE_DEF_openaasHTTP_openaasHTTPExt[4],
    "pStatement",
    1,
    0,
    65,
    "OV_INSTPTR_propertyValueStatement_PropertyValueStatement",
    (OV_STRING)NULL,
    1*sizeof(OV_INSTPTR_propertyValueStatement_PropertyValueStatement),
    offsetof(OV_INST_openaasHTTP_openaasHTTPExt, v_pStatement),
    0,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    NULL,
    NULL
}, {
    (OV_VARIABLE_DEF*)0,
    "pInterfaceDiscoveryServer",
    1,
    0,
    65,
    "OV_INSTPTR_openaas_InterfaceDiscoveryServer",
    (OV_STRING)NULL,
    1*sizeof(OV_INSTPTR_openaas_InterfaceDiscoveryServer),
    offsetof(OV_INST_openaasHTTP_openaasHTTPExt, v_pInterfaceDiscoveryServer),
    0,
    (OV_STRING)NULL,
    (OV_STRING)NULL,
    NULL,
    NULL
}};

OV_OPERATION_DEF OV_OPERATION_DEF_openaasHTTP_openaasHTTPExt[] = {{
    &OV_OPERATION_DEF_openaasHTTP_openaasHTTPExt[1],
    "constructor",
    0,
    "OV_FNC_CONSTRUCTOR"
}, {
    &OV_OPERATION_DEF_openaasHTTP_openaasHTTPExt[2],
    "CheckCommand",
    0,
    "KSHTTP_FNC_CHECKCOMMAND"
}, {
    (OV_OPERATION_DEF*)0,
    "HandleExtendedRequest",
    0,
    "KSHTTP_FNC_HANDLEEXTREQUEST"
}};

OV_CLASS_DEF OV_CLASS_DEF_openaasHTTP_openaasHTTPExt = {
    (OV_CLASS_DEF*)0,
    "openaasHTTPExt",
    "kshttp/httpClientHandlerExtension",
    1,
    0,
    (OV_STRING)NULL,
    Ov_GetInstSize(openaasHTTP_openaasHTTPExt),
    Ov_GetStaticInstSize(openaasHTTP_openaasHTTPExt),
    (OV_POINTER)&OV_VTABLE_openaasHTTP_openaasHTTPExt,
    &OV_VARIABLE_DEF_openaasHTTP_openaasHTTPExt[0],
    (OV_PART_DEF*)0,
    &OV_OPERATION_DEF_openaasHTTP_openaasHTTPExt[0]
};

OV_LIBRARY_DEF OV_LIBRARY_DEF_openaasHTTP = {
    "openaasHTTP",
    "V0.1 (DD-Mon-YYYY)",
    "2.0.0",
    "",
    "",
    "",
    (OV_STRUCTURE_DEF*)0,
    &OV_CLASS_DEF_openaasHTTP_openaasHTTPExt,
    (OV_ASSOCIATION_DEF*)0,
    ov_library_setglobalvars_openaasHTTP
};

#include "libov/ov_macros.h"

OV_RESULT ov_library_setglobalvars_openaasHTTP(void) {
    OV_INSTPTR_ov_library plib;
    OV_INSTPTR_ov_variable pvar;

    Ov_ForEachChildEx(ov_instantiation, pclass_ov_library, plib, ov_library) {
        if(!strcmp(plib->v_identifier, "openaasHTTP")) {
            pclass_openaasHTTP_openaasHTTPExt = Ov_SearchChildEx(ov_containment, plib, "openaasHTTPExt", ov_class);
            if(!pclass_openaasHTTP_openaasHTTPExt) {
                return OV_ERR_GENERIC;
            }
            pvar = Ov_SearchChildEx(ov_containment, pclass_openaasHTTP_openaasHTTPExt, "queryType", ov_variable);
            pvar->v_initialvalue.value.vartype = OV_VT_UINT;
            pvar->v_initialvalue.value.valueunion.val_uint = 0 ;
            return OV_ERR_OK;
        }
    }
    return OV_ERR_GENERIC;
}

OV_DLLFNCEXPORT OV_LIBRARY_DEF *ov_library_open_openaasHTTP(void) {
    /*
     * loading required libraries
     */
    Ov_loadRequiredLib("ksbase");
    Ov_loadRequiredLib("kshttp");
    Ov_loadRequiredLib("ksapi");
    Ov_loadRequiredLib("MessageSys");
    Ov_loadRequiredLib("fb");
    Ov_loadRequiredLib("identification");
    Ov_loadRequiredLib("propertyValueStatement");
    Ov_loadRequiredLib("lifeCycleEntry");
    Ov_loadRequiredLib("openAASDiscoveryServer");
    Ov_loadRequiredLib("openaas");
    return &OV_LIBRARY_DEF_openaasHTTP;
}

/*
*   End of file
*/
