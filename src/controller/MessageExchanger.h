#ifndef BASIC_CLIENT_H
#define BASIC_CLIENT_H

#include <ArduinoJson.h>

#include "connector/Connector.h"
#include "controller/Logger.h"
#include "request/RequestResolver.h"
#include "service/Storage.h"
#include "service/PortHandler.h"
#include "util/Map.h"
#include "util/Runnable.h"

class MessageExchanger : public Runnable {
   private:
    Connector &connector;
    Storage &storage;
    PortHandler &portHandler;
    Logger &logger;
    Map<const char*, RequestResolver*, CStringComparator> resolvers;
    char buffer[$SYSTEM.SIZE$4K];
    char smallBuffer[$SYSTEM.SIZE$2K];
    unsigned long lastStateSend = 0;

    void sendResponse(const int& messageIdentity, JsonObject responseHolder);

   public:
    MessageExchanger(Connector &connector, Storage &storage, PortHandler &portHandler, Logger &logger);
    void addRequestResolver(RequestResolver *requestResolver);
    void init() override;
    void run() override;
    void sendState();
    void sendControllerState();
    void processMessage(const char *message);
};

#endif
