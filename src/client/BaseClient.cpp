#include "client/BaseClient.h"

BaseClient::BaseClient(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, InternalStorage &storage, ControllerHandler &controllerHandler, PortHandler &portHandler)
    : dataExchangeJson(dataExchangeJson), jsonSchema(jsonSchema), storage(storage), controllerHandler(controllerHandler), portHandler(portHandler) {}

void BaseClient::pullMessageFrom(const char *message, const bool &checkId) {
    int hashCode = pulledMessageHashCodeFrom(message);
    JsonDocument jsonMessage;
    DeserializationError error = deserializeJson(jsonMessage, message);
    if (error == DeserializationError::Ok) {
        if (checkId) {
            //if jsonMessage[jsonSchema.ID_WORD] is not exist or (*dataExchangeJson)[jsonSchema.ID_WORD] is not equal jsonMessage[jsonSchema.ID_WORD]
            if(!jsonMessage[jsonSchema.ID_WORD].is<const char*>() || strcmp((*dataExchangeJson)[jsonSchema.ID_WORD].as<const char *>(), jsonMessage[jsonSchema.ID_WORD].as<const char *>()) != 0) {
                //push error and return
                pushPullingResponse(hashCode, "message is not identified");
                return;
            }
        }

        if (jsonMessage[jsonSchema.MODES_WORD].is<JsonObject>()) {
            (*dataExchangeJson)[jsonSchema.MODES_WORD] = jsonMessage[jsonSchema.MODES_WORD].as<JsonObject>();
            portHandler.pullModes();
            storage.saveModes();
        }
        if (jsonMessage[jsonSchema.STATE_WORD].is<JsonObject>()) {
            (*dataExchangeJson)[jsonSchema.STATE_WORD] = jsonMessage[jsonSchema.STATE_WORD].as<JsonObject>();
            portHandler.pullState();
            storage.saveState();
        }
        if (jsonMessage[jsonSchema.CONFIG_WORD].is<JsonObject>()) {
            (*dataExchangeJson)[jsonSchema.CONFIG_WORD] = jsonMessage[jsonSchema.CONFIG_WORD].as<JsonObject>();
            storage.saveConfiguration();
            controllerHandler.reboot();
        }
        portHandler.pullAndPushState();
        pushMessage();
    } else if (error == DeserializationError::EmptyInput)
        pushPullingResponse(hashCode, "message is empty");
    else if (error == DeserializationError::IncompleteInput)
        pushPullingResponse(hashCode, "message is not complete or too big");
    else if (error == DeserializationError::NoMemory)
        pushPullingResponse(hashCode, "message is too big or controller has no memory");
    else if (error == DeserializationError::TooDeep)
        pushPullingResponse(hashCode, "message has no-conventional structure or is too deep");
    else if (error == DeserializationError::InvalidInput)
        pushPullingResponse(hashCode, "message is invalid or is not a json");
    else pushPullingResponse(hashCode, "massage processing has unknown error");
}

void BaseClient::pushPullingResponse(int messageHashCode, const char *response) {
    JsonDocument json;
    json[jsonSchema.MESSAGE_HASH_WORD] = messageHashCode;
    json[jsonSchema.MESSAGE_RESPONSE] = response;
    char buffer[256];
    serializeJsonPretty(json, buffer);
    pushPullingResponce(buffer);
}

// Java's hashCode
int BaseClient::pulledMessageHashCodeFrom(const char *message) {
    int hashCode = 0;
    while (*message) {
        hashCode = 31 * hashCode + (unsigned char)(*message);
        message++;
    }
    return hashCode;
}