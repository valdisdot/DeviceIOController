#include "task/Task.h"

Task::Task(const char* name, int startupDelay, int loopDelay, int executionType, int stackSize, int priority)
    : name(name), startupDelay(startupDelay), loopDelay(loopDelay), executionType(executionType), stackSize(stackSize), priority(priority) {}

const char* Task::getName() {
    return name;
}

const int& Task::getStartupDelay() {
    return startupDelay;
}

const int& Task::getLoopDelay() {
    return loopDelay;
}

bool Task::isCyclic() {
    return executionType == $TASK.TYPE$CYCLIC;
}

bool Task::isReactive() {
    return executionType == $TASK.TYPE$REACTIVE;
}

bool Task::isSingleRun() {
    return executionType == $TASK.TYPE$SINGLE_RUN;
}

const int& Task::getStackSize() {
    return stackSize;
}

const int& Task::getPriority() {
    return priority;
}