#include "request/ConfigureNetworkRequestResolver.h"

ConfigureNetworkRequestResolver::ConfigureNetworkRequestResolver(const char* name, Storage& storage) : RequestResolver(name, true), storage(storage) {
}

int ConfigureNetworkRequestResolver::resolve(JsonVariant requestValue) {
    if (requestValue.is<JsonObject>()) {
        // connection config
        storage.getConnectionConfiguration().updateFromJson(requestValue.as<JsonObject>());
        storage.backupConfiguration();
        return $MESSAGE.RESPONSE$OK;
    } else {
        return $MESSAGE.RESPONSE$FAIL;
    }
}
