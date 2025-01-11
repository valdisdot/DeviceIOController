#include "controller/Boot.h"

Boot::Boot() : portState(),
               controllerState(),
               connectionConfiguration(),
               serverConfiguration(),
               controllerConfiguration(),
               storage(portState, controllerState, connectionConfiguration, serverConfiguration, controllerConfiguration),
               portHandler(portState),
               mainTaskHandler($TASK.CORE$MAIN),
               backgroundTaskHandler($TASK.CORE$BACKGROUND) {}

void Boot::init() {
    storage.restoreConfiguration();
    storage.restoreState();
    portHandler.pullState();
    portHandler.pushState();
    controllerState.setLastRebootReason(esp_reset_reason());
    int mode = connectionConfiguration.getMode();
    if (mode == $NETWORK.MODE$SERIAL)
        connector = new SerialConnector(Serial);
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
            connector = new MqttConnector(serverConfiguration, *networkClient);
        }
        // client is null or failed to initialize -> fall into the serial mode
        else {
            connector = new SerialConnector(Serial);
            mode = $NETWORK.MODE$SERIAL;
        }
    }
    logger = new Logger(*connector);
    logger->setLogLevel(storage.getControllerConfiguration().getLogLevel());
    messageExchanger = new MessageExchanger(*connector, storage, portHandler, *logger);

    messageExchanger->addRequestResolver(new ConfigureControllerRequestResolver($MESSAGE.REQUEST$CONFIGURE_CONTROLLER, storage, *logger));
    messageExchanger->addRequestResolver(new ConfigureNetworkRequestResolver($MESSAGE.REQUEST$CONFIGURE_NETWORK, storage));
    messageExchanger->addRequestResolver(new ConfigureServerRequestResolver($MESSAGE.REQUEST$CONFIGURE_SERVER, storage));
    messageExchanger->addRequestResolver(new MakeBackupRequestResolver($MESSAGE.REQUEST$MAKE_BACKUP, storage));
    messageExchanger->addRequestResolver(new RebootRequestResolver($MESSAGE.REQUEST$REBOOT));
    messageExchanger->addRequestResolver(new SendControllerStateRequestResolver($MESSAGE.REQUEST$SEND_CONTROLLER_STATE, *messageExchanger));
    messageExchanger->addRequestResolver(new SendStateRequestResolver($MESSAGE.REQUEST$SEND_STATE, *messageExchanger));
    messageExchanger->addRequestResolver(new SetDataRequestResolver($MESSAGE.REQUEST$SET_DATA, portHandler, storage, *messageExchanger));
    messageExchanger->addRequestResolver(new SetModesRequestResolver($MESSAGE.REQUEST$SET_MODES, portHandler, storage, *messageExchanger));

    // configureControllerRequestResolver = new ConfigureControllerRequestResolver($MESSAGE.REQUEST$CONFIGURE_CONTROLLER, storage, *logger);
    // configureNetworkRequestResolver = new ConfigureNetworkRequestResolver($MESSAGE.REQUEST$CONFIGURE_NETWORK, storage);
    // configureServerRequestResolver = new ConfigureServerRequestResolver($MESSAGE.REQUEST$CONFIGURE_SERVER, storage);
    // makeBackupRequestResolver = new MakeBackupRequestResolver($MESSAGE.REQUEST$MAKE_BACKUP, storage);
    // rebootRequestResolver = new RebootRequestResolver($MESSAGE.REQUEST$REBOOT);
    // sendControllerStateRequestResolver = new SendControllerStateRequestResolver($MESSAGE.REQUEST$SEND_CONTROLLER_STATE, *messageExchanger);
    // sendStateRequestResolver = new SendStateRequestResolver($MESSAGE.REQUEST$SEND_STATE, *messageExchanger);
    // setDataRequestResolver = new SetDataRequestResolver($MESSAGE.REQUEST$SET_DATA, portHandler, storage, *messageExchanger);
    // setModesRequestResolver = new SetModesRequestResolver($MESSAGE.REQUEST$SET_MODES, portHandler, storage, *messageExchanger);
    // messageExchanger->addRequestResolver(configureControllerRequestResolver);
    // messageExchanger->addRequestResolver(configureNetworkRequestResolver);
    // messageExchanger->addRequestResolver(configureServerRequestResolver);
    // messageExchanger->addRequestResolver(makeBackupRequestResolver);
    // messageExchanger->addRequestResolver(rebootRequestResolver);
    // messageExchanger->addRequestResolver(sendControllerStateRequestResolver);
    // messageExchanger->addRequestResolver(sendStateRequestResolver);
    // messageExchanger->addRequestResolver(setDataRequestResolver);
    // messageExchanger->addRequestResolver(setModesRequestResolver);
    if (!connector->init([this](const char *message) { this->messageExchanger->processMessage(message); })) {
        esp_restart();
    }
    messageExchanger->init();
    controllerState.setMode(mode);
    backgroundTaskHandler.create(new PortHandlerStatefulCollectorTask(portHandler));
    backgroundTaskHandler.create(new BackupTask(storage));
}

void Boot::run() {
    messageExchanger->run();
}