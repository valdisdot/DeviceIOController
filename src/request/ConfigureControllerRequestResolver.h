#ifndef CONFIGURE_CONTROLLER_REQUEST_RESOLVER_H
#define CONFIGURE_CONTROLLER_REQUEST_RESOLVER_H
#include "request/RequestResolver.h"
#include "service/Storage.h"
#include "controller/Logger.h"

class ConfigureControllerRequestResolver : public RequestResolver {
    private:
    Storage &storage;
    Logger &logger;
    
    public:
    ConfigureControllerRequestResolver(const char *name, Storage &storage, Logger &logger);
    int resolve(JsonVariant requestValue) override;
};

#endif