#include "service/PortHandler.h"

void PortHandler::collectStatefulData(int port) {
    // previous was not pressed
    if (statefulData[port] == LOW) {
        // INPUT_PULLUP ~ LOW means pressed
        if (digitalRead(port) == LOW) {
            data[port] = data[port] ? 0 : 1;
            // set previous as pressed
            statefulData[port] = HIGH;
        }
        // is not pressed anymore
    } else if (digitalRead(port) == HIGH) {
        // set previous as not pressed
        statefulData[port] = LOW;
    }
}

void PortHandler::collectData() {
    for (int i = 1; i < CONSTANT.PORT_COUNT; ++i) {
        if (modes[i] == CONSTANT.MODE_LOGICAL_INPUT)
            data[i] = digitalRead(i);
        if (modes[i] == CONSTANT.MODE_VALUE_INPUT)
            data[i] = analogRead(i);
        if (modes[i] == CONSTANT.MODE_INVERSED_LOGICAL_INPUT)
            data[i] = digitalRead(i) ? LOW : HIGH;
        if (modes[i] == CONSTANT.MODE_STATEFUL_LOGICAL_INPUT)
            collectStatefulData(i);
    }
}

void PortHandler::pullModes() {
    int temp[CONSTANT.PORT_COUNT];
    state.copyModesInto(temp);
    for (int i = 0; i < CONSTANT.PORT_COUNT; ++i) {
        if (modes[i] != temp[i]) {
            modes[i] = temp[i];
            data[i] = CONSTANT.NO_VALUE_INT;
            if (modes[i] == CONSTANT.MODE_NOT_INITIALIZED || modes[i] == CONSTANT.MODE_INIT_FORBIDDEN)
                continue;
            else if (modes[i] == CONSTANT.MODE_LOGICAL_INPUT || modes[i] == CONSTANT.MODE_VALUE_INPUT)
                pinMode(i, INPUT);
            else if (modes[i] == CONSTANT.MODE_LOGICAL_OUTPUT || modes[i] == CONSTANT.MODE_VALUE_OUTPUT)
                pinMode(i, OUTPUT);
            else if (modes[i] == CONSTANT.MODE_INVERSED_LOGICAL_INPUT || modes[i] == CONSTANT.MODE_STATEFUL_LOGICAL_INPUT)
                pinMode(i, INPUT_PULLUP);
        }
    }
}

void PortHandler::pullData() {
    int value;
    int temp[CONSTANT.PORT_COUNT];
    state.copyDataInto(temp);
    for (int i = 1; i <= CONSTANT.PORT_COUNT; ++i) {
        if (modes[i] == CONSTANT.MODE_LOGICAL_OUTPUT || modes[i] == CONSTANT.MODE_VALUE_OUTPUT || modes[i] == CONSTANT.MODE_STATEFUL_LOGICAL_INPUT) {
            if (modes[i] == CONSTANT.MODE_LOGICAL_OUTPUT) {
                value = temp[i] > 0 ? HIGH : LOW;
                digitalWrite(i, value);
            } else if (modes[i] == CONSTANT.MODE_VALUE_OUTPUT) {
                value = temp[i] < 0 ? 0 : temp[i] > 255 ? 255
                                                        : temp[i];
                analogWrite(i, value);
            } else
                value = temp[i] > 0 ? HIGH : LOW;
            data[i] = value;
        }
    }
}

PortHandler::PortHandler(PortState &state) : state(state) {
    data = new int[CONSTANT.PORT_COUNT];
    modes = new int[CONSTANT.PORT_COUNT];
    statefulData = new int[CONSTANT.PORT_COUNT];
    for (int i = 1; i < CONSTANT.PORT_COUNT; ++i) {
        data[i] = CONSTANT.NO_VALUE_INT;
        modes[i] = CONSTANT.NO_VALUE_INT;
        statefulData[i] = CONSTANT.NO_VALUE_INT;
    }
}

void PortHandler::pullState() {
    pullModes();
    pullData();
}

void PortHandler::pushState() {
    collectData();
    state.setData(data);
}

void PortHandler::checkStatefulPorts() {
    for (int i = 1; i < CONSTANT.PORT_COUNT; ++i) {
        if (modes[i] == CONSTANT.MODE_STATEFUL_LOGICAL_INPUT)
            collectStatefulData(i);
    }
}