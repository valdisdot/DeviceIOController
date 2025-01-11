#include "request/SendControllerStateRequestResolver.h"

SendControllerStateRequestResolver::SendControllerStateRequestResolver(const char* name, MessageExchanger &messageExchanger) : RequestResolver(name, false), messageExchanger(messageExchanger) {
}

int SendControllerStateRequestResolver::resolve(JsonVariant requestValue) {
    messageExchanger.sendControllerState();
    return $MESSAGE.RESPONSE$OK;
}
