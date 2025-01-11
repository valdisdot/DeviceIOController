#ifndef BOOT_H
#define BOOT_H

#include <WIFI.h>
#include <WiFiClientSecure.h>

#include "connector/Connector.h"
#include "connector/MqttConnector.h"
#include "connector/SerialConnector.h"
#include "controller/MessageExchanger.h"
#include "request/ConfigureControllerRequestResolver.h"
#include "request/ConfigureNetworkRequestResolver.h"
#include "request/ConfigureServerRequestResolver.h"
#include "request/MakeBackupRequestResolver.h"
#include "request/RebootRequestResolver.h"
#include "request/SendControllerStateRequestResolver.h"
#include "request/SendStateRequestResolver.h"
#include "request/SetDataRequestResolver.h"
#include "request/SetModesRequestResolver.h"
#include "service/Storage.h"
#include "service/PortHandler.h"
#include "task/ControllerTasks.h"
#include "task/TaskHandler.h"
#include "util/Constant.h"
#include "util/Function.h"
#include "util/JsonSchema.h"
#include "util/Runnable.h"

class Boot : public Runnable {
   private:
    PortState portState;
    ControllerState controllerState;
    NetworkConfiguration connectionConfiguration;
    ServerConfiguration serverConfiguration;
    ControllerConfiguration controllerConfiguration;
    Storage storage;
    PortHandler portHandler;
    TaskHandler mainTaskHandler;
    TaskHandler backgroundTaskHandler;
    Client *networkClient = nullptr;
    Connector *connector = nullptr;
    Logger *logger = nullptr;
    MessageExchanger *messageExchanger = nullptr;

   public:
    Boot();
    void init() override;
    void run() override;
};

#endif