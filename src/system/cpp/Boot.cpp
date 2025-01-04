#include "system/Boot.h"

Boot::Boot() : portState(),
               controllerState(),
               connectionConfiguration(),
               serverConfiguration(),
               controllerConfiguration(),
               storage(portState, connectionConfiguration, serverConfiguration, controllerConfiguration),
               portHandler(portState),
               mainTaskHandler($TASK.CORE$MAIN),
               backgroundTaskHandler($TASK.CORE$BACKGROUND) {}

void Boot::start() {
    storage.restoreConfiguration();
    storage.restoreState();
    portHandler.pullState();
    portHandler.pushState();
    int mode = connectionConfiguration.getMode();
    if (mode == $NETWORK.MODE$SERIAL)
        client = new SerialClient(storage, controllerState, portHandler, Serial);
    else {
        if (mode == $NETWORK.MODE$WIFI) {
            // init WiFi
            WiFi.mode(WIFI_STA);
            WiFi.begin(connectionConfiguration.getSSID(), connectionConfiguration.getPassword());
            // try to connect CONNECTION_ATTEMPTS times
            for (int i = 0; i < $NETWORK.CONNECTION_ATTEMPTS; ++i) {
                if (WiFi.status() != WL_CONNECTED) delay(1000);
            }
            // if wifi-connected
            if (WiFi.status() == WL_CONNECTED) {
                // create signal strength measurement task
                backgroundTaskHandler.create(new WiFiSignalStrengthCollector(controllerState));
                // if has a CA certificate from a mqtt-broker
                if (serverConfiguration.isSecure()) {
                    WiFiClientSecure *secureClient = new WiFiClientSecure();
                    secureClient->setCACert(serverConfiguration.getCertificate());
                    networkClient = secureClient;
                } else {
                    networkClient = new WiFiClient();
                }
            }
        } else if (mode == $NETWORK.MODE$CELLULAR) {
            // FEATURE #3 controllerState.setSignalStrength(-113 + tinyGSModem.getSignalQuality() * 2)}
            if (serverConfiguration.isSecure()) {
                // FUTURE #2: cheap GSM module (SIM800C/L) + TinyGSM library + serverConfiguration.getCertificate();
            } else {
                // FUTURE #1: cheap GSM module + TinyGSM library
            }
        }
        // if networkClient is initialized
        if (networkClient) {
            client = new MqttClient(storage, controllerState, portHandler, *networkClient);
        }
        // client is null or failed to initialize -> fall into the serial mode
        else {
            client = new SerialClient(storage, controllerState, portHandler, Serial);
            mode = $NETWORK.MODE$SERIAL;
        }
    }
    controllerState.setMode(mode);
    backgroundTaskHandler.create(new MemoryCollector(controllerState));
    backgroundTaskHandler.create(new PortHandlerStatefulCollectorTask(portHandler));
    backgroundTaskHandler.create(new BackupTask(storage));
    if (client->initialize())
        mainTaskHandler.create(new ClientRunnerTask(*client));
    else
        client->reboot();  // fall into reboot as long as client's initialization fails
}