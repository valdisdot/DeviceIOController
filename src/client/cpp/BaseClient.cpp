#include "client/BaseClient.h"

void BaseClient::sendState() {
    portHandler.pushState();
    char buffer[CONSTANT.SIZE_1K];
    serializeJson(storage.getPortState().getAsJson(), buffer, CONSTANT.SIZE_1K);
    sendState(buffer);
}

void BaseClient::sendControllerState() {
    controllerHandler.pushControllerState();
    char buffer[CONSTANT.SIZE_1K];
    serializeJsonPretty(controllerHandler.getControllerState().getAsJson(), buffer, CONSTANT.SIZE_1K);
    sendControllerState(buffer);
}

void BaseClient::processMessage(const char* message, const bool& checkControllerId) {
    int messageId = 0;
    int _hashCode = hashCode(message);
    JsonDocument jsonMessage;
    DeserializationError error = deserializeJson(jsonMessage, message);
    if (error == DeserializationError::Ok) {
        if (checkControllerId) {
            // if jsonMessage[jsonSchema.ID_WORD] is not exist or (*dataExchangeJson)[jsonSchema.ID_WORD] is not equal jsonMessage[jsonSchema.ID_WORD]
            if (!jsonMessage[SCHEMA_BASE.ID].is<const char*>() || !equal(controllerHandler.getId(), jsonMessage[SCHEMA_BASE.ID].as<const char*>())) {
                // push error and return
                sendError(messageId, _hashCode, "not_identified", "controller is not identified");
                return;
            }
        }
        // do not process without message_id
        if (!jsonMessage[SCHEMA_MESSAGE.MESSAGE_ID].is<int>()) {
            sendError(messageId, _hashCode, "not_identified", "message is not identified");
            return;
        }
        messageId = jsonMessage[SCHEMA_MESSAGE.MESSAGE_ID].as<int>();
        JsonDocument response;
        // send state and empty response-message if request isn't an array
        if (!jsonMessage[SCHEMA_MESSAGE.REQUEST].is<JsonArray>()) {
            sendState();
            sendResponse(messageId, _hashCode, response.to<JsonObject>());
            return;
        }
        JsonArray responseHolder = response[SCHEMA_MESSAGE.RESPONSE].to<JsonArray>();
        bool doReboot = false;
        for (JsonVariant request : jsonMessage[SCHEMA_MESSAGE.REQUEST].as<JsonArray>()) {
            // do not process if requests array element isn't an object
            if (request.is<JsonObject>())
                // response = request's name + result, request value can be any type, depending on the request name
                processRequest(request[SCHEMA_MESSAGE.NAME].as<const char*>(), request[SCHEMA_MESSAGE.VALUE].as<JsonVariant>(), responseHolder, doReboot);
        }
        sendResponse(messageId, _hashCode, response.as<JsonObject>());
        if (doReboot) controllerHandler.reboot();
    } else if (error == DeserializationError::EmptyInput)
        sendError(messageId, _hashCode, "message_processing", "message is empty");
    else if (error == DeserializationError::IncompleteInput)
        sendError(messageId, _hashCode, "message_processing", "message is not complete or too big");
    else if (error == DeserializationError::NoMemory)
        sendError(messageId, _hashCode, "message_processing", "message is too big or controller has no memory");
    else if (error == DeserializationError::TooDeep)
        sendError(messageId, _hashCode, "message_processing", "message has no-conventional structure or is too deep");
    else if (error == DeserializationError::InvalidInput)
        sendError(messageId, _hashCode, "message_processing", "message is invalid or is not a json");
    else
        sendError(messageId, _hashCode, "message_processing", "massage processing has unknown error");
}

