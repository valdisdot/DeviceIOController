#include "client/MqttClient.h"

bool MqttClient::checkConnection() {
    if (!mqttClient.connected()) {
        ServerConfiguration configuration = storage.getServerConfiguration();
        for (int i = 0; i < $NETWORK.CONNECTION_ATTEMPTS; ++i)
            if (connectToServer(configuration)) return true;
        return false;
    }
    return true;
}

bool MqttClient::connectToServer(ServerConfiguration& serverConfiguration) {
    if (mqttClient.connect(clientId, serverConfiguration.getUser(), serverConfiguration.getPassword())) {
        mqttClient.subscribe(requestTopic);
    }
    return mqttClient.connected();
}

void MqttClient::callback(const char* topic, byte* payload, unsigned int length) {
    if (equal(topic, requestTopic)) {
        convertToASCIIString(buffer, payload, length);
        processMessage(buffer);
    }
}

void MqttClient::sendState(const char* state) {
    mqttClient.publish(stateTopic, state);
}

void MqttClient::sendControllerState(const char* controllerState) {
    mqttClient.publish(controllerStateTopic, controllerState);
}

void MqttClient::sendResponse(const char* response) {
    mqttClient.publish(responseTopic, response);
}

void MqttClient::sendLog(const char* log) {
    mqttClient.publish(logTopic, log);
}

MqttClient::MqttClient(InternalStorage& storage, ControllerState& controllerState, PortHandler& portHandler, Client& networkClient) : BaseClient(storage, controllerState, portHandler), networkClient(networkClient) {
    const char* topicDivider = "/";
    copyString(clientId, "client-", $SYSTEM.SIZE$64);
    concatenateString(clientId, id, $SYSTEM.SIZE$64);

    /*
        from/123456789/state
        from/123456789/controllerState
        from/123456789/response
        from/123456789/log
        to/123456789/request
    */

    copyString(stateTopic, $MQTT.TOPIC$FROM, $SYSTEM.SIZE$64);
    concatenateString(stateTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(stateTopic, id, $SYSTEM.SIZE$64);
    concatenateString(stateTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(stateTopic, $MQTT.TOPIC$STATE, $SYSTEM.SIZE$64);

    copyString(controllerStateTopic, $MQTT.TOPIC$FROM, $SYSTEM.SIZE$64);
    concatenateString(controllerStateTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(controllerStateTopic, id, $SYSTEM.SIZE$64);
    concatenateString(controllerStateTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(controllerStateTopic, $MQTT.TOPIC$CONTROLLER, $SYSTEM.SIZE$64);

    copyString(responseTopic, $MQTT.TOPIC$FROM, $SYSTEM.SIZE$64);
    concatenateString(responseTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(responseTopic, id, $SYSTEM.SIZE$64);
    concatenateString(responseTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(responseTopic, $MQTT.TOPIC$RESPONSE, $SYSTEM.SIZE$64);

    copyString(logTopic, $MQTT.TOPIC$FROM, $SYSTEM.SIZE$64);
    concatenateString(logTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(logTopic, id, $SYSTEM.SIZE$64);
    concatenateString(logTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(logTopic, $MQTT.TOPIC$LOG, $SYSTEM.SIZE$64);

    copyString(requestTopic, $MQTT.TOPIC$TO, $SYSTEM.SIZE$64);
    concatenateString(requestTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(requestTopic, id, $SYSTEM.SIZE$64);
    concatenateString(requestTopic, topicDivider, $SYSTEM.SIZE$64);
    concatenateString(requestTopic, $MQTT.TOPIC$REQUEST, $SYSTEM.SIZE$64);
}

bool MqttClient::initialize() {
    mqttClient.setBufferSize($SYSTEM.SIZE$4K);
    mqttClient.setKeepAlive($NETWORK.KEEP_ALIVE);
    mqttClient.setClient(networkClient);
    ServerConfiguration &serverConfiguration = storage.getServerConfiguration();
    mqttClient.setServer(serverConfiguration.getURL(), serverConfiguration.getPort());
    mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->callback(topic, payload, length);
    });
    return checkConnection() && BaseClient::initialize();
}

void MqttClient::step() {
    // fall in reboot, the network client might be disconnected
    if (!checkConnection()) reboot();
    mqttClient.loop();
    BaseClient::step();
}
