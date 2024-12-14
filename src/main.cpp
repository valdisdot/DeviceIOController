#include "Arduino.h"
#include "ArduinoJson.h"
#include "client/BaseClient.h"
#include "client/SerialClient.h"
#include "constant/ControllerConstants.h"
#include "constant/JsonSchema.h"
#include "constant/TaskConstants.h"
#include "controller/ControllerHandler.h"
#include "port/PortHandler.h"
#include "storage/InternalStorage.h"
#include "task/ControllerTasks.h"
#include "task/TaskHandler.h"

JsonDocument *doc = new JsonDocument();
JsonSchema jsonSchema;
ControllerConstants constants;
InternalStorage storage(doc, jsonSchema, constants);
PortHandler portHandler(doc, jsonSchema, constants);
ControllerHandler controllerHandler(doc, jsonSchema);
TaskConstants taskConstants;
TaskHandler mainTaskHandler(taskConstants, taskConstants.MAIN_CORE);
TaskHandler backgroundTaskHandler(taskConstants, taskConstants.BACKGROUND_CORE);
BaseClient *client = nullptr;

void setup() {
    storage.readAll();
    portHandler.pullModes();
    portHandler.pullState();
    portHandler.collectData();
    controllerHandler.insertId();
    int mode = (*doc)[jsonSchema.CONFIG_WORD][jsonSchema.MODE_WORD].as<int>();

    if (mode == constants.CLIENT_SERIAL) {
        client = new SerialClient(doc, jsonSchema, storage, controllerHandler, portHandler, Serial);
    } else {
        int transmissionInterval = (*doc)[jsonSchema.CONFIG_WORD][jsonSchema.TRANSMISSION_INTERVAL_WORD].as<int>();
        // make a task to pushMessages if mode is not serial (not one-chanel client's)
        // here!
        if (mode == constants.CLIENT_MQTT) {
            // init mqtt-client
        } else if (mode == constants.CLIENT_HTTP) {
            // init http-client
        }  // other clients
    }
    if (client) {
        while (!client->initialize()) {}
        backgroundTaskHandler.create(new PortHandlerStatefulCollectorTask(portHandler, taskConstants));
        backgroundTaskHandler.create(new DataExchangerSaverTask(storage, taskConstants));
        mainTaskHandler.create(new ClientRunnerTask(*client, taskConstants));
    } else {
        ESP_LOGE("Initialization error", "Client is not initialized, no instanse was found for mode: %d", mode);
        abort();
    }
}

void loop(){}
