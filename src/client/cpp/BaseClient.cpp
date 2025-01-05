#include "client/BaseClient.h"

void BaseClient::sendState() {
    portHandler.pushState();
    serializeJson(storage.getPortState().getAsJson(), buffer, $SYSTEM.SIZE$4K);
    sendState(buffer);
}

void BaseClient::sendControllerState() {
    serializeJsonPretty(controllerState.getAsJson(), buffer, $SYSTEM.SIZE$4K);
    sendControllerState(buffer);
}

void BaseClient::processMessage(const char* message) {
    JsonDocument jsonMessage;
    DeserializationError error = deserializeJson(jsonMessage, message);
    if (error == DeserializationError::Ok) {
        // do not process without message_id
        if (!jsonMessage[JSON$MESSAGE.MESSAGE_ID].is<int>()) {
            log(ERROR, "CLIENT.MESSAGE", "Message doesn't have the ID", message);
            return;
        }
        int messageId = jsonMessage[JSON$MESSAGE.MESSAGE_ID].as<int>();
        JsonDocument responseMessage;
        // send state and empty response-message if request isn't an array, log
        if (!jsonMessage[JSON$MESSAGE.REQUEST].is<JsonArray>()) {
            log(ERROR, "CLIENT.MESSAGE", "Message doesn't have the request's array", message);
            sendResponse(messageId, responseMessage.to<JsonObject>());
            return;
        }
        JsonArray responsesArray = responseMessage[JSON$MESSAGE.RESPONSE].to<JsonArray>();
        bool doReboot = false;
        for (JsonVariant request : jsonMessage[JSON$MESSAGE.REQUEST].as<JsonArray>()) {
            if (request.is<JsonObject>()) {
                int res = processRequest(request[JSON$MESSAGE.NAME].as<const char*>(), request[JSON$MESSAGE.VALUE].as<JsonVariant>(), responsesArray, doReboot);
                if (logLevel <= INFO && res != $MESSAGE.RESPONSE$OK) {
                    char req[$SYSTEM.SIZE$1K];
                    serializeJson(request, req);
                    if (res == $MESSAGE.RESPONSE$FAIL) {
                        log(WARNING, "CLIENT.MESSAGE.REQUEST", "Request wasn't processed", req);
                    } else {
                        log(ERROR, "CLIENT.MESSAGE.REQUEST", "Request isn't known", req);
                    }
                }
            }
            // response = request's name + result, request value can be any type, depending on the request name
        }
        sendResponse(messageId, responseMessage.as<JsonObject>());
        if (doReboot) reboot();
    } else {
        if (error == DeserializationError::EmptyInput)
            log(ERROR, "CLIENT.MESSAGE", "Message is empty", message);
        else if (error == DeserializationError::IncompleteInput)
            log(ERROR, "CLIENT.MESSAGE", "Message isn't complete or is too big", message);
        else if (error == DeserializationError::NoMemory)
            log(ERROR, "CLIENT.MESSAGE", "Message is too big or the controller is out of memory", message);
        else if (error == DeserializationError::TooDeep)
            log(ERROR, "CLIENT.MESSAGE", "Message has reached the limit of nested objects", message);
        else if (error == DeserializationError::InvalidInput)
            log(ERROR, "CLIENT.MESSAGE", "Message is invalid or isn't a json", message);
        else
            log(ERROR, "CLIENT.MESSAGE", "Message processing has been finished with an unknown error", message);
    }
}

