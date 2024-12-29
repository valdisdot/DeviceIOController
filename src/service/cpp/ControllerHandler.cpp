#include "service/ControllerHandler.h"

ControllerHandler::ControllerHandler(ControllerState& state) : state(state) {
    byte mac_base[6] = {0};
    esp_efuse_mac_get_default(mac_base);
    snprintf(id, sizeof(id), "%d%d%d%d%d%d", mac_base[0] ^ 127, mac_base[1] ^ 127, mac_base[2] ^ 127, mac_base[3] ^ 127, mac_base[4] ^ 127, mac_base[5] ^ 127);
}

const char* ControllerHandler::getId() {
    return id;
}

void ControllerHandler::pushControllerState() {
    state.setMinMemoryState(esp_get_minimum_free_heap_size());
    state.setMaxMemoryState(esp_get_free_heap_size());
    switch (esp_reset_reason()) {
        case ESP_RST_POWERON:
            state.setLastRebootReason("after power on");
            break;
        case ESP_RST_EXT:
            state.setLastRebootReason("after triggering by external pin");
            break;
        case ESP_RST_SW:
            state.setLastRebootReason("after manual software reset");
            break;
        case ESP_RST_PANIC:
            state.setLastRebootReason("after error or panic reset");
            break;
        case ESP_RST_INT_WDT:
            state.setLastRebootReason("after interrupt watchdog");
            break;
        case ESP_RST_TASK_WDT:
            state.setLastRebootReason("after task watchdog");
            break;
        case ESP_RST_WDT:
            state.setLastRebootReason("after other watchdog");
            break;
        case ESP_RST_DEEPSLEEP:
            state.setLastRebootReason("after exiting deep sleep mode");
            break;
        case ESP_RST_BROWNOUT:
            state.setLastRebootReason("after too low voltage");
            break;
        case ESP_RST_SDIO:
            state.setLastRebootReason("after triggering via SDIO");
            break;
        default:
            state.setLastRebootReason("unknown");
            break;
    }
}

void ControllerHandler::reboot() {
    esp_restart();
}

ControllerState& ControllerHandler::getControllerState() {
    return state;
}
