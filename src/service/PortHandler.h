#ifndef PORT_HANDLER_H
#define PORT_HANDLER_H

#include "system/MicroSystem.h"
#include "capsule/PortState.h"

class PortHandler {
   private:
    PortState &state;
    int *data;                    
    int *modes;                     
    int *statefulData;                   

    void collectStatefulData(int port);
    void collectData();
    void pullModes();
    void pullData();

   public:
    PortHandler(PortState &state);
    void pullState();
    void pushState();
    void checkStatefulPorts();
};

#endif
