#include "client/SerialClient.h"

SerialClient::SerialClient(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, InternalStorage &storage, ControllerHandler &controllerHandler, PortHandler &portHandler, HardwareSerial &serial)
    : BaseClient(dataExchangeJson, jsonSchema, storage, controllerHandler, portHandler), serial(serial) {}

// Send responses via serial
void SerialClient::pushPullingResponce(const char *responseJson) {
    serial.print(responseJson);
}

// Push the state via Serial
void SerialClient::pushMessage() {
    char buffer[512];
    serializeJsonPretty((*dataExchangeJson)[jsonSchema.STATE_WORD], buffer, 512);
    serial.print(buffer);
}

bool SerialClient::initialize() {
    storage.readConfiguration();
    serial.begin(38400);
    unsigned long start = millis();
    while (!serial && millis() - start < 1000) { /*wait till ready and 2 seconds*/
    }
    while (serial.available() > 0) {
        serial.read();  // Clear any garbage data
    }
    return true;
}

void SerialClient::run() {
    if (serial.available() > 0) {
        int length = 256;
        char buffer[length];
        int i = 0;
        while (serial.available() > 0 && i < length) {
            buffer[i++] = (char) serial.read();
        }
        buffer[i > length ? i - 1 : i] = '\0';
        pullMessageFrom(buffer, true);
    }
}