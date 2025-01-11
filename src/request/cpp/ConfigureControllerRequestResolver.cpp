#include "request/ConfigureControllerRequestResolver.h"

ConfigureControllerRequestResolver::ConfigureControllerRequestResolver(const char* name, Storage& storage, Logger &logger) : RequestResolver(name, false), storage(storage), logger(logger) {
}

int ConfigureControllerRequestResolver::resolve(JsonVariant requestValue) {
    if (requestValue.is<JsonObject>()) {
        // controller config
        ControllerConfiguration& controllerConfiguration = storage.getControllerConfiguration();
        controllerConfiguration.updateFromJson(requestValue.as<JsonObject>());
        logger.setLogLevel(controllerConfiguration.getLogLevel());
        storage.backupConfiguration();
        return $MESSAGE.RESPONSE$OK;
    } else {
        return $MESSAGE.RESPONSE$FAIL;
    }
}