void BaseClient::processRequest(const char* name, JsonVariant values, JsonArray responseHolder, bool& doReboot) {
    if (name != nullptr) {
        JsonDocument response;
        response[SCHEMA_MESSAGE.NAME] = name;
        // set data
        if (equal(REQUEST_TYPE.SET_DATA, name)) {
            if (values.is<JsonObject>()) {
                // object style data-set
                char key[3];
                for (int i = 0; i < CONSTANT.PORT_COUNT; ++i) {
                    snprintf(key, 3, "%d", i);
                    if (values[key].is<int>())
                        storage.getPortState().setPortData(i, values[key].as<int>());
                }
                portHandler.pullState();
                storage.backupState();
            } else if (values.is<JsonArray>()) {
                // array style data-set
                storage.getPortState().setData(values.as<JsonArray>());
                portHandler.pullState();
                storage.backupState();
            }  // else treat like a simple request to fetch the data
            sendState();
            response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_OK;
            // set modes
        } else if (equal(REQUEST_TYPE.SET_MODES, name)) {
            // only array with full modes is supported
            if (values.is<JsonArray>()) {
                storage.getPortState().setModes(values.as<JsonArray>());
                portHandler.pullState();
                storage.backupState();
                response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_OK;
            } else {
                response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_FAIL;
            }
        } else if (equal(REQUEST_TYPE.CONFIGURE_CONNECTION, name)) {
            if (values.is<JsonObject>()) {
                //connection config
                storage.getConnectionConfiguration().updateFromJson(values.as<JsonObject>());
                response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_OK;
                storage.backupConfiguration();
                doReboot = true;
            } else {
                response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_FAIL;
            }
        } else if (equal(REQUEST_TYPE.CONFIGURE_SERVER, name)) {
            if (values.is<JsonObject>()) {
                //server config
                storage.getServerConfiguration().updateFromJson(values.as<JsonObject>());
                response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_OK;
                storage.backupConfiguration();
                doReboot = true;
            } else {
                response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_FAIL;
            }
        } else if (equal(REQUEST_TYPE.REBOOT, name)) {
            response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_OK;
            doReboot = true;
        } else if (equal(REQUEST_TYPE.SEND_CONTROLLER_STATE, name)) {
            response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_OK;
            sendControllerState();
        } else if (equal(REQUEST_TYPE.MAKE_BACKUP, name)) {
            response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_OK;
            storage.backupConfiguration();
            storage.backupState();
        } else {
            response[SCHEMA_MESSAGE.RESULT] = CONSTANT.RESPONSE_UNDEFINED;
            if(DEBUG_MODE) {
                char buffer[CONSTANT.SIZE_2K];
                JsonDocument doc;
                controllerHandler.pushControllerState();
                portHandler.pushState();
                doc[SCHEMA_BASE.ID] = controllerHandler.getId();
                doc[SCHEMA_STATE.MODES] = storage.getPortState().getModesAsJson();
                doc[SCHEMA_STATE.DATA] = storage.getPortState().getDataAsJson();
                doc[SCHEMA_BASE.CONTROLLER] = controllerHandler.getControllerState().getAsJson();
                JsonObject config = doc[SCHEMA_BASE.CONFIGURATION].to<JsonObject>();
                config[SCHEMA_CONNECTION_CONFIGURATION.ROOT] = storage.getConnectionConfiguration().getAsJson();
                config[SCHEMA_SERVER_CONFIGURATION.ROOT] = storage.getServerConfiguration().getAsJson();
                serializeJsonPretty(doc, buffer, CONSTANT.SIZE_2K);
                sendResponse(buffer);
            }
        } 
        responseHolder.add(response);
    }
}

void BaseClient::sendResponse(const int& messageIdentity, const int& messageHash, JsonObject responseHolder) {
    responseHolder[SCHEMA_MESSAGE.MESSAGE_ID] = messageIdentity;
    responseHolder[SCHEMA_MESSAGE.MESSAGE_HASH] = messageHash;
    char buffer[CONSTANT.SIZE_1K];
    serializeJsonPretty(responseHolder, buffer, CONSTANT.SIZE_1K);
    sendResponse(buffer);
}

void BaseClient::sendError(const int& messageId, const int& messageHash, const char* errorType, const char* details) {
    JsonDocument json;
    json[SCHEMA_MESSAGE.MESSAGE_ID] = messageId;
    json[SCHEMA_MESSAGE.MESSAGE_HASH] = messageHash;
    json[SCHEMA_MESSAGE.TYPE] = errorType;
    json[SCHEMA_MESSAGE.DETAILS] = details;
    char buffer[CONSTANT.SIZE_512];
    serializeJsonPretty(json, buffer, CONSTANT.SIZE_1K);
    sendResponse(buffer);
}

BaseClient::BaseClient(InternalStorage& storage, ControllerHandler& controllerHandler, PortHandler& portHandler)
    : storage(storage), controllerHandler(controllerHandler), portHandler(portHandler) {
}

void BaseClient::loop() {
    for (;;) step();
}
