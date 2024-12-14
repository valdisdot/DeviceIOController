#ifndef SERIAL_CLIENT_H
#define SERIAL_CLIENT_H

#include <Arduino.h>
#include "client/BaseClient.h"

class SerialClient : public BaseClient {
   private:
    HardwareSerial &serial;

   protected:
    void pushPullingResponce(const char *responseJson) override;

   public:
    SerialClient(JsonDocument *dataExchangeJson, const JsonSchema &jsonSchema, InternalStorage &storage, ControllerHandler &controllerHandler, PortHandler &portHandler, HardwareSerial &serial);
    // Push a message via Serial
    void pushMessage() override;
    // Initialize the Serial connection
    bool initialize() override;
    // Run the client
    void run() override;
};

#endif
