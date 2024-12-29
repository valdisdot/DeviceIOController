#ifndef BOOT_H
#define BOOT_H

#include "client/BaseClient.h"
#include "client/SerialClient.h"
#include "service/ControllerHandler.h"
#include "service/InternalStorage.h"
#include "service/PortHandler.h"
#include "system/MicroSystem.h"
#include "task/ControllerTasks.h"
#include "task/TaskHandler.h"

class Boot {
   private:
    PortState portState;
    ControllerState controllerState;
    ConnectionConfiguration connectionConfiguration;
    ServerConfiguration serverConfiguration;
    InternalStorage storage;
    PortHandler portHandler;
    ControllerHandler controllerHandler;
    TaskHandler mainTaskHandler;
    TaskHandler backgroundTaskHandler;
    BaseClient *client = nullptr;

   public:
    Boot();
    void start();
};

#endif