#include "request/ConfigureServerRequestResolver.h"

ConfigureServerRequestResolver::ConfigureServerRequestResolver(const char* name, Storage& storage) : RequestResolver(name, true), storage(storage) {
}

int ConfigureServerRequestResolver::resolve(JsonVariant requestValue) {
    if (requestValue.is<JsonObject>()) {
        // server config
        storage.getServerConfiguration().updateFromJson(requestValue.as<JsonObject>());
        storage.backupConfiguration();
        return $MESSAGE.RESPONSE$OK;
    } else {
        return $MESSAGE.RESPONSE$FAIL;
    }
}
