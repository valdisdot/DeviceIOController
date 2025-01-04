/**
 * @file BaseClient.h
 * @brief Provides the base class for managing client operations including JSON-based communication and state handling.
 *
 * The `BaseClient` class defines the core functionalities required for processing
 * messages, handling state and configuration, and interacting with various hardware
 * and software components.
 */

#ifndef BASIC_CLIENT_H
#define BASIC_CLIENT_H

#include "capsule/ControllerState.h"
#include "service/InternalStorage.h"
#include "service/PortHandler.h"

class BaseClient {
   protected:
    char id[$SYSTEM.SIZE$32];
    InternalStorage &storage;
    ControllerState &controllerState;
    PortHandler &portHandler;
    LogLevel logLevel;

    char buffer[$SYSTEM.SIZE$4K];
    unsigned long lastStateSend = 0;

    virtual void processMessage(const char *message);
    virtual int processRequest(const char *name, const JsonVariant value, JsonArray responsesArray, bool &doReboot);
    virtual void sendResponse(const int &messageIdentity, JsonObject responseMessage);

    virtual void sendState(const char *state) = 0;
    virtual void sendControllerState(const char *controllerState) = 0;
    virtual void sendResponse(const char *response) = 0;
    virtual void sendLog(const char *log) = 0;

   public:
    BaseClient(InternalStorage &storage, ControllerState &controllerState, PortHandler &portHandler);
    virtual bool initialize();
    virtual void step();
    void sendState();
    void sendControllerState();
    virtual void log(const LogLevel &level, const char *module, const char *message, const char *details);
    virtual void reboot();
};

#endif
