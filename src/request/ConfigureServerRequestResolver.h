#ifndef CONFIGURE_SERVER_REQUEST_RESOLVER_H
#define CONFIGURE_SERVER_REQUEST_RESOLVER_H
#include "request/RequestResolver.h"
#include "service/Storage.h"

class ConfigureServerRequestResolver : public RequestResolver {
    private:
    Storage& storage;
    public:
    ConfigureServerRequestResolver(const char *name, Storage& storage);
    int resolve(JsonVariant requestValue) override;
};

#endif