#include "BaseClient.h"

void BaseClient::sendState() {
    portHandler.pushState();
    char buffer[512];
    serializeJsonPretty((*dataExchangeJson)[jsonSchema.STATE_WORD], buffer);
    sendState(buffer);
}

void BaseClient::sendControllerState() {
    controllerHandler.insertControllerState();
    char buffer[512];
    serializeJsonPretty((*dataExchangeJson)[jsonSchema.CONTROLLER_WORD], buffer);
    sendControllerState(buffer);
}

void BaseClient::processMessage(const char* message, const bool& checkControllerId) {
    int messageId = 0;
    int hashCode = calculateHashCode(message);
    JsonDocument jsonMessage;
    DeserializationError error = deserializeJson(jsonMessage, message);
    if (error == DeserializationError::Ok) {
        if (checkControllerId) {
            // if jsonMessage[jsonSchema.ID_WORD] is not exist or (*dataExchangeJson)[jsonSchema.ID_WORD] is not equal jsonMessage[jsonSchema.ID_WORD]
            if (!jsonMessage[jsonSchema.ID_WORD].is<const char*>() || !equals((*dataExchangeJson)[jsonSchema.ID_WORD].as<const char*>(), jsonMessage[jsonSchema.ID_WORD].as<const char*>())) {
                // push error and return
                sendError(messageId, hashCode, "not_identified", "controller is not identified");
                return;
            }
        }
        if (!jsonMessage[jsonSchema.MESSAGE_ID_WORD].is<int>()) {
            sendError(messageId, hashCode, "not_identified", "message is not identified");
            return;
        }
        messageId = jsonMessage[jsonSchema.MESSAGE_ID_WORD].as<int>();
        JsonDocument response;
        if (!jsonMessage[jsonSchema.REQUEST_WORD].is<JsonArray>()) {
            sendState();
            sendResponse(messageId, hashCode, &response);
            return;
        }
        JsonArray responseHolder = response[jsonSchema.RESPONSE_WORD].to<JsonArray>();
        bool doReboot = false;
        for (JsonVariant request : jsonMessage[jsonSchema.REQUEST_WORD].as<JsonArray>()) {
            if (request.is<JsonObject>())
                processRequest(request[jsonSchema.NAME_WORD].as<const char*>(), request[jsonSchema.VALUE_WORD].as<JsonVariant>(), &responseHolder, doReboot);
        }
        sendResponse(messageId, hashCode, &response);
        if (doReboot) controllerHandler.reboot();
    } else if (error == DeserializationError::EmptyInput)
        sendError(messageId, hashCode, "message_processing", "message is empty");
    else if (error == DeserializationError::IncompleteInput)
        sendError(messageId, hashCode, "message_processing", "message is not complete or too big");
    else if (error == DeserializationError::NoMemory)
        sendError(messageId, hashCode, "message_processing", "message is too big or controller has no memory");
    else if (error == DeserializationError::TooDeep)
        sendError(messageId, hashCode, "message_processing", "message has no-conventional structure or is too deep");
    else if (error == DeserializationError::InvalidInput)
        sendError(messageId, hashCode, "message_processing", "message is invalid or is not a json");
    else
        sendError(messageId, hashCode, "message_processing", "massage processing has unknown error");
}

int BaseClient::calculateHashCode(const char* message) {
    int hashCode = 0;
    while (*message) {
        hashCode = 31 * hashCode + (unsigned char)(*message);
        message++;
    }
    return hashCode;
}

void BaseClient::processRequest(const char* name, const JsonVariant& values, JsonArray* responseHolder, bool& doReboot) {
    if (name != nullptr) {
        JsonDocument response;
        response[jsonSchema.NAME_WORD] = name;
        if (equals(jsonSchema.STATE_WORD, name)) {
            if (values.is<JsonObject>()) {
                (*dataExchangeJson)[jsonSchema.STATE_WORD] = values;
                portHandler.pullState();
                storage.saveState();
                response[jsonSchema.RESULT_WORD] = 1;
            } else
                response[jsonSchema.RESULT_WORD] = 0;
        } else if (equals(jsonSchema.MODES_WORD, name)) {
            if (values.is<JsonObject>()) {
                (*dataExchangeJson)[jsonSchema.MODES_WORD] = values;
                portHandler.pullModes();
                storage.saveModes();
                response[jsonSchema.RESULT_WORD] = 1;
            } else {
                response[jsonSchema.RESULT_WORD] = 0;
            }
        } else if (equals(jsonSchema.CONFIG_WORD, name)) {
            if (values.is<JsonObject>()) {
                (*dataExchangeJson)[jsonSchema.MODES_WORD] = values;
                storage.saveAll();
                response[jsonSchema.RESULT_WORD] = 1;
                doReboot = true;
            } else {
                response[jsonSchema.RESULT_WORD] = 0;
            }
        } else if (equals("reboot", name)) {
            response[jsonSchema.RESULT_WORD] = 1;
            doReboot = true;
        } else if (equals(jsonSchema.CONTROLLER_WORD, name)) {
            response[jsonSchema.RESULT_WORD] = 1;
            sendControllerState();
        } else {
            //your 'name' request is not supported yet
            response[jsonSchema.RESULT_WORD] = -1;
        }
        /*
        result: 0 - request is not sucessful
        result: 1 - request is  sucessful
        result: -1 - request is unknown
        */
        (*responseHolder).add(response);
    }
}

void BaseClient::sendResponse(const int& messageIdentity, const int& messageHash, JsonDocument* response) {
    (*response)[jsonSchema.MESSAGE_ID_WORD] = messageIdentity;
    (*response)[jsonSchema.MESSAGE_HASH_WORD] = messageHash;
    char buffer[1024];
    serializeJsonPretty((*response), buffer);
    sendResponse(buffer);
}

void BaseClient::sendError(const int& messageId, const int& messageHash, const char* errorType, const char* details) {
    JsonDocument json;
    json[jsonSchema.MESSAGE_ID_WORD] = messageId;
    json[jsonSchema.MESSAGE_HASH_WORD] = messageHash;
    json[jsonSchema.TYPE_WORD] = errorType;
    json[jsonSchema.DETAILS_WORD] = details;
    char buffer[256];
    serializeJsonPretty(json, buffer);
    sendResponse(buffer);
}

bool BaseClient::equals(const char* s1, const char* s2) {
    return strcmp(s1, s2) == 0;
}

BaseClient::BaseClient(JsonDocument* dataExchangeJson, const JsonSchema& jsonSchema, InternalStorage& storage, ControllerHandler& controllerHandler, PortHandler& portHandler)
    : dataExchangeJson(dataExchangeJson), jsonSchema(jsonSchema), storage(storage), controllerHandler(controllerHandler), portHandler(portHandler) {}

void BaseClient::loop() {
    for (;;) step();
}
