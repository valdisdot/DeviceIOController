#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <functional>
#include <Arduino.h>
#include "util/Constant.h"

class Connector {
   protected:
    char id[$SYSTEM.SIZE$32];
    char *buffer;
    const char *controllerId;
    std::function<void(const char *)> messageProcessor;

   public:
    Connector(int bufferSize);
    virtual bool init(std::function<void(const char *)> messageProcessor);
    virtual bool call() = 0;
    virtual void sendState(const char *state) = 0;
    virtual void sendControllerState(const char *controllerState) = 0;
    virtual void sendResponse(const char *response) = 0;
    virtual void sendLog(const char *log) = 0;
};

#endif
