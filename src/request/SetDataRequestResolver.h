#ifndef SET_DATA_REQUEST_RESOLVER_H
#define SET_DATA_REQUEST_RESOLVER_H
#include "request/RequestResolver.h"
#include "service/PortHandler.h"
#include "service/Storage.h"
#include "controller/MessageExchanger.h"

class SetDataRequestResolver : public RequestResolver {
    PortHandler &portHandler;
    Storage& storage;
    MessageExchanger &messageExchanger;
    public:
    SetDataRequestResolver(const char *name, PortHandler &portHandler, Storage& storage, MessageExchanger &messageExchanger);
    int resolve(JsonVariant requestValue) override;
};

#endif