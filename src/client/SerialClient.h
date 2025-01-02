#ifndef SERIAL_CLIENT_H
#define SERIAL_CLIENT_H

#include "client/BaseClient.h"

class SerialClient : public BaseClient {
   private:
    const char *DIVIDER = "\n#END#\n"; 
    HardwareSerial &serial;            

    void send(const char *data);

   protected:
    void sendState(const char *state) override;
    void sendControllerState(const char *controllerState) override;
    void sendResponse(const char *response) override;
    void sendLog(const char *log) override;

   public:
    SerialClient(InternalStorage &storage, ControllerHandler &controllerHandler, PortHandler &portHandler, HardwareSerial &serial);
    bool initialize() override;
    void step() override;
};

#endif
