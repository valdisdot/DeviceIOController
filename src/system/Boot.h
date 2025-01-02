#ifndef BOOT_H
#define BOOT_H

#include "client/BaseClient.h"
#include "client/SerialClient.h"
#include "client/MqttClient.h"
#include "service/ControllerHandler.h"
#include "service/InternalStorage.h"
#include "service/PortHandler.h"
#include "system/MicroSystem.h"
#include "task/ControllerTasks.h"
#include "task/TaskHandler.h"
#include <WIFI.h>
#include <WiFiClientSecure.h>

class Boot {
   private:
    PortState portState;
    ControllerState controllerState;
    NetworkConfiguration connectionConfiguration;
    ServerConfiguration serverConfiguration;
    ControllerConfiguration controllerConfiguration;
    InternalStorage storage;
    PortHandler portHandler;
    ControllerHandler controllerHandler;
    TaskHandler mainTaskHandler;
    TaskHandler backgroundTaskHandler;
    Client *networkClient = nullptr;
    BaseClient *client = nullptr;
    
   public:
    Boot();
    void start();
};

#endif