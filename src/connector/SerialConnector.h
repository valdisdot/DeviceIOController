#ifndef SERIAL_CONNECTOR_H
#define SERIAL_CONNECTOR_H

#include <HardwareSerial.h>
#include "connector/Connector.h"
#include "util/Constant.h"
#include "util/JsonSchema.h"
#include "util/Function.h"
#include <ArduinoJson.h>

class SerialConnector : public Connector {
   private:
    HardwareSerial& serial;

    const char* DIVIDER = "\n#END#\n";
    bool unlocked = false;

    void send(const char* data);

   public:
    SerialConnector(HardwareSerial& serial);
    bool init(std::function<void(const char*)> messageProcessor) override;
    bool call() override;
    void sendState(const char* state) override;
    void sendControllerState(const char* controllerState) override;
    void sendResponse(const char* response) override;
    void sendLog(const char* log) override;
};

#endif
