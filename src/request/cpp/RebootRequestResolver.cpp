#include "request/RebootRequestResolver.h"

RebootRequestResolver::RebootRequestResolver(const char* name) : RequestResolver(name, true) {
}

int RebootRequestResolver::resolve(JsonVariant requestValue) {
    return $MESSAGE.RESPONSE$OK;
}
