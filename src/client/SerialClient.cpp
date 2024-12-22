#include "client/SerialClient.h"

// when esp32 send gibberish stuff to the serial, simply check every T in the stream of [T]\n#END#\n[T]\n#END#\n[T]n#END#\n
void SerialClient::send(const char *data) {
    serial.write(data);
    serial.write(DIVIDER);
    serial.flush();
}

void SerialClient::sendState(const char *state) {
    send(state);
}

void SerialClient::sendControllerState(const char *controllerState) {
    send(controllerState);
}

void SerialClient::sendResponse(const char *response) {
    send(response);
}

SerialClient::SerialClient(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, InternalStorage &storage, ControllerHandler &controllerHandler, PortHandler &portHandler, HardwareSerial &serial)
    : BaseClient(dataExchangeJson, jsonSchema, storage, controllerHandler, portHandler), serial(serial) {}

bool SerialClient::initialize() {
    storage.readConfiguration();
    serial.begin(38400);
    unsigned long start = millis();
    while (!serial && millis() - start < 1000) { /*wait untill ready plus 2 seconds*/
    }
    while (serial.available() > 0) {
        serial.read();  //clear any garbage data
    }
    return true;
}

void SerialClient::step() {
    if (serial.available() > 0) {
        int length = 512;
        char buffer[length];
        int i = 0;
        while (serial.available() > 0 && i < length) {
            buffer[i++] = (char) serial.read();
        }
        buffer[i > length ? i - 1 : i] = '\0';
        processMessage(buffer, true);
    }
}
