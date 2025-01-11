#ifndef REQUEST_RESOLVER_H
#define REQUEST_RESOLVER_H

#include <ArduinoJson.h>
#include <util/Function.h>
#include <util/Constant.h>

class RequestResolver {
    private:
    char *name;
    bool requireReboot;

    public:
    RequestResolver(const char* name, bool requireReboot);
    virtual const char* getName();
    virtual const bool& isRebootRequired();
    virtual int resolve(JsonVariant requestValue) = 0;
};

#endif