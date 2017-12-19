//
// Created by Jérôme Lenssen on 16.12.17.
//

#ifndef UNTITLED_TYPES_H
#define UNTITLED_TYPES_H

#include<string>

using namespace std;

typedef struct REQUEST_HEADER {
    //timestamp
    //requestHandle
    //timeout
    //endpoint
    //additionalHeader
} REQUEST_HEADER;

typedef struct RESPONSE_HEADER {
    //timestamp
    //requestHandle
    //result
    //additionalHeader
} RESPONSE_HEADER;

#endif //UNTITLED_TYPES_H
