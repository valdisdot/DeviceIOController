#include "connector/SerialConnector.h"

// when esp32 send gibberish stuff to the serial, simply check every T in the stream of [T]\n#END#\n[T]\n#END#\n[T]n#END#\n
void SerialConnector::send(const char *data) {
    serial.write(data);
    serial.write(DIVIDER);
    serial.flush();
}

void SerialConnector::sendState(const char *state) {
    send(state);
}

void SerialConnector::sendControllerState(const char *controllerState) {
    send(controllerState);
}

void SerialConnector::sendResponse(const char *response) {
    send(response);
}

void SerialConnector::sendLog(const char *log) {
    send(log);
}

SerialConnector::SerialConnector(HardwareSerial &serial) : Connector($SYSTEM.SIZE$2K), serial(serial) {}

bool SerialConnector::init(std::function<void(const char *)> messageProcessor) {
    if (Connector::init(messageProcessor)) {
        serial.begin($NETWORK.SERIAL$BAUD_RATE);
        unsigned long start = millis();
        while (!serial && millis() - start < 1000) { /*wait untill ready plus 2 seconds*/}
        while (serial.available() > 0) {
            serial.read();  // clear any garbage data
        }
        return true;
    }
    return false;
}

bool SerialConnector::call() {
    if (serial.available() > 0) {
        int i = 0;
        while (serial.available() > 0 && i < $SYSTEM.SIZE$4K) {
            buffer[i++] = (char)serial.read();
        }
        buffer[i > $SYSTEM.SIZE$4K ? i - 1 : i] = '\0';
        if (unlocked) {
            this->messageProcessor(buffer);
        } else {
            unlocked = equal(buffer, controllerId);
            if (unlocked)
                send("Access granted");
            else
                send("Access denied");
        }
    }
    return true;
}