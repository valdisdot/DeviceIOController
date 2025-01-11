#include "request/SetModesRequestResolver.h"

SetModesRequestResolver::SetModesRequestResolver(const char* name, PortHandler& portHandler, Storage& storage, MessageExchanger& messageExchanger) : RequestResolver(name, false), portHandler(portHandler), storage(storage), messageExchanger(messageExchanger) {
}

int SetModesRequestResolver::resolve(JsonVariant requestValue) {
    PortState& portState = storage.getPortState();
    int res;
    if (requestValue.is<JsonObject>()) {
        // object style data-set
        char key[4];
        for (int i = 0; i < $PORT.COUNT; ++i) {
            snprintf(key, 4, "%d", i);
            if (requestValue[key].is<int>())
                portState.setPortMode(i, requestValue[key].as<int>());
        }
        portHandler.pullState();
        storage.backupState();
        res = $MESSAGE.RESPONSE$OK;
    } else if (requestValue.is<JsonArray>()) {
        // array style mode-set
        portState.setModes(requestValue.as<JsonArray>());
        portHandler.pullState();
        storage.backupState();
        res = $MESSAGE.RESPONSE$OK;
    } else {
        res = $MESSAGE.RESPONSE$FAIL;
    }
    messageExchanger.sendState();
    return res;
}
