#include "PortHandler.h"

PortHandler::PortHandler(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, const ControllerConstants &constants) : dataExchangeJson(dataExchangeJson), jsonSchema(jsonSchema), constants(constants) {
    currentState = new int[constants.LAST_PORT + 1];
    currentPortModes = new int[constants.LAST_PORT + 1];
    currentStatefulInput = new int[constants.LAST_PORT + 1];
    for (int i = 1; i <= constants.LAST_PORT; ++i) {
        currentState[i] = constants.NOT_INITIALIZED;
        currentPortModes[i] = constants.NOT_INITIALIZED;
        currentStatefulInput[i] = constants.NOT_INITIALIZED;
    }
}

void PortHandler::pullAndPushState() {
    pullState();
    pushState();
}

void PortHandler::pullModes() {
    if ((*dataExchangeJson)[jsonSchema.MODES_WORD].is<JsonObject>()) {
        JsonObject modes = (*dataExchangeJson)[jsonSchema.MODES_WORD].as<JsonObject>();
        int mode;
        char port[16];
        for (int i = 1; i <= constants.LAST_PORT; ++i) {
            snprintf(port, 16, "%s%d", jsonSchema.PORT_PREFIX, i);
            if (modes[port].is<signed int>())
                mode = modes[port].as<signed int>();
            else
                mode = constants.NOT_INITIALIZED;

            if (currentPortModes[i] != mode) {
                currentPortModes[i] = mode;
                currentState[i] = constants.NOT_INITIALIZED;
                if (mode == constants.NOT_INITIALIZED)
                    continue;
                else if (mode == constants.MODE_LOGICAL_INPUT || mode == constants.MODE_VALUE_INPUT)
                    pinMode(i, INPUT);
                else if (mode == constants.MODE_LOGICAL_OUTPUT || mode == constants.MODE_VALUE_INPUT)
                    pinMode(i, OUTPUT);
                else if (mode == constants.MODE_INVERSED_LOGICAL_INPUT || mode == constants.MODE_STATEFUL_LOGICAL_INPUT)
                    pinMode(i, INPUT_PULLUP);
            }
        }
    }
}

void PortHandler::pullState() {
    if ((*dataExchangeJson)[jsonSchema.STATE_WORD].is<JsonObject>()) {
        JsonObject states = (*dataExchangeJson)[jsonSchema.STATE_WORD].as<JsonObject>();
        char port[16];
        int mode;
        int value;
        for (int i = 1; i <= constants.LAST_PORT; ++i) {
            mode = currentPortModes[i];
            if (mode == constants.MODE_LOGICAL_OUTPUT || mode == constants.MODE_VALUE_OUTPUT) {
                snprintf(port, 16, "%s%d", jsonSchema.PORT_PREFIX, i);
                if (states[port].is<signed int>()) {
                    value = states[port].as<signed int>();
                    if (mode == constants.MODE_LOGICAL_OUTPUT) {
                        value = value > 0 ? HIGH : LOW;
                        digitalWrite(i, value);
                    } else {
                        value = value < 0 ? 0 : value > 255 ? 255
                                                            : value;
                        analogWrite(i, value);
                    }
                    currentState[i] = value;
                }
            }
        }
    }
}

void PortHandler::pushState() {
    collectData();
    JsonObject state = (*dataExchangeJson)[jsonSchema.STATE_WORD].to<JsonObject>();
    char port[16];
    for (int i = 1; i <= constants.LAST_PORT; ++i) {
        if (currentPortModes[i]) {
            snprintf(port, 16, "%s%d", jsonSchema.PORT_PREFIX, i);
            state[port] = currentState[i];
        }
    }
}

void PortHandler::collectData() {
    for (int i = 1; i <= constants.LAST_PORT; ++i) {
        if (currentPortModes[i] == constants.MODE_LOGICAL_INPUT)
            currentState[i] = digitalRead(i);
        if (currentPortModes[i] == constants.MODE_VALUE_INPUT)
            currentState[i] = analogRead(i);
        if (currentPortModes[i] == constants.MODE_INVERSED_LOGICAL_INPUT)
            currentState[i] = digitalRead(i) ? LOW : HIGH;
        if (currentPortModes[i] == constants.MODE_STATEFUL_LOGICAL_INPUT)
            collectStatefulData(i);
    }
}

void PortHandler::collectStatefulData() {
    for (int i = 1; i <= constants.LAST_PORT; ++i) {
        if (currentPortModes[i] == constants.MODE_STATEFUL_LOGICAL_INPUT)
            collectStatefulData(i);
    }
}

void PortHandler::collectStatefulData(int port) {
    // previous was not pressed
    if (currentStatefulInput[port] == LOW) {
        // INPUT_PULLUP ~ LOW means pressed
        if (digitalRead(port) == LOW) {
            currentState[port] = currentState[port] ? 0 : 1;
            // set previous as pressed
            currentStatefulInput[port] = HIGH;
        }
        // is not pressed anymore
    } else if (digitalRead(port) == HIGH) {
        // set previous as not pressed
        currentStatefulInput[port] = LOW;
    }
}
