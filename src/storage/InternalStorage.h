/**
 * @file InternalStorage.h
 * @brief Provides an API to interact with the controller's ROM memory.
 *
 * This header file defines the `InternalStorage` class, which facilitates reading,
 * writing, and managing data stored in the controller's ROM memory. It supports
 * operations for configuration, port modes, and state management.
 */

#ifndef INTERNAL_STORAGE_H
#define INTERNAL_STORAGE_H

#include <ArduinoJson.h>
#include <Preferences.h>
#include "constant/ControllerConstants.h"
#include "constant/JsonSchema.h"

/**
 * @class InternalStorage
 * @brief A class to manage data in the controller's ROM memory.
 *
 * The `InternalStorage` class provides methods to read and write data to the controller's
 * ROM memory. It allows manipulation of configuration settings, port modes, and port states.
 */
class InternalStorage {
   private:
    Preferences preferences;        /**< Object to handle preferences storage. */
    JsonDocument *dataExchangeJson; /**< Pointer to the JSON document used for data exchange. */
    JsonSchema jsonSchema;          /**< Instance of JsonSchema for field name management. */
    ControllerConstants constants;  /**< Instance of ControllerConstants for controller logic constants. */

   public:
    /**
     * @brief Constructs an InternalStorage object.
     * @param dataExchangeJson Pointer to a JSON document used for data exchange.
     * @param jsonSchema Reference to a JsonSchema object for field management.
     * @param constants Reference to a ControllerConstants object for logic constants.
     */
    InternalStorage(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, const ControllerConstants &constants);

    /**
     * @brief Reads all data from the memory into the JSON document.
     *
     * Combines the operations of reading configuration, modes, and state values.
     */
    void readAll();

    /**
     * @brief Reads controller and network-related values into the JSON document.
     */
    void readConfiguration();

    /**
     * @brief Reads port mode values into the JSON document.
     */
    void readModes();

    /**
     * @brief Reads the last port state values into the JSON document.
     */
    void readState();

    /**
     * @brief Saves all data from the JSON document into the memory.
     *
     * Combines the operations of saving configuration, modes, and state values.
     */
    void saveAll();

    /**
     * @brief Saves controller and network-related values from the JSON document into the memory.
     */
    void saveConfiguration();

    /**
     * @brief Saves port mode values from the JSON document into the memory.
     */
    void saveModes();

    /**
     * @brief Saves the last port state values from the JSON document into the memory.
     */
    void saveState();

    /**
     * @brief Erases all saved values from the memory.
     */
    void erase();
};

#endif
