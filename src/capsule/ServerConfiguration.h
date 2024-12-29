#ifndef SERVER_CONFIGURATION_H
#define SERVER_CONFIGURATION_H

#include "system/MicroSystem.h"

class ServerConfiguration {
   private:
    JsonDocument holder;

   public:
    const char* getURL();
    int getPort();
    const char* getUser();
    const char* getPassword();
    bool isSecure();
    const char* getCertificate();
    JsonObjectConst getAsJson();
    void updateFromJson(JsonObjectConst configuration);
};

#endif