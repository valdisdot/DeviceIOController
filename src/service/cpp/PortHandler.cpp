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
    for (int i = 1; i < $PORT.COUNT; ++i) {
        if (modes[i] == $PORT.MODE$LOGICAL_INPUT)
            data[i] = digitalRead(i);
        if (modes[i] == $PORT.MODE$VALUE_INPUT)
            data[i] = analogRead(i);
        if (modes[i] == $PORT.MODE$INVERSED_LOGICAL_INPUT)
            data[i] = digitalRead(i) ? LOW : HIGH;
        if (modes[i] == $PORT.MODE$STATEFUL_LOGICAL_INPUT)
            collectStatefulData(i);
    }
}

void PortHandler::pullModes() {
    int temp[$PORT.COUNT];
    state.copyModesInto(temp);
    for (int i = 0; i < $PORT.COUNT; ++i) {
        if (modes[i] != temp[i]) {
            modes[i] = temp[i];
            data[i] = $SYSTEM.NO_VALUE$INT;
            if (modes[i] == $PORT.MODE$NOT_INITIALIZED || modes[i] == $PORT.MODE$INIT_FORBIDDEN)
                continue;
            else if (modes[i] == $PORT.MODE$LOGICAL_INPUT || modes[i] == $PORT.MODE$VALUE_INPUT)
                pinMode(i, INPUT);
            else if (modes[i] == $PORT.MODE$LOGICAL_OUTPUT || modes[i] == $PORT.MODE$VALUE_OUTPUT)
                pinMode(i, OUTPUT);
            else if (modes[i] == $PORT.MODE$INVERSED_LOGICAL_INPUT || modes[i] == $PORT.MODE$STATEFUL_LOGICAL_INPUT)
                pinMode(i, INPUT_PULLUP);
        }
    }
}

void PortHandler::pullData() {
    int value;
    int temp[$PORT.COUNT];
    state.copyDataInto(temp);
    for (int i = 1; i <= $PORT.COUNT; ++i) {
        if (modes[i] == $PORT.MODE$LOGICAL_OUTPUT || modes[i] == $PORT.MODE$VALUE_OUTPUT || modes[i] == $PORT.MODE$STATEFUL_LOGICAL_INPUT) {
            if (modes[i] == $PORT.MODE$LOGICAL_OUTPUT) {
                value = temp[i] > 0 ? HIGH : LOW;
                digitalWrite(i, value);
            } else if (modes[i] == $PORT.MODE$VALUE_OUTPUT) {
                value = temp[i] < 0 ? 0 : temp[i] > 4096 ? 4096
                                                         : temp[i];
                analogWrite(i, value / 4096 * 255);
            } else
                value = temp[i] > 0 ? HIGH : LOW;
            data[i] = value;
        }
    }
}

PortHandler::PortHandler(PortState &state) : state(state) {
    data = new int[$PORT.COUNT];
    modes = new int[$PORT.COUNT];
    statefulData = new int[$PORT.COUNT];
    for (int i = 1; i < $PORT.COUNT; ++i) {
        data[i] = $SYSTEM.NO_VALUE$INT;
        modes[i] = $SYSTEM.NO_VALUE$INT;
        statefulData[i] = $SYSTEM.NO_VALUE$INT;
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
    for (int i = 1; i < $PORT.COUNT; ++i) {
        if (modes[i] == $PORT.MODE$STATEFUL_LOGICAL_INPUT)
            collectStatefulData(i);
    }
}