/**
 * @file BaseClient.h
 * @brief Defines a base class for clients to handle message processing and communication.
 *
 * This header file declares the `BaseClient` class, which provides an abstract base for
 * implementing specific client functionality. It includes methods for processing incoming 
 * messages, sending responses, and managing initialization.
 */

#ifndef BASE_CLIENT_H
#define BASE_CLIENT_H

#include "ArduinoJson.h"
#include "ControllerHandler.h"
#include "InternalStorage.h"
#include "JsonSchema.h"
#include "PortHandler.h"

/**
 * @class BaseClient
 * @brief Abstract base class for clients handling message processing and communication.
 *
 * The `BaseClient` class provides a framework for managing incoming and outgoing messages.
 * Derived classes must implement initialization, message sending, and response handling 
 * for their specific I/O interfaces.
 */
class BaseClient {
   protected:
    JsonDocument *dataExchangeJson;               /**< Pointer to the JSON document used for data exchange. */
    JsonSchema jsonSchema;                        /**< Instance of JsonSchema for field name management. */
    InternalStorage storage;                      /**< Instance of InternalStorage for ROM memory interaction. */
    ControllerHandler controllerHandler;          /**< Instance of ControllerHandler for controller operations. */
    PortHandler portHandler;                      /**< Instance of PortHandler for managing port states and modes. */

    /**
     * @brief Processes an incoming message from a JSON string.
     * @param messageJson Pointer to the JSON message string.
     * @param checkId Boolean indicating whether to check the message ID.
     */
    void pullMessageFrom(const char *messageJson, const bool &checkId);

    /**
     * @brief Calculates the hash code of an incoming message.
     * @param messageJson Pointer to the JSON message string.
     * @return The hash code of the message.
     */
    int pulledMessageHashCodeFrom(const char *messageJson);

    /**
     * @brief Sends a response to the result of message processing.
     * @param messageJsonHashCode Hash code of the processed message.
     * @param responseBody Pointer to the response body in JSON format.
     */
    void pushPullingResponse(int messageJsonHashCode, const char *responseBody);

    /**
     * @brief Abstract method to send the result of message processing.
     * @param responseJson Pointer to the JSON response string.
     */
    virtual void pushPullingResponce(const char *responseJson) = 0;

   public:
    /**
     * @brief Constructs a BaseClient object.
     * @param dataExchangeJson Pointer to a JSON document used for data exchange.
     * @param jsonSchema Reference to a JsonSchema object for field management.
     * @param storage Reference to an InternalStorage object for ROM memory interaction.
     * @param controllerHandler Reference to a ControllerHandler object for controller operations.
     * @param portHandler Reference to a PortHandler object for managing port states and modes.
     */
    BaseClient(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, InternalStorage &storage, ControllerHandler &controllerHandler, PortHandler &portHandler);

    /**
     * @brief Abstract method to initialize the client.
     * @return Boolean indicating whether initialization was successful.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Abstract method to send data manually.
     */
    virtual void pushMessage() = 0;
};

#endif
