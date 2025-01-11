#include "request/SendStateRequestResolver.h"

SendStateRequestResolver::SendStateRequestResolver(const char* name, MessageExchanger& messageExchanger) : RequestResolver(name, false), messageExchanger(messageExchanger) {
}

int SendStateRequestResolver::resolve(JsonVariant requestValue) {
    messageExchanger.sendState();
    return $MESSAGE.RESPONSE$OK;
}
