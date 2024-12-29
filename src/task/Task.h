#ifndef TASK_H
#define TASK_H

#include "system/MicroSystem.h"

class Task {
   protected:
    const char* name;                           
    const int startupDelay;                  
    const int loopDelay;                    
    const int executionType;                      
    const int stackSize;                      
    const int priority;                                

   public:
    Task(const char* name, int startupDelay, int loopDelay, int executionType, int stackSize, int priority);
    const char* getName();
    const int& getStartupDelay();
    const int& getLoopDelay();
    bool isCyclic();
    bool isReactive();
    bool isSingleRun();
    const int& getStackSize();
    const int& getPriority();
    virtual void execute() = 0;
};

#endif
