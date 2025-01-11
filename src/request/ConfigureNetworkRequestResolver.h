#ifndef CONFIGURE_NETWORK_REQUEST_RESOLVER_H
#define CONFIGURE_NETWORK_REQUEST_RESOLVER_H
#include "request/RequestResolver.h"
#include "service/Storage.h"

class ConfigureNetworkRequestResolver : public RequestResolver {
    private:
    Storage& storage;
    public:
    ConfigureNetworkRequestResolver(const char *name, Storage& storage);
    int resolve(JsonVariant requestValue) override;
};

#endif