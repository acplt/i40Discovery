//
// Created by Jérôme Lenssen on 18.12.17.
//

#ifndef DISTRIBUTEDDISCOVERYSERVER_SERVICES_H
#define DISTRIBUTEDDISCOVERYSERVER_SERVICES_H

// encoding of all service requests
#define GET_KESEC_KEDS_Request 0
#define AUT_KESEC_Request 1
#define RELEASE_KEY_KESEC_Request 2
#define GET_KES_KESEC_Request 3
#define REG_KEREG_Request 4
#define DEREG_KEREG_Request 5
#define RESOLVE_KERES_Request 6
#define SEARCH_DATA_ID_Request 7
#define SEARCH_SERVICE_ID_Request 8
#define SEARCH_DATA_TAGS_Request 9
#define SEARCH_SERVICE_TAGS_Request 10

// encoding of all service responses
#define GET_KESEC_KEDS_Response 11
#define AUT_KESEC_Response 12
#define RELEASE_KEY_KESEC_Response 13
#define GET_KES_KESEC_Response 14
#define REG_KEREG_Response 15
#define DEREG_KEREG_Response 16
#define RESOLVE_KERES_Response 17
#define SEARCH_DATA_ID_Response 18
#define SEARCH_SERVICE_ID_Response 19
#define SEARCH_DATA_TAGS_Response 20
#define SEARCH_SERVICE_TAGS_Response 21

// statuscode
#define DS_OK 100
#define DS_ABORT 200

#endif //DISTRIBUTEDDISCOVERYSERVER_SERVICES_H
