#include "system/MicroSystem.h"
#include "client/BaseClient.h"
#include "client/SerialClient.h"
#include "service/ControllerHandler.h"
#include "service/PortHandler.h"
#include "service/InternalStorage.h"
#include "task/ControllerTasks.h"
#include "task/TaskHandler.h"

PortState portState;
ControllerState controllerState;
ConnectionConfiguration connectionConfiguration;
ServerConfiguration serverConfiguration;

InternalStorage storage(portState, connectionConfiguration, serverConfiguration);
PortHandler portHandler(portState);
ControllerHandler controllerHandler(controllerState);
TaskHandler mainTaskHandler(TASK_CONSTANT.MAIN_CORE);
TaskHandler backgroundTaskHandler(TASK_CONSTANT.BACKGROUND_CORE);
BaseClient *client = nullptr;

void setup() {
    storage.restoreConfiguration();
    storage.restoreState();
    portHandler.pullState();
    portHandler.pushState();
    int mode = connectionConfiguration.getMode();

    if (mode == CONSTANT.CONNECTION_MODE_SERIAL) {
        Serial.begin(38400);
        client = new SerialClient(storage, controllerHandler, portHandler, Serial);
    } else {
        int transmissionInterval = connectionConfiguration.getTransmissionInterval();
        // make a task to pushMessages if mode is not serial (not one-chanel client's)
        // here!
        if (mode == CONSTANT.CONNECTION_MODE_WIFI) {
            // init mqtt-client with wifi
        } else if (mode == CONSTANT.CONNECTION_MODE_CELLULAR) {
            // init mqtt-client with cellurar
        }  // other clients
    }
    if (client) {
        while (!client->initialize()) {}
        backgroundTaskHandler.create(new PortHandlerStatefulCollectorTask(portHandler));
        backgroundTaskHandler.create(new BackupTask(storage));
        mainTaskHandler.create(new ClientRunnerTask(*client));
    } else {
        ESP_LOGE("Initialization error", "Client is not initialized, no instanse was found for mode: %d", mode);
        abort();
    }
}

void loop(){}