int BaseClient::processRequest(const char* name, JsonVariant value, JsonArray responseHolder, bool& doReboot) {
    // too big method, do refactoring later
    int res = $MESSAGE.RESPONSE$UNDEFINED;
    if (name != nullptr) {
        // set data
        if (equal($MESSAGE.REQUEST$SET_DATA, name)) {
            PortState &portState = storage.getPortState();
            if (value.is<JsonObject>()) {
                // object style data-set
                char key[4];
                for (int i = 0; i < $PORT.COUNT; ++i) {
                    snprintf(key, 4, "%d", i);
                    if (value[key].is<int>())
                        portState.setPortData(i, value[key].as<int>());
                }
                portHandler.pullState();
                storage.backupState();
                res = $MESSAGE.RESPONSE$OK;
            } else if (value.is<JsonArray>()) {
                // array style data-set
                portState.setData(value.as<JsonArray>());
                portHandler.pullState();
                storage.backupState();
                res = $MESSAGE.RESPONSE$OK;
            }  else {
                res = $MESSAGE.RESPONSE$FAIL;
            }
            sendState();
            // set modes
        } else if (equal($MESSAGE.REQUEST$SET_MODES, name)) {
            PortState &portState = storage.getPortState();
            if (value.is<JsonObject>()) {
                // object style data-set
                char key[4];
                for (int i = 0; i < $PORT.COUNT; ++i) {
                    snprintf(key, 4, "%d", i);
                    if (value[key].is<int>())
                        portState.setPortMode(i, value[key].as<int>());
                }
                portHandler.pullState();
                storage.backupState();
                res = $MESSAGE.RESPONSE$OK;
            } else if (value.is<JsonArray>()) {
                // array style mode-set
                portState.setModes(value.as<JsonArray>());
                portHandler.pullState();
                storage.backupState();
                res = $MESSAGE.RESPONSE$OK;
            } else {
                res = $MESSAGE.RESPONSE$FAIL;
            }
            sendState();
        } else if (equal($MESSAGE.REQUEST$CONFIGURE_NETWORK, name)) {
            if (value.is<JsonObject>()) {
                // connection config
                storage.getConnectionConfiguration().updateFromJson(value.as<JsonObject>());
                storage.backupConfiguration();
                doReboot = true;
                res = $MESSAGE.RESPONSE$OK;
            } else {
                res = $MESSAGE.RESPONSE$FAIL;
            }
        } else if (equal($MESSAGE.REQUEST$CONFIGURE_SERVER, name)) {
            if (value.is<JsonObject>()) {
                // server config
                storage.getServerConfiguration().updateFromJson(value.as<JsonObject>());
                storage.backupConfiguration();
                doReboot = true;
                res = $MESSAGE.RESPONSE$OK;
            } else {
                res = $MESSAGE.RESPONSE$FAIL;
            }
        } else if (equal($MESSAGE.REQUEST$REBOOT, name)) {
            doReboot = true;
            res = $MESSAGE.RESPONSE$OK;
        } else if (equal($MESSAGE.REQUEST$SEND_CONTROLLER_STATE, name)) {
            sendControllerState();
            res = $MESSAGE.RESPONSE$OK;
        } else if (equal($MESSAGE.REQUEST$MAKE_BACKUP, name)) {
            storage.backupConfiguration();
            storage.backupState();
            res = $MESSAGE.RESPONSE$OK;
        } else if (equal($MESSAGE.REQUEST$CONFIGURE_CONTROLLER, name)) {
            if (value.is<JsonObject>()) {
                // controller config
                ControllerConfiguration& controllerConfiguration = storage.getControllerConfiguration();
                controllerConfiguration.updateFromJson(value.as<JsonObject>());
                logLevel = controllerConfiguration.getLogLevel();
                storage.backupConfiguration();
                res = $MESSAGE.RESPONSE$OK;
            } else {
                res = $MESSAGE.RESPONSE$FAIL;
            }
        } else if (equal($MESSAGE.REQUEST$SEND_STATE, name)) {
            sendState();
            res = $MESSAGE.RESPONSE$OK;
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

BaseClient::BaseClient(InternalStorage& storage, ControllerState& controllerState, PortHandler& portHandler)
    : storage(storage), controllerState(controllerState), portHandler(portHandler) {
    byte mac_base[6] = {0};
    esp_efuse_mac_get_default(mac_base);
    snprintf(id, sizeof(id), "%d%d%d%d%d%d", mac_base[0] ^ 127, mac_base[1] ^ 127, mac_base[2] ^ 127, mac_base[3] ^ 127, mac_base[4] ^ 127, mac_base[5] ^ 127);
    logLevel = storage.getControllerConfiguration().getLogLevel();
    controllerState.setLastRebootReason(esp_reset_reason());
}

void BaseClient::step() {
    if (millis() - lastStateSend >= storage.getControllerConfiguration().getTransmissionInterval()) {
        sendState();
        lastStateSend = millis();
    }
}

bool BaseClient::initialize() {
    log(INFO, "CLIENT.INIT", "Successfully initialized", nullptr);
    sendControllerState();
    sendState();
    return true;
}

void BaseClient::reboot() {
    // replace with RTOS-delayed task later
    esp_restart();
}
