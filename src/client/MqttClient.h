#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <Client.h>
#include <PubSubClient.h>
#include "client/BaseClient.h"

class MqttClient : public BaseClient {
   private:
    Client& networkClient;
    PubSubClient mqttClient;
    char clientId[$SYSTEM.SIZE$64];
    char stateTopic[$SYSTEM.SIZE$64];
    char controllerStateTopic[$SYSTEM.SIZE$64];
    char responseTopic[$SYSTEM.SIZE$64];
    char requestTopic[$SYSTEM.SIZE$64];
    char logTopic[$SYSTEM.SIZE$64];

    unsigned long lastStateSend = 0;

    bool checkConnection();
    bool connectToServer(ServerConfiguration& serverConfiguration);
    void callback(const char* topic, byte* payload, unsigned int length);

   protected:
    void sendState(const char* state) override;
    void sendControllerState(const char* controllerState) override;
    void sendResponse(const char* response) override;
    void sendLog(const char* log) override;

   public:
    MqttClient(InternalStorage& storage, ControllerHandler& controllerHandler, PortHandler& portHandler, Client& networkClient);
    bool initialize() override;
    void step() override;
};

#endif