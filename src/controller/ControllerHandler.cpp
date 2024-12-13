#include "controller/ControllerHandler.h"

ControllerHandler::ControllerHandler(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema) : dataExchangeJson(dataExchangeJson), jsonSchema(jsonSchema) {}

void ControllerHandler::insertControllerInfo() {
    this->insertId();
    this->insertControllerState();
}

void ControllerHandler::insertId() {
    byte mac_base[6] = {0};
    esp_efuse_mac_get_default(mac_base);
    char id[32];
    snprintf(id, sizeof(id), "%d%d%d%d%d%d", mac_base[0] ^ 127, mac_base[1] ^ 127, mac_base[2] ^ 127, mac_base[3] ^ 127, mac_base[4] ^ 127, mac_base[5] ^ 127);
    (*dataExchangeJson)[jsonSchema.ID_WORD] = id;
}

void ControllerHandler::insertControllerState() {
    JsonObject controller = (*dataExchangeJson)[jsonSchema.CONTROLLER_WORD].to<JsonObject>();

    // System time
    // controller["uptimeMicroseconds"] = esp_get_time(); does not work
    // Add heap-related info

    // Get the CPU frequency in Hz (exact precision)
    // uint32_t cpu_freq_hz = 0;
    // esp_err_t ret = esp_clk_tree_src_get_freq_hz(ESP_CLK_SRC_CPU, ESP_CLK_TREE_SRC_FREQ_PRECISION_EXACT, &cpu_freq_hz); //does not work
    // controller["clockRate"] = cpu_freq_hz/1000000.0;

    controller[jsonSchema.HEAP_SIZE_WORD] = esp_get_free_heap_size();
    controller[jsonSchema.HEAP_MIN_SIZE_WORD] = esp_get_minimum_free_heap_size();

    // Reset reason
    switch (esp_reset_reason()) {
        case ESP_RST_POWERON:
            controller[jsonSchema.RESET_REASON_WORD] = "after power on";
            break;
        case ESP_RST_EXT:
            controller[jsonSchema.RESET_REASON_WORD] = "after triggering by external pin";
            break;
        case ESP_RST_SW:
            controller[jsonSchema.RESET_REASON_WORD] = "after manual software reset";
            break;
        case ESP_RST_PANIC:
            controller[jsonSchema.RESET_REASON_WORD] = "after error or panic reset";
            break;
        case ESP_RST_INT_WDT:
            controller[jsonSchema.RESET_REASON_WORD] = "after interrupt watchdog";
            break;
        case ESP_RST_TASK_WDT:
            controller[jsonSchema.RESET_REASON_WORD] = "after task watchdog";
            break;
        case ESP_RST_WDT:
            controller[jsonSchema.RESET_REASON_WORD] = "after other watchdog";
            break;
        case ESP_RST_DEEPSLEEP:
            controller[jsonSchema.RESET_REASON_WORD] = "after exiting deep sleep mode";
            break;
        case ESP_RST_BROWNOUT:
            controller[jsonSchema.RESET_REASON_WORD] = "after too low voltage";
            break;
        case ESP_RST_SDIO:
            controller[jsonSchema.RESET_REASON_WORD] = "after triggering via SDIO";
            break;
        default:
            controller[jsonSchema.RESET_REASON_WORD] = "unknown";
            break;
    }
    // Flash memory information
    uint32_t flash_size;
    esp_flash_get_size(NULL, &flash_size);
    controller[jsonSchema.FLASH_SIZE_WORD] = flash_size;
    // Chip information
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    controller[jsonSchema.CORES_WORD] = chip_info.cores;
    controller[jsonSchema.REVISION_WORD] = chip_info.revision;
    controller[jsonSchema.FEATURES_WORD][jsonSchema.WIFI_WORD] = (chip_info.features & CHIP_FEATURE_WIFI_BGN) > 0;
    controller[jsonSchema.FEATURES_WORD][jsonSchema.BLUETOOTH_WORD] = (chip_info.features & CHIP_FEATURE_BT) > 0;
    controller[jsonSchema.FEATURES_WORD][jsonSchema.BLUETOOTH_LE_WORD] = (chip_info.features & CHIP_FEATURE_BLE) > 0;
}

void ControllerHandler::reboot() {
    esp_restart();
}
