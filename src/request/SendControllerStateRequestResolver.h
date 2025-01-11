#ifndef SEND_CONTROLLER_STATE_REQUEST_RESOLVER_H
#define SEND_CONTROLLER_STATE_REQUEST_RESOLVER_H
#include "controller/MessageExchanger.h"
#include "request/RequestResolver.h"

class SendControllerStateRequestResolver : public RequestResolver {
   private:
    MessageExchanger &messageExchanger;

   public:
    SendControllerStateRequestResolver(const char *name, MessageExchanger &messageExchanger);
    int resolve(JsonVariant requestValue) override;
};

#endif