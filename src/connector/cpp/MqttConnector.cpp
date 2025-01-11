#include "connector/MqttConnector.h"

bool MqttConnector::checkConnection() {
    if (!mqttClient.connected()) {
        for (int i = 0; i < $NETWORK.CONNECTION_ATTEMPTS; ++i) {
            if (mqttClient.connect(clientId, serverConfiguration.getUser(), serverConfiguration.getPassword()) &&
                mqttClient.subscribe(requestTopic) &&
                mqttClient.connected()) return true;
        }
        return false;
    }
    return true;
}

MqttConnector::MqttConnector(ServerConfiguration& serverConfiguration, Client& networkClient) : Connector($SYSTEM.SIZE$4K), serverConfiguration(serverConfiguration), networkClient(networkClient) {}

bool MqttConnector::init(std::function<void(const char*)> messageProcessor) {
    if (Connector::init(messageProcessor)) {
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

        mqttClient.setBufferSize($SYSTEM.SIZE$4K);
        mqttClient.setKeepAlive($NETWORK.KEEP_ALIVE);
        mqttClient.setClient(networkClient);
        mqttClient.setServer(serverConfiguration.getURL(), serverConfiguration.getPort());
        mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
            if (equal(topic, requestTopic)) {
                convertToASCIIString(buffer, payload, length);
                this->messageProcessor(buffer);
            }
        });
        return checkConnection();
    }
    return false;
}

bool MqttConnector::call() {
    if (!checkConnection()) return false;
    return mqttClient.loop();
}

void MqttConnector::sendState(const char* state) {
    mqttClient.publish(stateTopic, state);
}

void MqttConnector::sendControllerState(const char* controllerState) {
    mqttClient.publish(controllerStateTopic, controllerState);
}

void MqttConnector::sendResponse(const char* response) {
    mqttClient.publish(responseTopic, response);
}

void MqttConnector::sendLog(const char* log) {
    mqttClient.publish(logTopic, log);
}
