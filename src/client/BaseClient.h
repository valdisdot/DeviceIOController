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

#include "service/ControllerHandler.h"
#include "service/PortHandler.h"
#include "service/InternalStorage.h"

class BaseClient {
   protected:
    InternalStorage &storage;
    ControllerHandler &controllerHandler;
    PortHandler &portHandler;

    void sendState();
    void sendControllerState();
    void processMessage(const char *message, const bool &checkControllerId);
    void processRequest(const char *name, const JsonVariant values, JsonArray responseHolder, bool &doReboot);
    void sendResponse(const int &messageIdentity, const int &messageHash, JsonObject responseHolder);
    void sendError(const int &messageIdentity, const int &messageHash, const char *errorType, const char *details);
    virtual void sendState(const char *state) = 0;
    virtual void sendControllerState(const char *controllerState) = 0;
    virtual void sendResponse(const char *response) = 0;

   public:
    BaseClient(InternalStorage &storage, ControllerHandler &controllerHandler, PortHandler &portHandler);
    virtual bool initialize() = 0;
    virtual void step() = 0;
    virtual void loop();
};

#endif
