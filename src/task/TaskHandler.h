#ifndef TASK_HANDLER_H
#define TASK_HANDLER_H

#include <atomic>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "util/Constant.h"
#include "util/JsonSchema.h"
#include "util/Function.h"
#include "task/Task.h"

class TaskHandler {
   private:
    int activeCore;
    TaskHandle_t gcTaskHandle; 
    int* taskIdHolder;
    TaskHandle_t** taskHandleHolder; 
    Task** taskHolder; 
    int nextTaskId = 100; 
    std::atomic<bool> lock{false};

    static void taskInitializer(void* taskPointer);
    static void gc(void* taskHandler);

    void clean(const int& onIndex);

   public:
    TaskHandler(int activeCore);
    int create(Task* task);
    bool suspend(const int& taskId);
    bool resume(const int& taskId);
    bool invoke(const int& taskId);
    void cancel(const int& taskId);
    int getAvailableStackSize(const int& taskId);
    void setPriority(const int& taskId, int priority);
    int getPriority(const int& taskId);
    const char* getName(const int& taskId);
    int getState(const int& taskId);
    void gc();
};

#endif
