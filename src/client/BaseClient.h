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

#include <ArduinoJson.h>

#include "constant/JsonSchema.h"
#include "controller/ControllerHandler.h"
#include "port/PortHandler.h"
#include "storage/InternalStorage.h"

/**
 * @class BaseClient
 * @brief Abstract base class for managing client operations, state processing, and communication.
 *
 * The `BaseClient` class provides methods for processing JSON messages, managing
 * stateful and configuration data, and interacting with hardware components.
 * Derived classes must implement the virtual methods for sending data.
 */
class BaseClient {
   protected:
    JsonDocument *dataExchangeJson;       /**< Pointer to the JSON document used for data exchange. */
    const JsonSchema &jsonSchema;         /**< Instance of `JsonSchema` for managing field names. */
    InternalStorage &storage;             /**< Reference to `InternalStorage` for persistent memory operations. */
    ControllerHandler &controllerHandler; /**< Reference to `ControllerHandler` for controller management. */
    PortHandler &portHandler;             /**< Reference to `PortHandler` for port state and mode handling. */

    /**
     * @brief Sends the current state to the remote endpoint.
     */
    void sendState();

    /**
     * @brief Sends the controller's current state to the remote endpoint.
     */
    void sendControllerState();

    /**
     * @brief Calculates a hash code for a given message.
     * @param message The input message as a C-string.
     * @return The calculated hash code.
     */
    int calculateHashCode(const char *message);

    /**
     * @brief Compares two C-strings for equality.
     * @param s1 The first string.
     * @param s2 The second string.
     * @return `true` if the strings are equal, `false` otherwise.
     */
    bool equals(const char *s1, const char *s2);

    /**
     * @brief Processes an incoming JSON message and generates appropriate responses.
     * @param message The incoming JSON message as a C-string.
     * @param checkControllerId Indicates whether to validate the controller ID in the message.
     */
    void processMessage(const char *message, const bool &checkControllerId);

    /**
     * @brief Processes an individual request from the received JSON message.
     * @param name The name of the request as a C-string.
     * @param values The JSON value associated with the request.
     * @param responseHolder Pointer to the JSON array for holding responses.
     * @param doReboot Reference to a boolean indicating whether a reboot is required.
     */
    void processRequest(const char *name, const JsonVariant &values, JsonArray *responseHolder, bool &doReboot);

    /**
     * @brief Sends a JSON-formatted response to the remote endpoint.
     * @param messageIdentity The unique identifier for the message.
     * @param messageHash The hash code of the message.
     * @param responseHolder Pointer to the JSON document containing the response.
     */
    void sendResponse(const int &messageIdentity, const int &messageHash, JsonDocument *responseHolder);

    /**
     * @brief Sends a JSON-formatted error response to the remote endpoint.
     * @param messageIdentity The unique identifier for the message.
     * @param messageHash The hash code of the message.
     * @param errorType A string representing the type of error.
     * @param details A string with detailed information about the error.
     */
    void sendError(const int &messageIdentity, const int &messageHash, const char *errorType, const char *details);

    /**
     * @brief Sends the state as a string to the remote endpoint.
     * @param state The state string to be sent.
     */
    virtual void sendState(const char *state) = 0;

    /**
     * @brief Sends the controller state as a string to the remote endpoint.
     * @param controllerState The controller state string to be sent.
     */
    virtual void sendControllerState(const char *controllerState) = 0;

    /**
     * @brief Sends a response string to the remote endpoint.
     * @param response The response string to be sent.
     */
    virtual void sendResponse(const char *response) = 0;

   public:
    /**
     * @brief Constructs a `BaseClient` object with the given dependencies.
     * @param dataExchangeJson Pointer to the JSON document for data exchange.
     * @param jsonSchema Reference to the `JsonSchema` object for field management.
     * @param storage Reference to the `InternalStorage` object.
     * @param controllerHandler Reference to the `ControllerHandler` object.
     * @param portHandler Reference to the `PortHandler` object.
     */
    BaseClient(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, InternalStorage &storage, ControllerHandler &controllerHandler, PortHandler &portHandler);

    /**
     * @brief Initializes the client.
     * @return `true` if initialization is successful, `false` otherwise.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Performs a single step of client operations.
     */
    virtual void step() = 0;

    /**
     * @brief Runs the client operations in a continuous loop.
     */
    virtual void loop();
};

#endif
