/**
 * @file ControllerInfo.h
 * @brief Provides an API to manage controller operations and retrieve its information.
 *
 * This header file defines the `ControllerHandler` class, which facilitates interactions
 * with the controller. It includes methods for retrieving controller information, managing
 * its state, and performing software resets.
 */

#ifndef CONTROLLER_INFO_H
#define CONTROLLER_INFO_H

#include "ArduinoJson.h"
#include "JsonSchema.h"
#include "Preferences.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "esp_mac.h"
#include "esp_system.h"
#include "esp_timer.h"
#include "esp_wifi.h"

/**
 * @class ControllerHandler
 * @brief A class to manage controller operations and retrieve information.
 *
 * The `ControllerHandler` class provides methods to interact with the controller, including
 * retrieving its details, inserting data into a JSON document, and executing a software reset.
 */
class ControllerHandler {
   private:
    JsonDocument *dataExchangeJson;               /**< Pointer to the JSON document used for data exchange. */
    JsonSchema jsonSchema;                        /**< Instance of JsonSchema for field name management. */

   public:
    /**
     * @brief Constructs a ControllerHandler object.
     * @param dataExchangeJson Pointer to a JSON document used for data exchange.
     * @param jsonSchema Reference to a JsonSchema object for field management.
     */
    ControllerHandler(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema);

    /**
     * @brief Inserts controller-related information into the JSON document.
     */
    void insertControllerInfo();

    /**
     * @brief Inserts the controller's unique ID into the JSON document.
     */
    void insertId();

    /**
     * @brief Inserts the controller's state into the JSON document.
     */
    void insertControllerState();

    /**
     * @brief Executes a software reset of the controller.
     */
    void reboot();
};

#endif
