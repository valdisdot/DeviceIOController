/**
 * @file PortHandler.h
 * @brief Provides an API to manage ports and handle their states and modes.
 *
 * This header file defines the `PortHandler` class, which manages port operations,
 * including setting port modes, collecting port data, and synchronizing states 
 * between hardware and a JSON document.
 */

#ifndef PORT_HANDLER_H
#define PORT_HANDLER_H

#include "Arduino.h"
#include "ArduinoJson.h"
#include "ControllerConstants.h"
#include "JsonSchema.h"

/**
 * @class PortHandler
 * @brief A class to handle port operations, including state and mode management.
 *
 * The `PortHandler` class provides methods to manage port modes, read and write port states,
 * and collect data from stateless and stateful ports. It also synchronizes data with a JSON document.
 */
class PortHandler {
   private:
    JsonDocument *dataExchangeJson;               /**< Pointer to the JSON document used for data exchange. */
    JsonSchema jsonSchema;                        /**< Instance of JsonSchema for field name management. */
    ControllerConstants constants;                /**< Instance of ControllerConstants for controller logic constants. */
    int *currentState;                            /**< Array storing the current state of each port. */
    int *currentPortModes;                        /**< Array storing the current mode of each port. */
    int *currentStatefulInput;                    /**< Array storing the state of stateful input ports. */

    /**
     * @brief Collects data from stateless ports and updates the current state.
     * @param port The port number to collect data from.
     */
    void collectStatefulData(int port);

   public:
    /**
     * @brief Constructs a PortHandler object.
     * @param dataExchangeJson Pointer to a JSON document used for data exchange.
     * @param jsonSchema Reference to a JsonSchema object for field management.
     * @param constants Reference to a ControllerConstants object for logic constants.
     */
    PortHandler(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, const ControllerConstants &constants);

    /**
     * @brief Synchronizes port state by pulling and pushing it.
     *
     * Combines the operations of pulling states from the JSON document and
     * pushing updated states back into it.
     */
    void pullAndPushState();

    /**
     * @brief Pulls port modes from the JSON document and sets port modes.
     *
     * Reads port mode data from the JSON document and updates the currentPortModes array.
     */
    void pullModes();

    /**
     * @brief Pulls port states from the JSON document and updates applicable states.
     *
     * Reads port state data from the JSON document and updates the currentState array
     * and hardware states where applicable.
     */
    void pullState();

    /**
     * @brief Pushes port states into the JSON document.
     *
     * Reads the currentState array and writes the data into the JSON document.
     */
    void pushState();

    /**
     * @brief Collects data from all ports and updates the current state.
     *
     * Physically reads data from the ports and updates the currentState array. It
     * also incorporates stateful data collection.
     */
    void collectData();

    /**
     * @brief Collects data from stateful ports.
     *
     * Iterates over each port to collect stateful data and updates the corresponding
     * state in the currentState array.
     */
    void collectStatefulData();
};

#endif
