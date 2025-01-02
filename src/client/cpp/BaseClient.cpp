#include "client/BaseClient.h"

void BaseClient::sendState() {
    portHandler.pushState();
    serializeJson(storage.getPortState().getAsJson(), buffer, $SYSTEM.SIZE$4K);
    sendState(buffer);
}

void BaseClient::sendControllerState() {
    controllerHandler.pushControllerState();
    serializeJsonPretty(controllerHandler.getControllerState().getAsJson(), buffer, $SYSTEM.SIZE$4K);
    sendControllerState(buffer);
}

void BaseClient::processMessage(const char* message, const bool& checkControllerId) {
    JsonDocument jsonMessage;
    DeserializationError error = deserializeJson(jsonMessage, message);
    if (error == DeserializationError::Ok) {
        if (checkControllerId) {
            // if jsonMessage[jsonSchema.ID_WORD] is not exist or (*dataExchangeJson)[jsonSchema.ID_WORD] is not equal jsonMessage[jsonSchema.ID_WORD]
            if (!jsonMessage[JSON$MESSAGE.ID].is<const char*>() || !equal(controllerHandler.getId(), jsonMessage[JSON$MESSAGE.ID].as<const char*>())) {
                // push error and return
                log(INFO, "BaseClient.processMessage", "controller is not identified", message);
                return;
            }
        }
        // do not process without message_id
        if (!jsonMessage[JSON$MESSAGE.MESSAGE_ID].is<int>()) {
            log(ERROR, "BaseClient.processMessage", "message do not have an ID", message);
            return;
        }
        int messageId = jsonMessage[JSON$MESSAGE.MESSAGE_ID].as<int>();
        JsonDocument response;
        // send state and empty response-message if request isn't an array
        if (!jsonMessage[JSON$MESSAGE.REQUEST].is<JsonArray>()) {
            sendState();
            sendResponse(messageId, response.to<JsonObject>());
            return;
        }
        JsonArray responseHolder = response[JSON$MESSAGE.RESPONSE].to<JsonArray>();
        bool doReboot = false;
        for (JsonVariant request : jsonMessage[JSON$MESSAGE.REQUEST].as<JsonArray>()) {
            if (request.is<JsonObject>()) {
                int res = processRequest(request[JSON$MESSAGE.NAME].as<const char*>(), request[JSON$MESSAGE.VALUE].as<JsonVariant>(), responseHolder, doReboot);
                if (logLevel <= INFO && res != $MESSAGE.RESPONSE$OK) {
                    char req[$SYSTEM.SIZE$1K];
                    serializeJson(request, req);
                    if (res == $MESSAGE.RESPONSE$FAIL) {
                        log(INFO, "BaseClient.processMessage", "failed request processing", req);
                    } else {
                        log(WARNING, "BaseClient.processMessage", "unknown request", req);
                    }
                }
            }
            // response = request's name + result, request value can be any type, depending on the request name
        }
        sendResponse(messageId, response.as<JsonObject>());
        if (doReboot) controllerHandler.reboot();
    } else {
        if (error == DeserializationError::EmptyInput)
            log(ERROR, "BaseClient.processMessage", "message is empty", message);
        else if (error == DeserializationError::IncompleteInput)
            log(ERROR, "BaseClient.processMessage", "message is not complete or too big", message);
        else if (error == DeserializationError::NoMemory)
            log(ERROR, "BaseClient.processMessage", "message is too big or controller has no memory", message);
        else if (error == DeserializationError::TooDeep)
            log(ERROR, "BaseClient.processMessage", "message is not complete or too big", message);
        else if (error == DeserializationError::InvalidInput)
            log(ERROR, "BaseClient.processMessage", "message is invalid or is not a json", message);
        else
            log(ERROR, "BaseClient.processMessage", "massage processing finished with unknown error", message);
    }
}

