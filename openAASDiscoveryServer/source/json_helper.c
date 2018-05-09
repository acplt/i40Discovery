#include "json_helper.h"

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

int scmp(char *s1, char *s2) {
	while(*s1 != '\0' && *s1 == *s2) { s1++; s2++; }
	return (*s1 - *s2);
}

jsmntok_t* findTag(const char* js, jsmntok_t *tokens, const char* tag) {
	for(int i=0; i < sizeof(tokens)/sizeof(jsmntok_t); i++) {
		char* tokStr = (char *)malloc(tokens[i].size);

		strncpy(tokStr, &js[tokens[i].start], (size_t)tokens[i].size);

		if(!scmp(tokStr, (char*)tag)) {
			return &tokens[i];
		}
	}
	return NULL;
}


char* getTagValue(const char* js, jsmntok_t tok, const char* tag) {
	return (char *)NULL;
}
