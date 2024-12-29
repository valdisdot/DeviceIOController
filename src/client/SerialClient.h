/**
 * @file SerialClient.h
 * @brief Defines the `SerialClient` class for serial communication.
 *
 * The `SerialClient` class extends `BaseClient` to provide serial-based communication
 * functionalities. It manages data transmission, state updates, and message processing
 * over a hardware serial interface.
 */

#ifndef SERIAL_CLIENT_H
#define SERIAL_CLIENT_H

#include "client/BaseClient.h"

/**
 * @class SerialClient
 * @brief A client implementation for serial communication.
 *
 * The `SerialClient` class facilitates communication over a hardware serial interface.
 * It handles message processing, state updates, and configuration management via
 * JSON-based communication.
 */
class SerialClient : public BaseClient {
   private:
    const char *DIVIDER = "\n#END#\n"; /**< Message delimiter used to separate transmissions. */
    HardwareSerial &serial;            /**< Reference to the hardware serial interface. */

    /**
     * @brief Sends data over the serial interface.
     * @param data The data to be sent as a C-string.
     */
    void send(const char *data);

   protected:
    /**
     * @brief Sends the current state over the serial interface.
     * @param state The current state as a C-string.
     */
    void sendState(const char *state) override;

    /**
     * @brief Sends the controller's current state over the serial interface.
     * @param controllerState The controller state as a C-string.
     */
    void sendControllerState(const char *controllerState) override;

    /**
     * @brief Sends a response message over the serial interface.
     * @param response The response message as a C-string.
     */
    void sendResponse(const char *response) override;

   public:
    /**
     * @brief Constructs a `SerialClient` object.
     * @param dataExchangeJson Pointer to the JSON document for data exchange.
     * @param jsonSchema Reference to the `JsonSchema` object for field management.
     * @param storage Reference to the `InternalStorage` object for ROM operations.
     * @param controllerHandler Reference to the `ControllerHandler` object.
     * @param portHandler Reference to the `PortHandler` object.
     * @param serial Reference to the hardware serial interface.
     */
    SerialClient(InternalStorage &storage, ControllerHandler &controllerHandler, PortHandler &portHandler, HardwareSerial &serial);

    /**
     * @brief Initializes the serial client.
     * 
     * This method sets up the hardware serial interface, clears any garbage data,
     * and reads the initial configuration from storage.
     * 
     * @return `true` if initialization is successful, `false` otherwise.
     */
    bool initialize() override;

    /**
     * @brief Processes a single step of operations.
     *
     * Reads available data from the serial interface and processes it as a message.
     */
    void step() override;
};

#endif
