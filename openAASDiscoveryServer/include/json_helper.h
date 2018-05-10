#ifndef __JSON_H_
#define __JSON_H_

#include "jsmn.h"
#include "libov/ov_macros.h"
#include "openAASDiscoveryServer.h"


int jsoneq(const char *json, const jsmntok_t *tok, const char *s);
OV_RESULT jsonTokenize(json_data* jsonData);
OV_RESULT jsonRequestParse(request_data* requestData);
OV_RESULT jsonResponseParse(response_data* responseData);
OV_RESULT jsonGetTokenIndexByTags(const OV_STRING_VEC tags, const json_data jsonData, OV_UINT_VEC tokenIndex);
OV_RESULT jsonGetValuesByTags(const OV_STRING_VEC tags, const json_data jsonData, OV_STRING_VEC values);
OV_RESULT jsonGetValuesAndTokenIndexByTags(const OV_STRING_VEC tags, const json_data jsonData, OV_STRING_VEC values, OV_UINT_VEC tokenIndex);
OV_RESULT jsonGetValueByToken(const char* js, const jsmntok_t* t, OV_STRING* str);
#endif
