#ifndef __JSON_H_
#define __JSON_H_

#include "jsmn.h"

jsmntok_t* findTag(const char* js, jsmntok_t *tokens, const char* tag);
char* getTagValue(const char* js, jsmntok_t tok, const char* tag);

#endif
