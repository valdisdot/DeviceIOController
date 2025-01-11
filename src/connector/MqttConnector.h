#ifndef MQTT_CONNECTOR_H
#define MQTT_CONNECTOR_H

#include <Client.h>
#include <PubSubClient.h>

#include "capsule/ServerConfiguration.h"
#include "connector/Connector.h"
#include "util/Constant.h"
#include "util/JsonSchema.h"
#include "util/Function.h"
#include <ArduinoJson.h>

class MqttConnector : public Connector {
   private:
    ServerConfiguration& serverConfiguration;
    Client& networkClient;
    PubSubClient mqttClient;
    char clientId[$SYSTEM.SIZE$64];
    char stateTopic[$SYSTEM.SIZE$64];
    char controllerStateTopic[$SYSTEM.SIZE$64];
    char responseTopic[$SYSTEM.SIZE$64];
    char requestTopic[$SYSTEM.SIZE$64];
    char logTopic[$SYSTEM.SIZE$64];

    bool checkConnection();

   public:
    MqttConnector(ServerConfiguration& serverConfiguration, Client& networkClient);
    bool init(std::function<void(const char*)> messageProcessor) override;
    bool call() override;
    void sendState(const char* state) override;
    void sendControllerState(const char* controllerState) override;
    void sendResponse(const char* response) override;
    void sendLog(const char* log) override;
};

#endif
