#include "connector/Connector.h"

Connector::Connector(int bufferSize) {
    byte mac_base[6] = {0};
    esp_efuse_mac_get_default(mac_base);
    snprintf(id, sizeof(id), "%d%d%d%d%d%d", mac_base[0] ^ 127, mac_base[1] ^ 127, mac_base[2] ^ 127, mac_base[3] ^ 127, mac_base[4] ^ 127, mac_base[5] ^ 127);
    buffer = new char[bufferSize];
    buffer[0] = '\0';
}

bool Connector::init(std::function<void(const char*)> messageProcessor) {
    if (messageProcessor) {
        this->messageProcessor = messageProcessor;
        return true;
    }
    return false;
}