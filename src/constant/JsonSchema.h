/**
 * @file JsonSchema.h
 * @brief Contains definitions of JSON field names and patterns for the application's JSON schema.
 *
 * This header file defines a `JsonSchema` structure that stores constant strings
 * representing field names and specific patterns used within the application's JSON schema.
 */

#ifndef JSON_SCHEMA_H
#define JSON_SCHEMA_H

/**
 * @struct JsonSchema
 * @brief Structure containing JSON field names and patterns.
 *
 * This structure provides constant string members representing field names and
 * patterns used in the application's JSON schema. It is intended to facilitate
 * consistent use of these fields across the application.
 */
struct JsonSchema {
    const char* CONFIG_WORD = "configuration";               /**< Represents the configuration field name. */
    const char* MODE_WORD = "mode";                          /**< Represents the mode field name. */
    const char* SSID_WORD = "ssid";                          /**< Represents the SSID field name. */
    const char* PASSWORD_WORD = "password";                  /**< Represents the password field name. */
    const char* TRANSMISSION_INTERVAL_WORD = "transmission_interval"; /**< Represents the transmission interval field name. */

    const char* MODES_WORD = "modes";                        /**< Represents the modes field name. */
    const char* STATE_WORD = "state";                        /**< Represents the state field name. */
    const char* PORT_PREFIX = "port_";                       /**< Prefix for port field names. */

    const char* ID_WORD = "id";                              /**< Represents the ID field name. */

    const char* CONTROLLER_WORD = "controller";              /**< Represents the controller field name. */
    const char* HEAP_SIZE_WORD = "heap_size";                 /**< Represents the heap size field name. */
    const char* HEAP_MIN_SIZE_WORD = "heap_min_size";          /**< Represents the minimum heap size field name. */
    const char* RESET_REASON_WORD = "reset_reason";       /**< Represents the reset reason code field name. */
    const char* FLASH_SIZE_WORD = "flash_memory_size";         /**< Represents the flash memory size field name. */
    const char* CORES_WORD = "cores";                        /**< Represents the cores field name. */
    const char* REVISION_WORD = "revision";                  /**< Represents the revision field name. */
    const char* FEATURES_WORD = "features";                  /**< Represents the features field name. */
    const char* WIFI_WORD = "wifi";                          /**< Represents the Wi-Fi field name. */
    const char* BLUETOOTH_WORD = "bluetooth";                /**< Represents the Bluetooth field name. */
    const char* BLUETOOTH_LE_WORD = "bluetooth_le";           /**< Represents the Bluetooth Low Energy field name. */

    const char* MESSAGE_ID_WORD = "message_id";           /**< Represents the message hash field name. */
    const char* REQUEST_WORD = "request";           /**< Represents the message hash field name. */
    const char* NAME_WORD = "name";           /**< Represents the message hash field name. */
    const char* VALUE_WORD = "value";           /**< Represents the message hash field name. */
    const char* MESSAGE_HASH_WORD = "message_hash";           /**< Represents the message hash field name. */
    const char* RESPONSE_WORD = "response";           /**< Represents the message hash field name. */
    const char* RESULT_WORD = "result";           /**< Represents the message hash field name. */
    const char* TYPE_WORD = "type";               /**< Represents the response message field name. */
    const char* DETAILS_WORD = "details";               /**< Represents the response message field name. */

    JsonSchema() = default; /**< Default constructor for the JsonSchema structure. */
};

#endif
