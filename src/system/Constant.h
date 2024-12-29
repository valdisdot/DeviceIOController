#ifndef SYSTEM_CONSTANT_H
#define SYSTEM_CONSTANT_H

struct SystemConstant {
    const static int SIZE_16 = 16;
    const static int SIZE_32 = 32;
    const static int SIZE_64 = 64;
    const static int SIZE_128 = 128;
    const static int SIZE_512 = 512;
    const static int SIZE_1K = 1024;
    const static int SIZE_2K = 2048;
    const static int SIZE_4K = 4096;
    const static int SIZE_8K = 8192;

    const int CONNECTION_MODE_SERIAL = 1;
    const int CONNECTION_MODE_WIFI = 2;
    const int CONNECTION_MODE_CELLULAR = 3;

    const int MODE_NOT_INITIALIZED = 0;
    const int MODE_LOGICAL_INPUT = 1;                 
    const int MODE_LOGICAL_OUTPUT = 2;                
    const int MODE_VALUE_INPUT = 3;                  
    const int MODE_VALUE_OUTPUT = 4;                    
    const int MODE_INVERSED_LOGICAL_INPUT = 5;       
    const int MODE_STATEFUL_LOGICAL_INPUT = 6;       
    const int MODE_INIT_FORBIDDEN = 10;

    const int RESPONSE_OK = 1;
    const int RESPONSE_FAIL = 0;
    const int RESPONSE_UNDEFINED = -1;

    const int NO_VALUE_INT = -1;
    const char* NO_VALUE_STR = "";

    const int PORT_COUNT = 40;

    SystemConstant() = default;
};

struct RequestType {
    const char* SET_MODES = "set_modes";
    const char* SET_DATA = "set_data";
    const char* CONFIGURE_CONNECTION = "configure_connection";
    const char* CONFIGURE_SERVER = "configure_server";
    const char* REBOOT = "reboot";
    const char* SEND_CONTROLLER_STATE = "send_controller_state";
    const char* MAKE_BACKUP = "make_backup";

    RequestType() = default;
};

struct TaskConstant {
    const int TASK_TYPE_SINGLE_RUN = 0;           
    const int TASK_TYPE_CYCLIC = 1;             
    const int TASK_TYPE_REACTIVE = 2;         

    const int TASK_STATE_UNDEFINED = 0;      
    const int TASK_STATE_RUNNING = 1;            
    const int TASK_STATE_AWAITS_IN_QUEUE = 2;  
    const int TASK_STATE_AWAINTS_NOTIFICATION = 3;
    const int TASK_STATE_SUSPENDED = 4;          
    const int TASK_STATE_DELETED = 5;           

    const int HANDLER_GC_INTERVAL = 60000;     
    const int HANDLER_HOLDER_SIZE = 30;          
    const int MAIN_CORE = 0;                    
    const int BACKGROUND_CORE = 1;                

    const int PRIOTITY_NOW = 32;                
    const int PRIOTITY_HIGH = 16;              
    const int PRIOTITY_MIDDLE = 8;              
    const int PRIOTITY_LOW = 0;              

    const int PORT_HANDLER_STATE_COLLECTOR_TASK_STACK_SIZE = 4048;
    //users set their own delay
    const int PORT_HANDLER_STATE_COLLECTOR_TASK_PRIORITY = PRIOTITY_HIGH; 

    const int PORT_HANDLER_STATEFUL_COLLECTOR_TASK_STACK_SIZE = 4048; 
    const int PORT_HANDLER_STATEFUL_COLLECTOR_TASK_DELAY = 10; 
    const int PORT_HANDLER_STATEFUL_COLLECTOR_TASK_PRIORITY = PRIOTITY_NOW; 

    const int INTERNAL_STORAGE_TASK_STACK_SIZE = 8192; 
    const int INTERNAL_STORAGE_TASK_DELAY = 60000;  //1 minute
    const int INTERNAL_STORAGE_TASK_PRIORITY = PRIOTITY_MIDDLE;

    const int CLIENT_RUNNER_TASK_STACK_SIZE = 8192; 
    const int CLIENT_RUNNER_TASK_DELAY = 100; 
    const int CLIENT_RUNNER_TASK_PRIORITY = PRIOTITY_NOW; 
};

#endif