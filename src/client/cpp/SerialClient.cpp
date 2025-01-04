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

void SerialClient::sendLog(const char *log) {
    send(log);
}

SerialClient::SerialClient(InternalStorage &storage, ControllerState &controllerState, PortHandler &portHandler, HardwareSerial &serial)
    : BaseClient(storage, controllerState, portHandler), serial(serial) {}

bool SerialClient::initialize() {
    serial.begin($NETWORK.SERIAL$BAUD_RATE);
    storage.restoreConfiguration();
    unsigned long start = millis();
    while (!serial && millis() - start < 1000) { /*wait untill ready plus 2 seconds*/
    }
    while (serial.available() > 0) {
        serial.read();  // clear any garbage data
    }
    return true;
}

void SerialClient::step() {
    if (serial.available() > 0) {
        int i = 0;
        while (serial.available() > 0 && i < $SYSTEM.SIZE$4K) {
            buffer[i++] = (char)serial.read();
        }
        buffer[i > $SYSTEM.SIZE$4K ? i - 1 : i] = '\0';
        if (unlocked) {
            processMessage(buffer);
        } else {
            unlocked = equal(buffer, id);
            if(unlocked) log(INFO, "SERIAL_CLIENT", "Access unlocked", nullptr);
            else log(ERROR, "SERIAL_CLIENT", "Access denied", nullptr);
        }
    } else if(unlocked) {
        BaseClient::step();
    }
}