int BaseClient::processRequest(const char* name, JsonVariant value, JsonArray responseHolder, bool& doReboot) {
    int res = $MESSAGE.RESPONSE$UNDEFINED;
    if (name != nullptr) {
        // set data
        if (equal($MESSAGE.REQUEST$SET_DATA, name)) {
            if (value.is<JsonObject>()) {
                // object style data-set
                char key[4];
                for (int i = 0; i < $PORT.COUNT; ++i) {
                    snprintf(key, 4, "%d", i);
                    if (value[key].is<int>())
                        storage.getPortState().setPortData(i, value[key].as<int>());
                }
                portHandler.pullState();
                storage.backupState();
            } else if (value.is<JsonArray>()) {
                // array style data-set
                storage.getPortState().setData(value.as<JsonArray>());
                portHandler.pullState();
                storage.backupState();
            }  // else treat like a simple request to fetch the data
            sendState();
            res = $MESSAGE.RESPONSE$OK;
            // set modes
        } else if (equal($MESSAGE.REQUEST$SET_MODES, name)) {
            // only array with full modes is supported
            if (value.is<JsonArray>()) {
                storage.getPortState().setModes(value.as<JsonArray>());
                portHandler.pullState();
                storage.backupState();
                res = $MESSAGE.RESPONSE$OK;
            } else {
                res = $MESSAGE.RESPONSE$FAIL;
            }
        } else if (equal($MESSAGE.REQUEST$CONFIGURE_NETWORK, name)) {
            if (value.is<JsonObject>()) {
                // connection config
                storage.getConnectionConfiguration().updateFromJson(value.as<JsonObject>());
                res = $MESSAGE.RESPONSE$OK;
                storage.backupConfiguration();
                doReboot = true;
            } else {
                res = $MESSAGE.RESPONSE$FAIL;
            }
        } else if (equal($MESSAGE.REQUEST$CONFIGURE_SERVER, name)) {
            if (value.is<JsonObject>()) {
                // server config
                storage.getServerConfiguration().updateFromJson(value.as<JsonObject>());
                res = $MESSAGE.RESPONSE$OK;
                storage.backupConfiguration();
                doReboot = true;
            } else {
                res = $MESSAGE.RESPONSE$FAIL;
            }
        } else if (equal($MESSAGE.REQUEST$REBOOT, name)) {
            res = $MESSAGE.RESPONSE$OK;
            doReboot = true;
        } else if (equal($MESSAGE.REQUEST$SEND_CONTROLLER_STATE, name)) {
            res = $MESSAGE.RESPONSE$OK;
            sendControllerState();
        } else if (equal($MESSAGE.REQUEST$MAKE_BACKUP, name)) {
            storage.backupConfiguration();
            storage.backupState();
            res = $MESSAGE.RESPONSE$OK;
        } else if (equal($MESSAGE.REQUEST$CONFIGURE_CONTROLLER, name)) {
            if (value.is<JsonObject>()) {
                // controller config
                ControllerConfiguration &controllerConfiguration = storage.getControllerConfiguration();
                controllerConfiguration.updateFromJson(value.as<JsonObject>());
                logLevel = controllerConfiguration.getLogLevel();
                res = $MESSAGE.RESPONSE$OK;
                storage.backupConfiguration();
            } else {
                res = $MESSAGE.RESPONSE$FAIL;
            }
        }
        JsonObject response = responseHolder.add<JsonObject>();
        response[JSON$MESSAGE.NAME] = name;
        response[JSON$MESSAGE.RESULT] = res;
    }
    return res;
}

void BaseClient::sendResponse(const int& messageIdentity, JsonObject responseHolder) {
    responseHolder[JSON$MESSAGE.TIMESTAMP] = millis();
    responseHolder[JSON$MESSAGE.MESSAGE_ID] = messageIdentity;
    serializeJsonPretty(responseHolder, buffer, $SYSTEM.SIZE$4K);
    sendResponse(buffer);
}

void BaseClient::log(const LogLevel& level, const char* module, const char* message, const char* details) {
    unsigned long timestamp = millis();
    if (level >= logLevel && (module || message || details)) {
        JsonDocument log;
        char buffer[$SYSTEM.SIZE$4K];
        const char* _level;
        switch (level) {
            case DEBUG:
                _level = $LOG.DEBUG$STRING;
                break;
            case INFO:
                _level = $LOG.INFO$STRING;
                break;
            case WARNING:
                _level = $LOG.WARNING$STRING;
                break;
            case ERROR:
                _level = $LOG.ERROR$STRING;
                break;
            default:
                break;
        }
        log[JSON$MESSAGE.TIMESTAMP] = timestamp;
        log[JSON$LOG.LEVEL] = _level;
        if (module) log[JSON$LOG.MODULE] = module;
        if (message) log[JSON$LOG.MESSAGE] = message;
        if (details) log[JSON$LOG.CAUSE] = details;
        serializeJsonPretty(log, buffer);
        sendLog(buffer);
    }
}

BaseClient::BaseClient(InternalStorage& storage, ControllerHandler& controllerHandler, PortHandler& portHandler)
    : storage(storage), controllerHandler(controllerHandler), portHandler(portHandler) {
    logLevel = storage.getControllerConfiguration().getLogLevel();
}

void BaseClient::loop() {
    for (;;) step();
}
