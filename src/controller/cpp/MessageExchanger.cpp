#include "controller/MessageExchanger.h"

MessageExchanger::MessageExchanger(Connector &connector, Storage &storage, PortHandler &portHandler, Logger &logger) : connector(connector), storage(storage), portHandler(portHandler), logger(logger) {
}

void MessageExchanger::addRequestResolver(RequestResolver *requestResolver) {
    if(requestResolver) resolvers.put(requestResolver->getName(), requestResolver);
}

void MessageExchanger::init() {
    logger.log(INFO, "MESSAGE_EXCHANGER.INIT", "Successfully initialized", nullptr);
    sendControllerState();
    sendState();
}

void MessageExchanger::run() {
    connector.call();
    if (millis() - lastStateSend >= storage.getControllerConfiguration().getTransmissionInterval()) {
        sendState();
        lastStateSend = millis();
    }
}

void MessageExchanger::sendState() {
    portHandler.pushState();
    serializeJson(storage.getPortState().getAsJson(), buffer, $SYSTEM.SIZE$4K);
    connector.sendState(buffer);
}

void MessageExchanger::sendControllerState() {
    storage.getControllerState().setMemory(esp_get_free_heap_size());
    serializeJsonPretty(storage.getControllerState().getAsJson(), buffer, $SYSTEM.SIZE$4K);
    connector.sendControllerState(buffer);
}

void MessageExchanger::processMessage(const char *message) {
    JsonDocument jsonMessage;
    DeserializationError error = deserializeJson(jsonMessage, message);
    if (error == DeserializationError::Ok) {
        // do not process without message_id
        if (!jsonMessage[JSON$MESSAGE.MESSAGE_ID].is<int>()) {
            logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE", "Message doesn't have the ID", message);
            return;
        }
        int messageId = jsonMessage[JSON$MESSAGE.MESSAGE_ID].as<int>();
        JsonDocument responseMessage;
        // send state and empty response-message if request isn't an array, log
        if (!jsonMessage[JSON$MESSAGE.REQUEST].is<JsonArray>()) {
            logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE", "Message doesn't have the request's array", message);
            sendResponse(messageId, responseMessage.to<JsonObject>());
            return;
        }
        JsonArray responsesArray = responseMessage[JSON$MESSAGE.RESPONSE].to<JsonArray>();
        bool doReboot = false;
        for (JsonVariant request : jsonMessage[JSON$MESSAGE.REQUEST].as<JsonArray>()) {
            if (request.is<JsonObject>() && request[JSON$MESSAGE.NAME].is<const char *>()) {
                int res = $MESSAGE.RESPONSE$UNDEFINED;
                if (resolvers.containsKey(request[JSON$MESSAGE.NAME].as<const char *>())) {
                    res = (*resolvers.get(request[JSON$MESSAGE.NAME].as<const char *>()))->resolve(request[JSON$MESSAGE.VALUE].as<JsonVariant>());
                    if ((*resolvers.get(request[JSON$MESSAGE.NAME].as<const char *>()))->isRebootRequired()) doReboot = true;
                }
                JsonObject response = responsesArray.add<JsonObject>();
                response[JSON$MESSAGE.NAME] = request[JSON$MESSAGE.NAME].as<const char *>();
                response[JSON$MESSAGE.RESULT] = res;
                if (res != $MESSAGE.RESPONSE$OK) {
                    serializeJson(request, smallBuffer);
                    if (res == $MESSAGE.RESPONSE$FAIL) {
                        logger.log(WARNING, "MESSAGE_EXCHANGER.MESSAGE.REQUEST", "Request wasn't processed", smallBuffer);
                    } else {
                        logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE.REQUEST", "Request isn't known", smallBuffer);
                    }
                }
            } else {
                serializeJson(request, smallBuffer);
                logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE.REQUEST", "Request array's element is not a request object", smallBuffer);
            }
        }
        sendResponse(messageId, responseMessage.as<JsonObject>());
        if (doReboot) esp_restart();
    } else {
        if (error == DeserializationError::EmptyInput)
            logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE", "Message is empty", message);
        else if (error == DeserializationError::IncompleteInput)
            logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE", "Message isn't complete or is too big", message);
        else if (error == DeserializationError::NoMemory)
            logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE", "Message is too big or the controller is out of memory", message);
        else if (error == DeserializationError::TooDeep)
            logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE", "Message has reached the limit of nested objects", message);
        else if (error == DeserializationError::InvalidInput)
            logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE", "Message is invalid or isn't a json", message);
        else
            logger.log(ERROR, "MESSAGE_EXCHANGER.MESSAGE", "Message processing has been finished with an unknown error", message);
    }
}

void MessageExchanger::sendResponse(const int &messageIdentity, JsonObject responseHolder) {
    responseHolder[JSON$MESSAGE.TIMESTAMP] = millis();
    responseHolder[JSON$MESSAGE.MESSAGE_ID] = messageIdentity;
    serializeJsonPretty(responseHolder, buffer, $SYSTEM.SIZE$4K);
    connector.sendResponse(buffer);
}
